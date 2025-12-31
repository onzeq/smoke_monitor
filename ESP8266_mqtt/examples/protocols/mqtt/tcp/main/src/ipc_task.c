/* spi_slave example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "app_main.h"
#include "driver/spi.h"
#include "driver/hspi_logic_layer.h"

// static const char *TAG = "spi_slave_example";

#define SPI_SLAVE_HANDSHARK_GPIO                4

#define SPI_WRITE_BUFFER_MAX_SIZE               2048
#define SPI_READ_BUFFER_MAX_SIZE                1024


uint32_t read_count = 0;
static char* TAG = "ipc_task";

char str[10];
static void IRAM_ATTR spi_slave_read_master_task(void *arg)
{
    static uint8_t read_data[SPI_READ_BUFFER_MAX_SIZE];
    uint32_t read_len = 0;
    for (;;) {

        read_len = hspi_slave_logic_read_data(read_data, SPI_READ_BUFFER_MAX_SIZE, 1000);

        if(read_len > 0)
        {

            send_mqtt(read_data, read_len);
        }
        ESP_LOGI(TAG,"read_len %.3f: \n", *(float*)(read_data));
        ESP_LOGI(TAG,"read_len %d: \n", read_len);
        for(int i=0;i< read_len;i++){
            
            ESP_LOGI(TAG,"Receive byte %d: %x\n",i, read_data[i]);
            
        }
        memset(read_data, 0x0, SPI_READ_BUFFER_MAX_SIZE);
    }
}

void ipc_task_create(void)
{
    spi_config_t spi_config;
    // Load default interface parameters
    // CS_EN:1, MISO_EN:1, MOSI_EN:1, BYTE_TX_ORDER:1, BYTE_TX_ORDER:1, BIT_RX_ORDER:0, BIT_TX_ORDER:0, CPHA:0, CPOL:0
    spi_config.interface.val = SPI_DEFAULT_INTERFACE;

    // Load default interrupt enable
    // TRANS_DONE: false, WRITE_STATUS: true, READ_STATUS: true, WRITE_BUFFER: true, READ_BUFFER: ture
    spi_config.intr_enable.val = SPI_SLAVE_DEFAULT_INTR_ENABLE;
    // Set SPI to slave mode
    spi_config.mode = SPI_SLAVE_MODE;
    // Register SPI event callback function
    spi_config.event_cb = NULL;
    spi_init(HSPI_HOST, &spi_config);

    hspi_slave_logic_device_create(SPI_SLAVE_HANDSHARK_GPIO, 1, SPI_WRITE_BUFFER_MAX_SIZE, SPI_READ_BUFFER_MAX_SIZE);
#ifdef SPI_SLAVE_TEST_SEND
    xTaskCreate(spi_slave_write_master_task, "spi_slave_write_master_task", 2048, NULL, 2, NULL);
#else
    // create spi_slave_read_master_task
    xTaskCreate(spi_slave_read_master_task, "spi_slave_read_master_task", 2048, NULL, 5, NULL);
#endif
}


