#include "stopwatch.h"
#include "dashboard.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"

static const char *TAG = "STOPWATCH";

static void stopwatch_timer_callback(TimerHandle_t xTimer){

    // Take the "Magic Conch" (mutex) to safely access the shared data
    if (xSemaphoreTake(g_data_mutex, pdMS_TO_TICKS(10)) == pdTRUE) {
        // --- Updated clock, critical section ---
        g_dashboard_data.time_seconds++;
        if (g_dashboard_data.time_seconds >= 60) {
            g_dashboard_data.time_seconds = 0;
            g_dashboard_data.time_minutes++;
            if (g_dashboard_data.time_minutes >= 60) {
                g_dashboard_data.time_minutes = 0;
                g_dashboard_data.time_hours++;
            }
        }
        // --- End of critical section ---

        // Give the mutex back so other tasks can use the data
        xSemaphoreGive(g_data_mutex);
    }
}

void stopwatch_start(void) {
    ESP_LOGI(TAG, "Starting software timer for stopwatch...");

    // Create a new FreeRTOS Software Timer
    TimerHandle_t stopwatch_timer = xTimerCreate(
            "StopwatchTimer",         // A name for the timer (for debugging)
            pdMS_TO_TICKS(1000),      // The timer period in ticks (1000ms = 1s)
            pdTRUE,                   // Set to pdTRUE for an auto-reloading (periodic) timer
            NULL,                     // A timer ID (we don't need one)
            stopwatch_timer_callback  // The function to call when the timer expires
            );

    // Start the timer. It will now call our callback function every second.
    if (stopwatch_timer != NULL && xTimerStart(stopwatch_timer, 0) == pdPASS) {
        ESP_LOGI(TAG, "Stopwatch timer started successfully.");
    } else {
        ESP_LOGE(TAG, "Failed to start stopwatch timer!");
    }
}
