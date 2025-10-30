#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "PROD_CONS";

typedef struct {
    int id;
    int value;
} Message;

static QueueHandle_t queue;

void producer(void *pv)
{
    int seq = 0;
    Message msg;
    while (1) {
        msg.id = 1;
        msg.value = ++seq;
        if (xQueueSend(queue, &msg, pdMS_TO_TICKS(100)) == pdPASS) {
            ESP_LOGI(TAG, "Produced: id=%d val=%d", msg.id, msg.value);
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void consumer(void *pv)
{
    Message msg;
    while (1) {
        if (xQueueReceive(queue, &msg, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG, "Consumed: id=%d val=%d", msg.id, msg.value);
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Producer-Consumer Queue Demo ===");
    queue = xQueueCreate(10, sizeof(Message));
    if (!queue) {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }
    xTaskCreate(producer, "producer", 2048, NULL, 2, NULL);
    xTaskCreate(consumer, "consumer", 2048, NULL, 2, NULL);
}


