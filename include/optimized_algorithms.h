#ifndef OPTIMIZED_ALGORITHMS_H
#define OPTIMIZED_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BIT_MASK_LIMIT 32

/*
// Типы данных
typedef void (*perm_callback_t)(int perm[], int n);
*/

typedef struct {
    bool use_cache_optimization;
    bool use_bit_operations;
    bool verbose_output;
    int hybrid_threshold_small;
    int hybrid_threshold_medium;
} AlgorithmConfig;

// Макросы
#define SWAP(arr, i, j) do { \
    if ((i) != (j)) { \
        int _temp = (arr)[(i)]; \
        (arr)[(i)] = (arr)[(j)]; \
        (arr)[(j)] = _temp; \
    } \
} while(0)


// Оптимизированные алгоритмы
void permutations_johnson_trotter(int arr[], int n, void (*callback)(int[], int));
void permutations_heap(int arr[], int n, void (*callback)(int[], int));
void permutations_minimal_change(int arr[], int n, void (*callback)(int[], int));
void permutations_cycle_leader(int arr[], int n, void (*callback)(int[], int));
void permutations_binary_masks(int arr[], int n, void (*callback)(int[], int));
void permutations_hybrid(int arr[], int n, void (*callback)(int[], int));

// Конфигурация
void set_algorithm_config(const AlgorithmConfig* config);
AlgorithmConfig get_algorithm_config(void);

#endif

