#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED1_PIN GPIO_NUM_2
#define LED2_PIN GPIO_NUM_4
#define BUTTON_PIN GPIO_NUM_0

static const char *TAG = "SINGLE_TASK";

void app_main(void)
{
    // GPIO Configuration for LEDs
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << LED1_PIN) | (1ULL << LED2_PIN),
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);

    // Button configuration
    gpio_config_t button_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << BUTTON_PIN,
        .pull_up_en = 1,
        .pull_down_en = 0,
    };
    gpio_config(&button_conf);

    ESP_LOGI(TAG, "Single Task System Started");
    ESP_LOGI(TAG, "LED1 (GPIO%d): Sensor simulation", LED1_PIN);
    ESP_LOGI(TAG, "LED2 (GPIO%d): Actuator simulation", LED2_PIN);
    ESP_LOGI(TAG, "Button (GPIO%d): Emergency test", BUTTON_PIN);

    while (1) {
        // Task 1: Blink LED1 (simulated sensor reading)
        ESP_LOGI(TAG, "Reading sensor...");
        gpio_set_level(LED1_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500)); // Simulate slow sensor
        gpio_set_level(LED1_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Task 2: Process data (heavy computation)
        ESP_LOGI(TAG, "Processing data...");
        for (int i = 0; i < 1000000; i++) {
            // Simulate heavy computation
            volatile int dummy = i * i;
        }

        // Task 3: Control LED2 (actuator)
        ESP_LOGI(TAG, "Controlling actuator...");
        gpio_set_level(LED2_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(300));
        gpio_set_level(LED2_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(300));

        // Task 4: Check button (emergency response)
        if (gpio_get_level(BUTTON_PIN) == 0) {
            ESP_LOGW(TAG, "Button pressed! (Delayed response)");
            // Response is delayed because other tasks run first
            gpio_set_level(LED1_PIN, 1);
            gpio_set_level(LED2_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(LED1_PIN, 0);
            gpio_set_level(LED2_PIN, 0);
        }
    }
}

