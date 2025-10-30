#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"

static const char *TAG = "TIMER_APPS";

static TimerHandle_t one_shot;
static TimerHandle_t periodic;

void one_shot_cb(TimerHandle_t xTimer)
{
    ESP_LOGW(TAG, "One-shot fired");
}

void periodic_cb(TimerHandle_t xTimer)
{
    static int cnt = 0;
    ESP_LOGI(TAG, "Periodic fired %d", ++cnt);
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Timer Applications Demo ===");
    one_shot = xTimerCreate("oneshot", pdMS_TO_TICKS(3000), pdFALSE, NULL, one_shot_cb);
    periodic = xTimerCreate("period", pdMS_TO_TICKS(1000), pdTRUE, NULL, periodic_cb);
    if (!one_shot || !periodic) {
        ESP_LOGE(TAG, "Failed to create timers");
        return;
    }
    xTimerStart(one_shot, 0);
    xTimerStart(periodic, 0);
}


