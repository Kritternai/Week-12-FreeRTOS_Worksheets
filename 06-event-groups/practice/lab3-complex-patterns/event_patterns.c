#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

static const char *TAG = "EVENT_PATTERNS";

#define EVT_NET_UP   (1<<0)
#define EVT_CFG_OK   (1<<1)
#define EVT_SENSOR   (1<<2)
#define EVT_SYSTEM_READY (EVT_NET_UP|EVT_CFG_OK|EVT_SENSOR)

static EventGroupHandle_t eg;

void network_task(void *pv)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    ESP_LOGI(TAG, "Network up");
    xEventGroupSetBits(eg, EVT_NET_UP);
    vTaskDelete(NULL);
}

void config_task(void *pv)
{
    vTaskDelay(pdMS_TO_TICKS(1500));
    ESP_LOGI(TAG, "Config loaded");
    xEventGroupSetBits(eg, EVT_CFG_OK);
    vTaskDelete(NULL);
}

void sensor_init_task(void *pv)
{
    vTaskDelay(pdMS_TO_TICKS(1200));
    ESP_LOGI(TAG, "Sensor ready");
    xEventGroupSetBits(eg, EVT_SENSOR);
    vTaskDelete(NULL);
}

void startup_orchestrator(void *pv)
{
    ESP_LOGI(TAG, "Waiting for ALL prerequisites");
    xEventGroupWaitBits(eg, EVT_SYSTEM_READY, pdTRUE, pdTRUE, portMAX_DELAY);
    ESP_LOGW(TAG, "SYSTEM READY - start services");
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Event Group Complex Patterns Demo ===");
    eg = xEventGroupCreate();
    xTaskCreate(network_task, "net", 2048, NULL, 2, NULL);
    xTaskCreate(config_task, "cfg", 2048, NULL, 2, NULL);
    xTaskCreate(sensor_init_task, "sensor", 2048, NULL, 2, NULL);
    xTaskCreate(startup_orchestrator, "orch", 2048, NULL, 3, NULL);
}


