################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/BME68x_SensorAPI/bme68x.c 

OBJS += \
./3rdParty/BME68x_SensorAPI/bme68x.o 

C_DEPS += \
./3rdParty/BME68x_SensorAPI/bme68x.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/BME68x_SensorAPI/%.o 3rdParty/BME68x_SensorAPI/%.su 3rdParty/BME68x_SensorAPI/%.cyclo: ../3rdParty/BME68x_SensorAPI/%.c 3rdParty/BME68x_SensorAPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"/home/jake/projects/Rauch_Logger/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/jake/projects/Rauch_Logger/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/jake/projects/Rauch_Logger/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/jake/projects/Rauch_Logger/smoke_monitor/smoke_monitor/3rdParty/BME68x_SensorAPI" -I"/home/jake/projects/Rauch_Logger/smoke_monitor/smoke_monitor/include" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-3rdParty-2f-BME68x_SensorAPI

clean-3rdParty-2f-BME68x_SensorAPI:
	-$(RM) ./3rdParty/BME68x_SensorAPI/bme68x.cyclo ./3rdParty/BME68x_SensorAPI/bme68x.d ./3rdParty/BME68x_SensorAPI/bme68x.o ./3rdParty/BME68x_SensorAPI/bme68x.su

.PHONY: clean-3rdParty-2f-BME68x_SensorAPI

