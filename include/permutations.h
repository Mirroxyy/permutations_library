#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <stddef.h> 
#include <stdbool.h> 

// Пул памяти 
void pool_init(size_t max_bytes); // Инициализация пула с заданным размером
void* pool_alloc(size_t size);    // Выделение памяти из пула
void pool_reset();                // Сброс пула (освобождение всех выделенных блоков)
void pool_destroy();              // Уничтожение пула и освобождение всех ресурсов
size_t pool_get_peak_memory();    // Получение пикового использования памяти


// Алгоритмы
typedef enum {
    ALGO_BACKTRACK = 1,
    ALGO_RECURSIVE_SWAP,
    ALGO_NARAYANA,
    ALGO_FACTORIAL_SYSTEM,
    ALGO_JOHNSON_TROTTER,
    ALGO_HEAP,
    ALGO_MINIMAL_CHANGE,
    ALGO_CYCLE_LEADER,
    ALGO_BINARY_MASKS,
    ALGO_PSEUDO_LEXICOGRAPHIC
} permutation_algorithm_t;


// Интерфейс для генерации перестановок с помощью различных алгоритмов
typedef void (*permutation_callback_t)(int perm[], int n);

void generate_permutations(permutation_algorithm_t algo,
                           int arr[], int n,
                           permutation_callback_t callback);


// Бенчмаркинг
typedef struct {
    double time_seconds;
    unsigned long count;
    char algorithm_name[50];
} benchmark_result_t;

benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo, 
                                       int arr[], int n, 
                                       int iterations);

#endif

