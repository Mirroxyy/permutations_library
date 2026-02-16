#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include "permutation_types.h"
#include "permutation_core.h"
#include "benchmark.h"
#include "memory_pool.h"

#include "iterative_algorithms.h"
#include "iterative_utils.h"
#include "recursive_algorithms.h" 
#include "optimized_algorithms.h"

void generate_permutations(permutation_algorithm_t algo,
                           int arr[], int n,
                           void (*callback)(int[], int));


int compare_ints(const void* a, const void* b); //Function for qsort

//Functions for early termination of a recursive algorithm
void reset_stop_flag();
void request_stop();

void print_perm(int perm[], int n); //Function for outputting an array

void swap(int* a, int* b);

#endif

