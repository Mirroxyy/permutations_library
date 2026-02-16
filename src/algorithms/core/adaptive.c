#include "permutations.h"

permutation_algorithm_t select_optimal_algorithm(int n, constraint_set_t* constraints) {
    bool need_lex = false;
    bool mem_limit = false;

    if (constraints) {
        need_lex = constraints->require_order;
        if (constraints->max_memory_mb > 0 && constraints->max_memory_mb < 2) {
            mem_limit = true;
        }
    }

    if (need_lex) {
        return ALGO_NARAYANA;
    }

    if (mem_limit || n > 10) {
        return ALGO_HEAP;
    }

    return ALGO_HEAP;
}

void generate_permutations_adaptive(int arr[], int n,
                                    constraint_set_t* constraints,
                                    void (*callback)(int perm[], int n))
{
    if (!arr || n <= 0 || !callback) return;

    // Algorithm selection
    permutation_algorithm_t algo = select_optimal_algorithm(n, constraints);

    // Creating an Iterator
    permutation_iterator_t* iter = iterator_create(algo, arr, n);

    // Fallback if the selected algorithm is not supported
    if (!iter) {
        iter = iterator_create(ALGO_NARAYANA, arr, n);
        if (!iter) return; // if bad, exit
    }

    // Iteration
    int* p;
    while ((p = iterator_next(iter)) != NULL) {
        callback(p, n);
    }

    iterator_destroy(iter);
}
