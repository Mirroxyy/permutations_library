#ifndef PERMUTATION_TYPES_H
#define PERMUTATION_TYPES_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// enum всех алгоритмов
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

// Структура для хранения результатов бенчмарков
typedef struct {
    unsigned long long permutations_count; // Было пропущено
    double perms_per_second;               // Было пропущено
    char algorithm_name[50];        // <--- ДОБАВЛЕНО (для названия алгоритма)
    double time_seconds;
    unsigned long long count;       // <--- ДОБАВЛЕНО (счетчик перестановок)
    unsigned long memory_peak;
} benchmark_result_t;
/*
// Интерфейс для генерации перестановок с помощью различных алгоритмов
typedef void (*permutation_callback_t)(int perm[], int n);
*/
#endif