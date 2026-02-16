#define _POSIX_C_SOURCE 199309L

#include "permutations.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

/**
 * Empty callback to minimize I/O overhead during performance measurements.
 */
static void dummy_callback(int p[], int n) {
    (void)p;
    (void)n;
}

benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo,
                                       int arr[], int n,
                                       int iterations)
{
    benchmark_result_t res = {0};

    if (iterations < 1) iterations = 1;
    if (n < 0) return res;

    int* temp_arr = malloc(n * sizeof(int));
    if (!temp_arr) return res; 

    unsigned long long total_time_ns = 0;

    for (int i = 0; i < iterations; i++) {
        /* Reset memory pool for each iteration to track peak memory usage accurately */
        pool_reset();
        memcpy(temp_arr, arr, n * sizeof(int));

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        /* ROUTING TO SPECIFIC ALGORITHM IMPLEMENTATIONS */
        switch (algo) {
            case ALGO_BACKTRACK:
                permutations_backtrack(temp_arr, n, dummy_callback);
                break;
            case ALGO_RECURSIVE_SWAP:
                permutations_recursive_swap(temp_arr, n, dummy_callback);
                break;
            case ALGO_NARAYANA:
                permutation_narayana(temp_arr, n, dummy_callback);
                break;
            case ALGO_FACTORIAL_SYSTEM:
                permutations_factorial_system(temp_arr, n, dummy_callback);
                break;
            case ALGO_JOHNSON_TROTTER:
                permutations_johnson_trotter(temp_arr, n, dummy_callback);
                break;
            case ALGO_HEAP:
                permutations_heap(temp_arr, n, dummy_callback);
                break;
            case ALGO_MINIMAL_CHANGE:
                permutations_minimal_change(temp_arr, n, dummy_callback);
                break;
            case ALGO_CYCLE_LEADER:
                permutations_cycle_leader(temp_arr, n, dummy_callback);
                break;
            case ALGO_BINARY_MASKS:
                permutations_binary_masks(temp_arr, n, dummy_callback);
                break;
            case ALGO_PSEUDO_LEXICOGRAPHIC:
                permutations_recursive_lexicographic(temp_arr, n, dummy_callback);
                break;
            default:
                /* No algorithm selected; time will remain effectively zero */
                break;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        unsigned long long elapsed_ns = (unsigned long long)(end.tv_sec - start.tv_sec) * 1000000000ULL + 
                                        (unsigned long long)(end.tv_nsec - start.tv_nsec);
        total_time_ns += elapsed_ns;
    }

    free(temp_arr);

    /* Calculate average time across iterations */
    res.time_seconds = (double)total_time_ns / 1000000000.0 / iterations;
    
    /* Calculate expected permutation count (N!) */
    res.count = factorial(n);
    
    /* Fetch peak memory usage recorded during the execution */
    res.memory_peak = pool_get_peak_memory();

    return res;
}