#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "permutations.h"

static memory_pool_t g_pool = {NULL, 0, 0, 0};

void pool_init(size_t max_bytes) {
    if (g_pool.start_ptr != NULL) {
        free(g_pool.start_ptr);
    }
    
    g_pool.start_ptr = (uint8_t*)malloc(max_bytes);
    if (g_pool.start_ptr == NULL) {
        fprintf(stderr, "КРИТИЧЕСКАЯ ОШИБКА: Не удалось выделить пул памяти!\n");
        exit(1);
    }
    
    g_pool.capacity = max_bytes;
    g_pool.offset = 0;
    g_pool.peak_usage = 0;
}

void* pool_alloc(size_t size) {
    if (g_pool.offset + size > g_pool.capacity) {
        fprintf(stderr, "ОШИБКА: Переполнение пула памяти!\n");
        return NULL; 
    }

    void* ptr = g_pool.start_ptr + g_pool.offset;
    g_pool.offset += size;

    if (g_pool.offset > g_pool.peak_usage) {
        g_pool.peak_usage = g_pool.offset;
    }

    return ptr;
}

void pool_reset() {
    g_pool.offset = 0;
}

void pool_destroy() {
    if (g_pool.start_ptr) {
        free(g_pool.start_ptr);
        g_pool.start_ptr = NULL;
    }
    g_pool.offset = 0;
    g_pool.capacity = 0;
}

size_t pool_get_peak_memory() {
    return g_pool.peak_usage;
}