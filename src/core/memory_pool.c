#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "memory_pool.h"

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
    if (size == 0) return NULL;

    // Memory alignment on an 8-byte boundary (memory alignment)
    // This is critical to preventing Segmentation Faults on structures and ints
    size_t align = 8;
    size_t padding = 0;
    
    if (g_pool.offset % align != 0) {
        padding = align - (g_pool.offset % align);
    }

    // Check if there is enough space given the alignment
    if (g_pool.offset + padding + size > g_pool.capacity) {
        fprintf(stderr, "ОШИБКА: Переполнение пула памяти! Нужен больший max_bytes.\n");
        return NULL; 
    }

    // Shift offset to the aligned address
    g_pool.offset += padding;
    
    // We remember the pointer that we will return to the user
    void* ptr = g_pool.start_ptr + g_pool.offset;
    
    // Reserve memory for the requested size
    g_pool.offset += size;

    // Update peak consumption
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
    g_pool.peak_usage = 0;
}

size_t pool_get_peak_memory() {
    return g_pool.peak_usage;
}