/**
 * Copyright (C) 2023 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "bme68x.h"
#include "bme680/common.h"
#include "spi.h"

#include "stm32f1xx_hal.h"

/******************************************************************************/
/*!                 Macro definitions                                         */
/*! BME68X shuttle board ID */
#define BME68X_SHUTTLE_ID  0x93
#define BUFFER_SIZE 8

/******************************************************************************/
/*!                Static variable definition                                 */
static uint8_t dev_addr;
SPI_HandleTypeDef hspi1;

static volatile bool bme680_vbRspiIdle;
// static void bme680_vRspiCb(void* pcbdat);
static uint8_t r_buffer[BUFFER_SIZE];
static uint8_t w_buffer[BUFFER_SIZE];

/******************************************************************************/
/*!                User interface functions                                   */

/*!
 * SPI read function map to COINES platform
 */
BME68X_INTF_RET_TYPE bme68x_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    HAL_StatusTypeDef err;
    BME68X_INTF_RET_TYPE ret;
    uint8_t device_addr = *(uint8_t*)intf_ptr;
    memset((void *)r_buffer, 0, BUFFER_SIZE);
    memset((void *)w_buffer, 0, BUFFER_SIZE);
    w_buffer[0] = reg_addr;
    (void)intf_ptr;

    /* Write control byte */
    HAL_GPIO_WritePin(GPIOA, SPI1_CS, GPIO_PIN_RESET);
    err = HAL_SPI_TransmitReceive(&hspi1,
        w_buffer, 
        r_buffer, 
        len+1,
        portMAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, SPI1_CS, GPIO_PIN_SET);
    if(err == HAL_OK)
    {
        memcpy(reg_data, &r_buffer[1], len); /* Read starts after write of reg_addr*/
        ret = BME68X_INTF_RET_SUCCESS;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

/*!
 * SPI write function map to COINES platform
 */
BME68X_INTF_RET_TYPE bme68x_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    HAL_StatusTypeDef err;
    BME68X_INTF_RET_TYPE ret;
    uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;
    memset((void *)w_buffer, 0, BUFFER_SIZE);

    
    w_buffer[0] = reg_addr;
    memcpy((w_buffer +1), reg_data, len);

    HAL_GPIO_WritePin(GPIOA, SPI1_CS, GPIO_PIN_RESET);
    err = HAL_SPI_Transmit(&hspi1, 
        w_buffer, 
        len + 1, 
        portMAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, SPI1_CS, GPIO_PIN_SET);
    if(err == HAL_OK)
    {
        ret = BME68X_INTF_RET_SUCCESS;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

/*!
 * Delay function map to COINES platform
 */
void bme68x_delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;
    vTaskDelay(period/1000);
}

void bme68x_check_rslt(const char api_name[], int8_t rslt)
{
    switch (rslt)
    {
        case BME68X_OK:

            /* Do nothing */
            break;
        case BME68X_E_NULL_PTR:
            printf("API name [%s]  Error [%d] : Null pointer\r\n", api_name, rslt);
            break;
        case BME68X_E_COM_FAIL:
            printf("API name [%s]  Error [%d] : Communication failure\r\n", api_name, rslt);
            break;
        case BME68X_E_INVALID_LENGTH:
            printf("API name [%s]  Error [%d] : Incorrect length parameter\r\n", api_name, rslt);
            break;
        case BME68X_E_DEV_NOT_FOUND:
            printf("API name [%s]  Error [%d] : Device not found\r\n", api_name, rslt);
            break;
        case BME68X_E_SELF_TEST:
            printf("API name [%s]  Error [%d] : Self test error\r\n", api_name, rslt);
            break;
        case BME68X_W_NO_NEW_DATA:
            printf("API name [%s]  Warning [%d] : No new data found\r\n", api_name, rslt);
            break;
        default:
            printf("API name [%s]  Error [%d] : Unknown error code\r\n", api_name, rslt);
            break;
    }
}

int8_t bme68x_interface_init(struct bme68x_dev *bme, uint8_t intf)
{
    int8_t rslt = BME68X_OK;
    HAL_StatusTypeDef err;
    BME68X_INTF_RET_TYPE ret;

    if (bme != NULL)
    {

        err = MX_SPI1_Init(&hspi1);
    
        if (err != HAL_OK)
        {
            // thread_safe_printf(
            //     "\n Unable to connect with Application Board ! \n" " 1. Check if the board is connected and powered on. \n" " 2. Check if Application Board USB driver is installed. \n"
            //     " 3. Check if board is in use by another application. (Insufficient permissions to access USB) \n");
            while(1)
            {}
        }
#if defined(PC)
        setbuf(stdout, NULL);
#endif

        vTaskDelay(100);

        /* Bus configuration : SPI */
        if (intf == BME68X_SPI_INTF)
        {
            dev_addr = 0;
            bme->read = bme68x_spi_read;
            bme->write = bme68x_spi_write;
            bme->intf = BME68X_SPI_INTF;
        }

        vTaskDelay(100);

        bme->delay_us = bme68x_delay_us;
        bme->intf_ptr = &dev_addr;
        bme->amb_temp = 25; /* The ambient temperature in deg C is used for defining the heater temperature */
    }
    else
    {
        rslt = BME68X_E_NULL_PTR;
    }

    return rslt;
}

void bme68x_coines_deinit(void)
{
}