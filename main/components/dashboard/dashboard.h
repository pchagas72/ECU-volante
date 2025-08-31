#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// The central panel data structure
typedef struct {
    uint16_t rpm;
    uint16_t speed;
    uint8_t  soc;
    uint8_t  temp_cvt;
    uint8_t  temp_eng;
    uint8_t  flags;
    uint8_t  time_hours;
    uint8_t  time_minutes;
    uint8_t  time_seconds;
} dashboard_data_t;

// Global variables defined in main.c
extern dashboard_data_t g_dashboard_data;
extern SemaphoreHandle_t g_data_mutex;

#endif // DASHBOARD_H
