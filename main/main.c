#include "dashboard.h"
#include "can_driver.h"
#include "stopwatch.h"
#include "ui_manager.h"

// Define global variables
dashboard_data_t g_dashboard_data = {0};
SemaphoreHandle_t g_data_mutex;

void app_main(void) {
    // Create the mutex before starting any tasks (spongebob magic clam)
    g_data_mutex = xSemaphoreCreateMutex();

    // Start all modules
    can_driver_start();
    stopwatch_start();
    ui_manager_start();
}
