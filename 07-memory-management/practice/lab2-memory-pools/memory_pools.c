#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MEM_POOLS";

typedef struct {
    void *blocks;
    size_t block_size;
    int capacity;
    int free_count;
    uint8_t *free_bitmap;
} SimplePool;

void pool_init(SimplePool *p, int capacity, size_t block_size)
{
    p->blocks = malloc(capacity * block_size);
    p->block_size = block_size;
    p->capacity = capacity;
    p->free_count = capacity;
    p->free_bitmap = calloc(capacity, 1);
}

void *pool_alloc(SimplePool *p)
{
    for (int i = 0; i < p->capacity; i++) {
        if (!p->free_bitmap[i]) {
            p->free_bitmap[i] = 1;
            p->free_count--;
            return (uint8_t*)p->blocks + i * p->block_size;
        }
    }
    return NULL;
}

void pool_free(SimplePool *p, void *ptr)
{
    intptr_t off = (uint8_t*)ptr - (uint8_t*)p->blocks;
    int idx = off / (int)p->block_size;
    if (idx >= 0 && idx < p->capacity && p->free_bitmap[idx]) {
        p->free_bitmap[idx] = 0;
        p->free_count++;
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== Memory Pool Demo ===");
    SimplePool pool;
    pool_init(&pool, 10, 64);

    void *a = pool_alloc(&pool);
    void *b = pool_alloc(&pool);
    ESP_LOGI(TAG, "Allocated blocks, free=%d", pool.free_count);

    pool_free(&pool, a);
    pool_free(&pool, b);
    ESP_LOGI(TAG, "Freed blocks, free=%d", pool.free_count);
}


