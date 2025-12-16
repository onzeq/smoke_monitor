################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/freertos/Src/croutine.c \
../3rdParty/freertos/Src/event_groups.c \
../3rdParty/freertos/Src/heap_3.c \
../3rdParty/freertos/Src/list.c \
../3rdParty/freertos/Src/port.c \
../3rdParty/freertos/Src/queue.c \
../3rdParty/freertos/Src/stream_buffer.c \
../3rdParty/freertos/Src/tasks.c \
../3rdParty/freertos/Src/timers.c 

OBJS += \
./3rdParty/freertos/Src/croutine.o \
./3rdParty/freertos/Src/event_groups.o \
./3rdParty/freertos/Src/heap_3.o \
./3rdParty/freertos/Src/list.o \
./3rdParty/freertos/Src/port.o \
./3rdParty/freertos/Src/queue.o \
./3rdParty/freertos/Src/stream_buffer.o \
./3rdParty/freertos/Src/tasks.o \
./3rdParty/freertos/Src/timers.o 

C_DEPS += \
./3rdParty/freertos/Src/croutine.d \
./3rdParty/freertos/Src/event_groups.d \
./3rdParty/freertos/Src/heap_3.d \
./3rdParty/freertos/Src/list.d \
./3rdParty/freertos/Src/port.d \
./3rdParty/freertos/Src/queue.d \
./3rdParty/freertos/Src/stream_buffer.d \
./3rdParty/freertos/Src/tasks.d \
./3rdParty/freertos/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/freertos/Src/%.o 3rdParty/freertos/Src/%.su 3rdParty/freertos/Src/%.cyclo: ../3rdParty/freertos/Src/%.c 3rdParty/freertos/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/src/git/smoke_monitor/smoke_monitor/3rdParty/BME68x_SensorAPI" -I"C:/src/git/smoke_monitor/smoke_monitor/include" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/src/git/smoke_monitor/smoke_monitor/freertos/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-3rdParty-2f-freertos-2f-Src

clean-3rdParty-2f-freertos-2f-Src:
	-$(RM) ./3rdParty/freertos/Src/croutine.cyclo ./3rdParty/freertos/Src/croutine.d ./3rdParty/freertos/Src/croutine.o ./3rdParty/freertos/Src/croutine.su ./3rdParty/freertos/Src/event_groups.cyclo ./3rdParty/freertos/Src/event_groups.d ./3rdParty/freertos/Src/event_groups.o ./3rdParty/freertos/Src/event_groups.su ./3rdParty/freertos/Src/heap_3.cyclo ./3rdParty/freertos/Src/heap_3.d ./3rdParty/freertos/Src/heap_3.o ./3rdParty/freertos/Src/heap_3.su ./3rdParty/freertos/Src/list.cyclo ./3rdParty/freertos/Src/list.d ./3rdParty/freertos/Src/list.o ./3rdParty/freertos/Src/list.su ./3rdParty/freertos/Src/port.cyclo ./3rdParty/freertos/Src/port.d ./3rdParty/freertos/Src/port.o ./3rdParty/freertos/Src/port.su ./3rdParty/freertos/Src/queue.cyclo ./3rdParty/freertos/Src/queue.d ./3rdParty/freertos/Src/queue.o ./3rdParty/freertos/Src/queue.su ./3rdParty/freertos/Src/stream_buffer.cyclo ./3rdParty/freertos/Src/stream_buffer.d ./3rdParty/freertos/Src/stream_buffer.o ./3rdParty/freertos/Src/stream_buffer.su ./3rdParty/freertos/Src/tasks.cyclo ./3rdParty/freertos/Src/tasks.d ./3rdParty/freertos/Src/tasks.o ./3rdParty/freertos/Src/tasks.su ./3rdParty/freertos/Src/timers.cyclo ./3rdParty/freertos/Src/timers.d ./3rdParty/freertos/Src/timers.o ./3rdParty/freertos/Src/timers.su

.PHONY: clean-3rdParty-2f-freertos-2f-Src

