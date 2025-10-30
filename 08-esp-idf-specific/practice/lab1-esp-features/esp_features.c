#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_chip_info.h"

static const char *TAG = "ESP_FEATURES";

void task_core0(void *pv)
{
    ESP_LOGI(TAG, "Task running on Core 0");
    while (1) {
        ESP_LOGI(TAG, "Core 0: tick=%d", xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_core1(void *pv)
{
    ESP_LOGI(TAG, "Task running on Core 1");
    while (1) {
        ESP_LOGI(TAG, "Core 1: tick=%d", xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== ESP-IDF Specific Features Demo ===");
    
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "Chip: %s", CONFIG_IDF_TARGET);
    ESP_LOGI(TAG, "Cores: %d", chip_info.cores);
    ESP_LOGI(TAG, "Features: 0x%x", chip_info.features);
    
    // Pin tasks to specific cores
    xTaskCreatePinnedToCore(task_core0, "core0_task", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(task_core1, "core1_task", 2048, NULL, 2, NULL, 1);
    
    ESP_LOGI(TAG, "Tasks created with core affinity");
}

