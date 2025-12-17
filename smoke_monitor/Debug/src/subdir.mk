################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/forced_mode.c \
../src/main.c \
../src/spi.c 

OBJS += \
./src/forced_mode.o \
./src/main.o \
./src/spi.o 

C_DEPS += \
./src/forced_mode.d \
./src/main.d \
./src/spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/src/git/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/src/git/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/src/git/smoke_monitor/smoke_monitor/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/src/git/smoke_monitor/smoke_monitor/3rdParty/BME68x_SensorAPI" -I"C:/src/git/smoke_monitor/smoke_monitor/include" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/forced_mode.cyclo ./src/forced_mode.d ./src/forced_mode.o ./src/forced_mode.su ./src/main.cyclo ./src/main.d ./src/main.o ./src/main.su ./src/spi.cyclo ./src/spi.d ./src/spi.o ./src/spi.su

.PHONY: clean-src

