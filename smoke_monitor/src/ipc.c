#include "FreeRTOS.h"
#include <event_groups.h>
#include <queue.h>

#include <stdint.h>
#include <string.h>

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"

#include "spi.h"
#include "ipc.h"

#define TX_BUFF_SIZE 32
static SPI_HandleTypeDef hspi2;
static uint8_t tx_buffer[TX_BUFF_SIZE];
static IPC_STATUS_COMMAND_S status_cmd;


EventGroupHandle_t gpioEventGroup;
QueueHandle_t ipc_queue;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (GPIO_Pin == SLAVE_DONE_PIN)   // your GPIO pin
    {
        xEventGroupSetBitsFromISR(
            gpioEventGroup,
            SLAVE_DONE_EVENT_BIT,
            &xHigherPriorityTaskWoken
        );
    }

    // Context switch if a higher-priority task was woken
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void wait_for_isr()
{
            while(!(xEventGroupGetBits( gpioEventGroup ) & SLAVE_DONE_EVENT_BIT) )
            {
                vTaskDelay(100);
            }
            return;
}

void ipc_init()
{
    HAL_StatusTypeDef err = HAL_OK;
    /* Initialize event group */
    gpioEventGroup = xEventGroupCreate();
    configASSERT(gpioEventGroup != NULL);
    /* Initialize message queue for sending bme data*/
    ipc_queue = xQueueCreate(
        QUEUE_LENGTH,
        sizeof(BME_RESIST_VAL_S *)   // size of a pointer, NOT the struct
    );

    if (ipc_queue == NULL)
    {
        /* TODO Handle */
    }

    /* Initialize gpio for handshake*/
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = SLAVE_DONE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; // interrupt on HIGH
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Enable EXTI interrupt in NVIC
    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    /* Initialize spi2*/

    err = MX_SPI2_Init(&hspi2);
    if(HAL_OK != err)
    {
        while(1)
        {}
    }

}
static ipc_write(void* data, uint32_t len)
{
    
    HAL_StatusTypeDef err = HAL_OK;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    err = HAL_SPI_Transmit(&hspi2, 
                    data, 
                    len, 
                    portMAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    return err;
}

void ipc_task()
{
    HAL_StatusTypeDef err = HAL_OK;
    BME_RESIST_VAL_S *bme_data = NULL;
    ipc_init();
    /* Make sure cs is low as long as esp boots up */

    for(;;)
    {
        if (xQueueReceive(ipc_queue, &bme_data, portMAX_DELAY) == pdFAIL)
        {
            vTaskDelay(100);
            continue;
        }
        if(NULL == bme_data) 
        {
            vTaskDelay(100);
            continue;
        }
        {
            /* Write lenth to status register */
            status_cmd.cmd = 1; /* Status command */
            status_cmd.data = sizeof(BME_RESIST_VAL_S); /* Status command */
            err = ipc_write(&status_cmd, sizeof(status_cmd));
            if(HAL_OK != err)
            {
                continue;
            }

            wait_for_isr();

            /* Write actual data */
            tx_buffer[0] = 2; /* Master send command */ 
            memcpy(tx_buffer +1, bme_data, sizeof(BME_RESIST_VAL_S)); /* Copy data to tx buffer */

            err = ipc_write(&tx_buffer, sizeof(BME_RESIST_VAL_S) +1 );
            if(HAL_OK != err)
            {
                continue;
            }
            wait_for_isr();

            /* Write lenth to status register */
            status_cmd.cmd = 1; /* Status command */
            status_cmd.data = 0x00; /* Status command */

            err = ipc_write(&tx_buffer, sizeof(BME_RESIST_VAL_S) +1 );
            if(HAL_OK != err)
            {
                continue;
            }
            wait_for_isr();
        }
    }

    /* 
1. Since there will be a conflict if both master and slave transmit data to each 
other at the same time. So, before the master transmiting data, it will check 
if the ESP8266 is transmitting data now. If it is, then the master will wait 
until the ESP8266's transmission completed.
2. The master writes the data length to the status register, indicates the 
length of data that it is going to transmit.
3. The ESP8266 will generate a WR\_STA_DONE interrupt, and pull up the 
GPIO\_HANDSHAKE pin to inform the master that it has got the data length 
information.
4. The master can send up to 64 bytes per time. If data is longer than 64 
bytes, then it needs to be divided to several subpackets to send.
5. ESP8266 will store the received data into the SPI register, and generate a 
WR\_BUF\_DONE interrupt, and then pull up the GPIO\_HANDSHAKE pin to inform the 
master that it has received the previous data and the master can start the next
 transmission now. 
6. The master has to wait for the interrupt of GPIO\_HANDSHAKE pin, which means
 ESP8266 received the data successfully, to start the next transmission. 
7. After sent data, the master will check the software buffer to see if there 
is more data wait for sending. 
  * If there is, then the master will repeat the procedure starts from step 2. 
  * If there is not, then the master needs to write 0 to the status register, 
  * indicates that data sending completed. When ESP8266 reads the status 0, the
  *  ESP8266 stops pulling up the GPIO\_HANDSHAKE pin.*/

}