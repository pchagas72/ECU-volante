#include "stopwatch.h" // Include our own header first

// All other necessary includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "ssd1306.h"

// --- Private variables and definitions ---
// These are now "private" to the stopwatch module.

static const char *TAG = "STOPWATCH";
static SSD1306_t dev; // The device handle is now managed inside this module
static QueueHandle_t time_queue;

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time_data_t;

// --- Private Functions (Tasks) ---
// By marking these tasks as 'static', they can only be seen and used inside this file.
// This is called "encapsulation" and is a core principle of good software design.

static void display_task(void *pvParameters) {
    time_data_t current_time;
    char time_str[12];

    for (;;) {
        if (xQueueReceive(time_queue, &current_time, portMAX_DELAY)) {
            snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
                     current_time.hours, current_time.minutes, current_time.seconds);
            
            ssd1306_clear_screen(&dev, false);
            ssd1306_display_text(&dev, 4, time_str, 8, false);
        }
    }
}

static void stopwatch_task(void *pvParameters) {
    time_data_t current_time = {0, 0, 0};
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);

    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        current_time.seconds++;
        if (current_time.seconds == 60) {
            current_time.seconds = 0;
            current_time.minutes++;
            if (current_time.minutes == 60) {
                current_time.minutes = 0;
                current_time.hours++;
            }
        }
        xQueueSend(time_queue, &current_time, 0);
    }
}


// --- Public Function Implementation ---

void stopwatch_start(void) {
    ESP_LOGI(TAG, "Initializing display...");
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&dev, 128, 64);
    ESP_LOGI(TAG, "Display initialized successfully.");
    
    time_queue = xQueueCreate(1, sizeof(time_data_t));
    if (time_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create queue.");
        return; // Don't create tasks if queue creation fails
    }

    xTaskCreate(stopwatch_task, "Stopwatch Task", 2048, NULL, 5, NULL);
    xTaskCreate(display_task, "Display Task", 2048, NULL, 4, NULL);

    ESP_LOGI(TAG, "Tasks created. Stopwatch is running.");
}
