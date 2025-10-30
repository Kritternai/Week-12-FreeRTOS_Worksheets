#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "COUNT_SEM";

static SemaphoreHandle_t count_sem;

void producer(void *pv)
{
    while (1) {
        xSemaphoreGive(count_sem);
        ESP_LOGI(TAG, "Produced token");
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void consumer(void *pv)
{
    while (1) {
        if (xSemaphoreTake(count_sem, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Consumed token");
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Counting Semaphore Demo ===");
    count_sem = xSemaphoreCreateCounting(5, 0);
    if (!count_sem) {
        ESP_LOGE(TAG, "Failed to create counting semaphore");
        return;
    }
    xTaskCreate(producer, "producer", 2048, NULL, 2, NULL);
    xTaskCreate(consumer, "consumer", 2048, NULL, 2, NULL);
}


