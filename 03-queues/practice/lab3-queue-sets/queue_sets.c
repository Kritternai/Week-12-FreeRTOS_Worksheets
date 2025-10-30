#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "QUEUE_SETS";

static QueueHandle_t q1, q2;
static QueueSetHandle_t qset;

void source1(void *pv)
{
    int v = 100;
    while (1) {
        xQueueSend(q1, &v, portMAX_DELAY);
        ESP_LOGI(TAG, "q1 -> %d", v);
        v++;
        vTaskDelay(pdMS_TO_TICKS(700));
    }
}

void source2(void *pv)
{
    int v = 2000;
    while (1) {
        xQueueSend(q2, &v, portMAX_DELAY);
        ESP_LOGI(TAG, "q2 -> %d", v);
        v += 10;
        vTaskDelay(pdMS_TO_TICKS(1200));
    }
}

void mux(void *pv)
{
    QueueSetMemberHandle_t activated;
    int rx;
    while (1) {
        activated = xQueueSelectFromSet(qset, portMAX_DELAY);
        if (activated == q1 && xQueueReceive(q1, &rx, 0) == pdPASS) {
            ESP_LOGI(TAG, "from q1: %d", rx);
        } else if (activated == q2 && xQueueReceive(q2, &rx, 0) == pdPASS) {
            ESP_LOGI(TAG, "from q2: %d", rx);
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Queue Sets Demo ===");
    q1 = xQueueCreate(5, sizeof(int));
    q2 = xQueueCreate(5, sizeof(int));
    qset = xQueueCreateSet(10);
    xQueueAddToSet(q1, qset);
    xQueueAddToSet(q2, qset);

    xTaskCreate(source1, "src1", 2048, NULL, 2, NULL);
    xTaskCreate(source2, "src2", 2048, NULL, 2, NULL);
    xTaskCreate(mux, "mux", 2048, NULL, 3, NULL);
}


