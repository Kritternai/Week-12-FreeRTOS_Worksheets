#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "QUEUE_BASIC";

static QueueHandle_t queue;

void sender_task(void *pv)
{
    int value = 0;
    while (1) {
        value++;
        if (xQueueSend(queue, &value, pdMS_TO_TICKS(100)) == pdPASS) {
            ESP_LOGI(TAG, "Sent: %d", value);
        } else {
            ESP_LOGW(TAG, "Queue full, drop: %d", value);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void receiver_task(void *pv)
{
    int rx = 0;
    while (1) {
        if (xQueueReceive(queue, &rx, pdMS_TO_TICKS(1000)) == pdPASS) {
            ESP_LOGI(TAG, "Received: %d", rx);
        } else {
            ESP_LOGW(TAG, "Receive timeout");
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Basic Queue Demo ===");
    queue = xQueueCreate(5, sizeof(int));
    if (!queue) {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }

    xTaskCreate(sender_task, "sender", 2048, NULL, 2, NULL);
    xTaskCreate(receiver_task, "receiver", 2048, NULL, 2, NULL);
}


