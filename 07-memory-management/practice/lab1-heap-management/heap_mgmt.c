#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"

static const char *TAG = "HEAP_MGMT";

void app_main(void)
{
    ESP_LOGI(TAG, "=== Heap Management Demo ===");
    ESP_LOGI(TAG, "Free heap: %d", esp_get_free_heap_size());

    char *buf1 = (char*)malloc(1024);
    int *arr = (int*)malloc(200 * sizeof(int));
    if (!buf1 || !arr) {
        ESP_LOGE(TAG, "Allocation failed");
        free(buf1);
        free(arr);
        return;
    }
    memset(buf1, 'Z', 1023);
    buf1[1023] = '\0';
    for (int i = 0; i < 200; i++) arr[i] = i*i;

    ESP_LOGI(TAG, "Allocated 1KB + 800B, now free: %d", esp_get_free_heap_size());

    free(buf1);
    free(arr);
    ESP_LOGI(TAG, "Freed buffers, free heap: %d", esp_get_free_heap_size());
}


