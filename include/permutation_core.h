/* Core project types and utilities used across the library. */
#ifndef PERMUTATION_CORE_H
#define PERMUTATION_CORE_H

#include <stddef.h>
#include <stdint.h>

/* Simple fixed-size block memory pool.
 * Thread-unsafe, intended for internal use where many small
 * fixed-size allocations are required and freed frequently.
 */
typedef struct memory_pool {
	size_t block_size;   /* size of each block (aligned) */
	size_t block_count;  /* total number of blocks */
	void *buffer;        /* contiguous buffer holding all blocks */
	void *free_list;     /* singly-linked list of free blocks */
} memory_pool_t;

/* Initialize a memory pool.
 * - pool: pointer to memory_pool_t (caller-owned)
 * - block_size: requested size for each block in bytes
 * - block_count: number of blocks to allocate
 * Returns 0 on success, non-zero on failure.
 */
int memory_pool_init(memory_pool_t *pool, size_t block_size, size_t block_count);

/* Allocate a block from the pool. Returns NULL if pool is exhausted. */
void *memory_pool_alloc(memory_pool_t *pool);

/* Return a previously allocated block to the pool. ptr must be one
 * previously returned by memory_pool_alloc from the same pool.
 */
void memory_pool_free(memory_pool_t *pool, void *ptr);

/* Release internal resources held by the pool. Leaves `pool` in a
 * zeroed/empty state.
 */
void memory_pool_destroy(memory_pool_t *pool);

#endif /* PERMUTATION_CORE_H */

