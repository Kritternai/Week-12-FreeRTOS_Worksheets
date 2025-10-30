#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

static const char *TAG = "BASIC_EVENTS";

#define EVT_BIT_A (1<<0)
#define EVT_BIT_B (1<<1)

static EventGroupHandle_t eg;

void setter_a(void *pv)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupSetBits(eg, EVT_BIT_A);
        ESP_LOGI(TAG, "Set A");
    }
}

void setter_b(void *pv)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1500));
        xEventGroupSetBits(eg, EVT_BIT_B);
        ESP_LOGI(TAG, "Set B");
    }
}

void waiter_any(void *pv)
{
    while (1) {
        EventBits_t bits = xEventGroupWaitBits(eg, EVT_BIT_A|EVT_BIT_B, pdTRUE, pdFALSE, portMAX_DELAY);
        ESP_LOGI(TAG, "ANY got: 0x%02x", bits);
    }
}

void waiter_all(void *pv)
{
    while (1) {
        EventBits_t bits = xEventGroupWaitBits(eg, EVT_BIT_A|EVT_BIT_B, pdTRUE, pdTRUE, portMAX_DELAY);
        ESP_LOGI(TAG, "ALL got both: 0x%02x", bits);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Basic Event Groups Demo ===");
    eg = xEventGroupCreate();
    if (!eg) {
        ESP_LOGE(TAG, "Failed to create event group");
        return;
    }
    xTaskCreate(setter_a, "setA", 2048, NULL, 2, NULL);
    xTaskCreate(setter_b, "setB", 2048, NULL, 2, NULL);
    xTaskCreate(waiter_any, "any", 2048, NULL, 2, NULL);
    xTaskCreate(waiter_all, "all", 2048, NULL, 2, NULL);
}


