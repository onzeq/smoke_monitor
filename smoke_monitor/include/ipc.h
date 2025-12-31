#ifndef _IPC_H_
#define _IPC_H_

#include "FreeRTOS.h"
#include <event_groups.h>
#include <queue.h>

#include <stdint.h>
#include "bme68x_defs.h"

extern EventGroupHandle_t gpioEventGroup;
extern QueueHandle_t ipc_queue;

#define SLAVE_DONE_EVENT_BIT   (1 << 0)
#define SLAVE_DONE_PIN GPIO_PIN_3
#define QUEUE_LENGTH 1

typedef struct
{
#ifndef BME68X_USE_FPU
    /*! Gas resistance in Ohms */
    uint32_t value;
#else
    float value;
#endif
} BME_RESIST_VAL_S;

typedef struct __attribute__((packed))
{
    uint8_t cmd;
    uint32_t data;
}IPC_STATUS_COMMAND_S;

void ipc_init();
void ipc_task();

#endif /* _IPC_H_ */