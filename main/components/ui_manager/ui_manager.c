#include "ui_manager.h"
#include "dashboard.h" // We need access to the shared data

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "UI_MANAGER";

static void ui_manager_task(void *pvParameters)
{
    // This task will periodically print the current time to the log for now.
    for (;;) {
        // Two seconds delay
        vTaskDelay(pdMS_TO_TICKS(2000));

        uint8_t hours, minutes, seconds;

        // Takes the mutex to safely read the shared data (spongebob magic clam)
        if (xSemaphoreTake(g_data_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            // Make a local copy of the time
            hours = g_dashboard_data.time_hours;
            minutes = g_dashboard_data.time_minutes;
            seconds = g_dashboard_data.time_seconds;
            
            // Give the mutex back
            xSemaphoreGive(g_data_mutex);

            ESP_LOGI(TAG, "Current time from dashboard: %02d:%02d:%02d", hours, minutes, seconds);
        }
    }
}


void ui_manager_start(void) {
    ESP_LOGI(TAG, "UI Manager module started.");
    
    // For now, we just create a temporary task to log the time.
    // In the future, this will initialize displays and create the real UI task.
    xTaskCreate(ui_manager_task, "UITask", 3072, NULL, 5, NULL);
}
