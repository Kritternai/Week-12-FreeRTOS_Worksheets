#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "BIN_SEM";

static SemaphoreHandle_t sem;

void isr_simulator(void *pv)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(sem);
        ESP_LOGI(TAG, "ISR gave semaphore");
    }
}

void worker(void *pv)
{
    while (1) {
        if (xSemaphoreTake(sem, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Worker got semaphore -> do work");
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Binary Semaphore Demo ===");
    sem = xSemaphoreCreateBinary();
    if (!sem) {
        ESP_LOGE(TAG, "Failed to create semaphore");
        return;
    }
    xTaskCreate(isr_simulator, "isr_sim", 2048, NULL, 3, NULL);
    xTaskCreate(worker, "worker", 2048, NULL, 2, NULL);
}


