#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"

static const char *TAG = "BASIC_TIMERS";

static TimerHandle_t periodic_timer;

void timer_callback(TimerHandle_t xTimer)
{
    static int tick = 0;
    ESP_LOGI(TAG, "Timer fired: %d", ++tick);
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== FreeRTOS Basic Timers Demo ===");
    periodic_timer = xTimerCreate("T1", pdMS_TO_TICKS(1000), pdTRUE, NULL, timer_callback);
    if (!periodic_timer) {
        ESP_LOGE(TAG, "Failed to create timer");
        return;
    }
    xTimerStart(periodic_timer, 0);
}


