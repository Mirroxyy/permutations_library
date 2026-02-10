#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "permutations.h"         


static unsigned long long g_counter = 0;

// Callback для подсчета количества перестановок
void counter_callback(int perm[], int n) {
    (void)perm;
    (void)n;
    g_counter++;
}

// Вспомогательная функция для получения имени алгоритма
const char* get_algo_name(permutation_algorithm_t algo) {
    switch(algo) {
        case ALGO_BACKTRACK: return "Backtrack";
        case ALGO_RECURSIVE_SWAP: return "Recursive Swap";
        case ALGO_NARAYANA: return "Narayana";
        case ALGO_FACTORIAL_SYSTEM: return "Factorial System";
        case ALGO_JOHNSON_TROTTER: return "Johnson-Trotter";
        case ALGO_HEAP: return "Heap's Algorithm";
        case ALGO_MINIMAL_CHANGE: return "Minimal Change";
        case ALGO_CYCLE_LEADER: return "Cycle Leader";
        case ALGO_BINARY_MASKS: return "Binary Masks";
        case ALGO_PSEUDO_LEXICOGRAPHIC: return "Pseudo Lexicographic";
        default: return "Unknown Algorithm";
    }
}

// Основная функция бенчмаркинга
benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo, 
                                       int arr[], int n, 
                                       int iterations) {
    benchmark_result_t result;

    double total_time = 0.0;
    size_t max_peak_memory = 0
    
    strncpy(result.algorithm_name, get_algo_name(algo), 49);
    result.algorithm_name[49] = '\0';

    for (int i = 0; i < iterations; i++) {
        pool_reset();
        g_counter = 0;

        clock_t start = clock();
        
        generate_permutations(algo, arr, n, counter_callback);
        
        clock_t end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;

        size_t current_peak = pool_get_peak_memory();
        if (current_peak > max_peak_memory) {
            max_peak_memory = current_peak;
        }
    }

    result.time_seconds = total_time / iterations; // Среднее время
    result.count = g_counter;
    result.memory_peak = max_peak_memory;

    return result;
}