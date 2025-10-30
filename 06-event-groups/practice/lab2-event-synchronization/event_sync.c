#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

static const char *TAG = "EVENT_SYNC";

#define EVT_SENSOR (1<<0)
#define EVT_PROCESS (1<<1)
#define EVT_ACTUATE (1<<2)

static EventGroupHandle_t eg;

void sensor_task(void *pv)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(800));
        ESP_LOGI(TAG, "Sensor ready");
        xEventGroupSetBits(eg, EVT_SENSOR);
    }
}

void processing_task(void *pv)
{
    while (1) {
        xEventGroupWaitBits(eg, EVT_SENSOR, pdTRUE, pdTRUE, portMAX_DELAY);
        ESP_LOGI(TAG, "Processing done");
        xEventGroupSetBits(eg, EVT_PROCESS);
    }
}

void actuator_task(void *pv)
{
    while (1) {
        xEventGroupWaitBits(eg, EVT_PROCESS, pdTRUE, pdTRUE, portMAX_DELAY);
        ESP_LOGI(TAG, "Actuate!");
        xEventGroupSetBits(eg, EVT_ACTUATE);
    }
}

void orchestrator(void *pv)
{
    while (1) {
        xEventGroupWaitBits(eg, EVT_ACTUATE, pdTRUE, pdTRUE, portMAX_DELAY);
        ESP_LOGW(TAG, "Cycle complete");
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Event Synchronization Demo ===");
    eg = xEventGroupCreate();
    if (!eg) {
        ESP_LOGE(TAG, "Failed to create event group");
        return;
    }
    xTaskCreate(sensor_task, "sensor", 2048, NULL, 2, NULL);
    xTaskCreate(processing_task, "proc", 2048, NULL, 2, NULL);
    xTaskCreate(actuator_task, "act", 2048, NULL, 2, NULL);
    xTaskCreate(orchestrator, "orch", 2048, NULL, 2, NULL);
}


