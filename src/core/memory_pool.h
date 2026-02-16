#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>
#include <stdint.h>


typedef struct {
    uint8_t* start_ptr;
    size_t capacity;
    size_t offset;
    size_t peak_usage;
} memory_pool_t;

void pool_init(size_t max_bytes); // Initializing a pool with a given size
void* pool_alloc(size_t size);    // Allocating memory from a pool
void pool_reset();                // freeing all allocated blocks
void pool_destroy();              // Destroy pool and freeing all resurs 
size_t pool_get_peak_memory();    // Get peak using memory_pool
#endif