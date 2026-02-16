#ifndef PERMUTATION_CORE_H
#define PERMUTATION_CORE_H

#include <stdbool.h>
#include "permutation_types.h"   // если у тебя есть enum permutation_algorithm_t

// ------------------------------------------------------------
// 1. Forward declaration — ДОЛЖНА быть первой!
// ------------------------------------------------------------
typedef struct permutation_iterator permutation_iterator_t;

// ------------------------------------------------------------
// 2. Итератор API
// ------------------------------------------------------------
permutation_iterator_t* iterator_create(permutation_algorithm_t algo,
                                        int arr[], int n);

int* iterator_next(permutation_iterator_t* iter);

void iterator_destroy(permutation_iterator_t* iter);

// ------------------------------------------------------------
// 3. Адаптивный выбор алгоритма
// ------------------------------------------------------------
typedef struct {
    int max_memory_mb;
    bool require_order;
    int time_limit_ms;
} constraint_set_t;

permutation_algorithm_t select_optimal_algorithm(int n,
                                                 constraint_set_t* constraints);

void generate_permutations_adaptive(int arr[], int n,
                                    constraint_set_t* constraints,
                                    void (*callback)(int perm[], int n));

// ------------------------------------------------------------
// 4. Визуализация
// ------------------------------------------------------------
typedef void (*step_callback_t)(const char* description,
                                int current_perm[],
                                int n);

void visualize_algorithm_to_png(permutation_algorithm_t algo, int n);

// ------------------------------------------------------------
// 5. Юнит‑тесты
// ------------------------------------------------------------
bool core_verify_algorithm(permutation_algorithm_t algo, int n);

#endif
