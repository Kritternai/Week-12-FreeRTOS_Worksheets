#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "MUTEX_DEMO";

static SemaphoreHandle_t mutex;
static int shared_counter = 0;

void worker_task(void *pv)
{
    const char *name = (const char *)pv;
    while (1) {
        if (xSemaphoreTake(mutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
            int local = shared_counter;
            vTaskDelay(pdMS_TO_TICKS(10));
            shared_counter = local + 1;
            ESP_LOGI(TAG, "%s incremented -> %d", name, shared_counter);
            xSemaphoreGive(mutex);
        } else {
            ESP_LOGW(TAG, "%s timeout waiting mutex", name);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Mutex & Critical Section Demo ===");
    mutex = xSemaphoreCreateMutex();
    if (!mutex) {
        ESP_LOGE(TAG, "Failed to create mutex");
        return;
    }
    xTaskCreate(worker_task, "A", 2048, (void*)"A", 2, NULL);
    xTaskCreate(worker_task, "B", 2048, (void*)"B", 2, NULL);
}


