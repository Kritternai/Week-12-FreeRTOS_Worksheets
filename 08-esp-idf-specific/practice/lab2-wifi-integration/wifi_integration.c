#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "nvs_flash.h"

static const char *TAG = "WIFI_INT";

void wifi_init_task(void *pv)
{
    ESP_LOGI(TAG, "WiFi initialization task");
    
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    ESP_LOGI(TAG, "WiFi initialization done");
    vTaskDelete(NULL);
}

void network_monitor_task(void *pv)
{
    while (1) {
        ESP_LOGI(TAG, "Network monitor: Free heap=%d", esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== WiFi Integration with FreeRTOS Demo ===");
    
    // Initialize WiFi in a task
    xTaskCreate(wifi_init_task, "wifi_init", 4096, NULL, 3, NULL);
    
    // Monitor task
    xTaskCreate(network_monitor_task, "net_monitor", 2048, NULL, 2, NULL);
    
    ESP_LOGI(TAG, "WiFi integration tasks created");
}

