#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MEM_OPT";

void app_main(void)
{
    ESP_LOGI(TAG, "=== Memory Optimization Demo ===");

    // Use heap for large buffers instead of stack
    size_t big_size = 4096;
    uint8_t *big = (uint8_t*)heap_caps_malloc(big_size, MALLOC_CAP_DEFAULT);
    if (!big) {
        ESP_LOGE(TAG, "heap_caps_malloc failed");
        return;
    }
    memset(big, 0xAA, big_size);

    // Shrink-to-fit simulation
    size_t used = 1024;
    uint8_t *resized = (uint8_t*)realloc(big, used);
    if (resized) big = resized;
    ESP_LOGI(TAG, "Resized buffer to %d bytes", (int)used);

    free(big);
    ESP_LOGI(TAG, "Freed optimized buffer");
}


