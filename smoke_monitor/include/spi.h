#ifndef SPI_H
#define SPI_H
#include "stm32f1xx_hal.h"

HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef * hspi );

HAL_StatusTypeDef MX_SPI2_Init(SPI_HandleTypeDef * hspi );
#endif // SPI_H