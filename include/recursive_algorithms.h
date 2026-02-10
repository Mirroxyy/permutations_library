#ifndef RECURSIVE_ALGORITHMS_H
#define RECURSIVE_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//Стандартный Backtrack алгоритм
void permutations_backtrack(int arr[], int n, memory_pool_t* pool, void (*callback)(int[], int))

//Рекурсивный алгоритм перестановки с помощью обменов
void permutations_recursive_swap(int arr[], int n, void (*callback)(int[], int));

//Рекурсивный алгоритм перестановки в лексиграфическом порядке
void permutations_recursive_lexicographic(int arr[], int n, memory_pool_t* pool, void (*callback)(int[], int));

//Рекурсивный алгоритм перестановки с ограничениями
void permutations_with_constraints(int arr[], int n,
                                    memory_pool_t* pool,
                                    bool (*constraint)(int[], int, int, void*),
                                    void* constraint_data,
                                    void (*callback)(int[], int));
bool pos_constraint(int partial[], int k, int next, void* data);
bool rel_constraint(int partial[], int k, int next, void* data);

//Рекурсивный алгоритм перестановки с отслеживанием повторения
void multiset_permutations(int arr[], int n, memory_pool_t* pool, void (*callback)(int[], int));

#endif