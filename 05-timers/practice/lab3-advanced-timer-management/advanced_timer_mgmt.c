#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"

static const char *TAG = "ADV_TIMERS";

static TimerHandle_t pulse_timer;
static TimerHandle_t watchdog_timer;

void pulse_cb(TimerHandle_t t)
{
    ESP_LOGI(TAG, "Pulse timer tick");
}

void watchdog_cb(TimerHandle_t t)
{
    ESP_LOGE(TAG, "Watchdog timeout! Take action");
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Advanced Timer Management Demo ===");
    pulse_timer = xTimerCreate("pulse", pdMS_TO_TICKS(200), pdTRUE, NULL, pulse_cb);
    watchdog_timer = xTimerCreate("wd", pdMS_TO_TICKS(5000), pdFALSE, NULL, watchdog_cb);
    if (!pulse_timer || !watchdog_timer) {
        ESP_LOGE(TAG, "Failed to create timers");
        return;
    }
    xTimerStart(pulse_timer, 0);
    xTimerStart(watchdog_timer, 0);

    // Simulate feeding the watchdog periodically
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(4000));
        ESP_LOGI(TAG, "Feeding watchdog");
        xTimerReset(watchdog_timer, 0);
    }
}


