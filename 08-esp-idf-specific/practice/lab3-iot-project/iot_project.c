#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_system.h"

static const char *TAG = "IOT_PROJECT";

#define EVT_SENSOR (1<<0)
#define EVT_NETWORK (1<<1)

static QueueHandle_t sensor_queue;
static EventGroupHandle_t system_events;

typedef struct {
    float temperature;
    float humidity;
    uint32_t timestamp;
} sensor_data_t;

void sensor_task(void *pv)
{
    sensor_data_t data;
    uint32_t seq = 0;
    
    while (1) {
        data.temperature = 25.0 + (seq % 10);
        data.humidity = 60.0 + (seq % 20);
        data.timestamp = xTaskGetTickCount();
        
        if (xQueueSend(sensor_queue, &data, pdMS_TO_TICKS(100)) == pdPASS) {
            ESP_LOGI(TAG, "Sensor data sent: temp=%.1f, hum=%.1f", 
                     data.temperature, data.humidity);
        }
        
        xEventGroupSetBits(system_events, EVT_SENSOR);
        seq++;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void network_task(void *pv)
{
    sensor_data_t data;
    
    while (1) {
        if (xQueueReceive(sensor_queue, &data, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG, "Network: sending temp=%.1f, hum=%.1f to cloud", 
                     data.temperature, data.humidity);
            xEventGroupSetBits(system_events, EVT_NETWORK);
        }
    }
}

void monitor_task(void *pv)
{
    while (1) {
        EventBits_t bits = xEventGroupWaitBits(system_events, 
                                               EVT_SENSOR|EVT_NETWORK, 
                                               pdTRUE, pdTRUE, 
                                               pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "System healthy: heap=%d", esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Complete IoT Project Demo ===");
    
    sensor_queue = xQueueCreate(10, sizeof(sensor_data_t));
    system_events = xEventGroupCreate();
    
    if (!sensor_queue || !system_events) {
        ESP_LOGE(TAG, "Failed to create sync objects");
        return;
    }
    
    xTaskCreate(sensor_task, "sensor", 2048, NULL, 2, NULL);
    xTaskCreate(network_task, "network", 4096, NULL, 2, NULL);
    xTaskCreate(monitor_task, "monitor", 2048, NULL, 1, NULL);
    
    ESP_LOGI(TAG, "IoT project tasks started");
}

