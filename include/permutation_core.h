#ifndef PERMUTATION_CORE_H
#define PERMUTATION_CORE_H

#include "permutation_types.h"

// БЕНЧМАРКИНГ
benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo, 
                                       int arr[], int n, 
                                       int iterations);

typedef struct permutation_iterator permutation_iterator_t;


// ИТЕРАТОР
permutation_iterator_t* iterator_create(permutation_algorithm_t algo, int arr[], int n);
int* iterator_next(permutation_iterator_t* iter);
void iterator_destroy(permutation_iterator_t* iter);


// АДАПТИВНЫЙ ВЫБОР АЛГОРИТМА
typedef struct {
    int max_memory_mb;     
    bool require_order;     
    int time_limit_ms;      
} constraint_set_t;

// Лучший алгоритм под условия
permutation_algorithm_t select_optimal_algorithm(int n,
                                                 constraint_set_t* constraints);

// Запуск генерации с авто-выбором
void generate_permutations_adaptive(int arr[], int n,
                                    constraint_set_t* constraints,
                                    void (*callback)(int perm[], int n));


// ЮНИТ-ТЕСТЫ
bool core_verify_algorithm(permutation_algorithm_t algo, int n);


// ВИЗУАЛИЗАЦИЯ
typedef void (*step_callback_t)(const char* description, 
                                int current_perm[], 
                                int n);

void visualize_algorithm(permutation_algorithm_t algo,
                         int arr[], int n,
                         step_callback_t step_cb);

#endif