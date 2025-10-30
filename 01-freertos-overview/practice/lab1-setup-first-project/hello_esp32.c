#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

static const char *TAG = "HELLO_ESP32";

void app_main(void)
{
    ESP_LOGI(TAG, "=== My First ESP32 Project ===");
    ESP_LOGI(TAG, "ESP-IDF Version: %s", esp_get_idf_version());
    ESP_LOGI(TAG, "Free heap: %d bytes", esp_get_free_heap_size());
    
    int counter = 0;
    while(1) {
        ESP_LOGI(TAG, "ESP32 is running... Counter: %d", counter++);
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
    }
}

