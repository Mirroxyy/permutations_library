#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#include "permutations.h"


static bool stub_narayana_next(int* arr, int n) {
    (void)arr; (void)n;
    return false;  // Студент 2 реализует это
}

static bool stub_heap_next(int* arr, int n, int* c, int* i) {
    (void)arr; (void)n; (void)c; (void)i;
    return false; // Студент 3 реализует это
}

struct permutation_iterator {
    int* current_perm;      // Текущая перестановка
    int* aux_arr;           // Вспомогательный массив (c[] для Heap)
    int n;
    int state_idx;          // Индекс i для Heap
    permutation_algorithm_t algo;
    bool is_first;
    bool finished;
};

permutation_iterator_t* iterator_create(permutation_algorithm_t algo, 
                                           int arr[], int n) {
    if (n <= 0 || !arr) return NULL;

    if (algo == ALGO_BACKTRACK || algo == ALGO_RECURSIVE_SWAP) {
        return NULL;
    }
    
    permutation_iterator_t* iter = (permutation_iterator_t*)malloc(sizeof(struct permutation_iterator));
    if (!iter) return NULL;

    iter->n = n;
    iter->algo = algo;
    iter->is_first = true;
    iter->finished = false;
    iter->state_idx = 0;
    iter->aux_arr = NULL;

    iter->current_perm = (int*)malloc(n * sizeof(int));
    if (!iter->current_perm) {
        free(iter); 
        return NULL;
    }
    memcpy(iter->current_perm, arr, n * sizeof(int));

    if (algo == ALGO_HEAP) {
        iter->aux_arr = (int*)malloc(n * sizeof(int));
        if (!iter->aux_arr) {
            free(iter->current_perm);
            free(iter);
            return NULL;
        }
        memset(iter->aux_arr, 0, n * sizeof(int));
    }
    
    return iter;
}

int* iterator_next(permutation_iterator_t* iter) {
    if (!iter || iter->finished) return NULL;

    // Первый вызов — возвращаем то, с чего начали
    if (iter->is_first) {
        iter->is_first = false;
        return iter->current_perm;
    }

    bool has_next = false;

    // Диспетчер алгоритмов
    switch (iter->algo) {
        case ALGO_NARAYANA:
            has_next = stub_narayana_next(iter->current_perm, iter->n);
            break;

        case ALGO_HEAP:
            has_next = stub_heap_next(iter->current_perm, iter->n, 
                                      iter->aux_arr, &iter->state_idx);
            break;

        default:
            has_next = false;
            break;
    }

    if (!has_next) {
        iter->finished = true;
        return NULL;
    }

    return iter->current_perm;
}

void iterator_destroy(permutation_iterator_t* iter) {
    if (iter) {
        if (iter->current_perm) free(iter->current_perm);
        if (iter->aux_arr) free(iter->aux_arr);
        free(iter);
    }
}