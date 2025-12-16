################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bme680/common.c 

OBJS += \
./src/bme680/common.o 

C_DEPS += \
./src/bme680/common.d 


# Each subdirectory must supply rules for building sources it contributes
src/bme680/%.o src/bme680/%.su src/bme680/%.cyclo: ../src/bme680/%.c src/bme680/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/src/git/smoke_monitor/smoke_monitor/3rdParty/BME68x_SensorAPI" -I"C:/src/git/smoke_monitor/smoke_monitor/include" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/src/git/smoke_monitor/smoke_monitor/freertos/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-bme680

clean-src-2f-bme680:
	-$(RM) ./src/bme680/common.cyclo ./src/bme680/common.d ./src/bme680/common.o ./src/bme680/common.su

.PHONY: clean-src-2f-bme680

