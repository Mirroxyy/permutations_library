#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include "permutation_types.h"
#include "permutation_core.h"

#include "iterative_algorithms.h"
#include "iterative_utils.h"
#include "recursive_algorithms.h" 
#include "optimized_algorithms.h"

// Пул памяти 
typedef struct {
    uint8_t* start_ptr;
    size_t capacity;
    size_t offset;
    size_t peak_usage;
} memory_pool_t;

void pool_init(size_t max_bytes); // Инициализация пула с заданным размером
void* pool_alloc(size_t size);    // Выделение памяти из пула
void pool_reset();                // Сброс пула (освобождение всех выделенных блоков)
void pool_destroy();              // Уничтожение пула и освобождение всех ресурсов
size_t pool_get_peak_memory();    // Получение пикового использования памяти

void generate_permutations(permutation_algorithm_t algo,
                           int arr[], int n,
                           void (*callback)(int[], int));


int compare_ints(const void* a, const void* b); //Функция для qsort

//Функции для досрочной остановки рекурсивного алгоритма
void reset_stop_flag();
void request_stop();

void print_perm(int perm[], int n); //Функция для вывода массива

#endif

