#include "permutations.h"

struct permutation_iterator {
    int* current_perm;      // Current permutation
    int* aux_arr;           // Auxiliary array (c[] for Heap)
    int n;
    int state_idx;          // Index i for Heap
    permutation_algorithm_t algo;
    bool is_first;
    bool finished;
};

// Helper function for Heap iterator
static bool heap_next_step(int* arr, int n, int* c, int* i) {
    while (*i < n) {
        if (c[*i] < *i) {
            if (*i & 1) {
                swap(&arr[c[*i]], &arr[*i]);
            } else {
                swap(&arr[0], &arr[*i]);
            }
            c[*i] += 1;
            *i = 0;
            return true;
        } else {
            c[*i] = 0;
            (*i)++;
        }
    }
    return false;
}

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
        iter->state_idx = 0;
    }
    
    return iter;
}

int* iterator_next(permutation_iterator_t* iter) {
    if (!iter || iter->finished) return NULL;

    if (iter->is_first) {
        iter->is_first = false;
        return iter->current_perm;
    }

    bool has_next = false;

    switch (iter->algo) {
        case ALGO_NARAYANA:
            has_next = next_permutation_narayana(iter->current_perm, iter->n);
            break;

        case ALGO_HEAP:
            has_next = heap_next_step(iter->current_perm,
                                      iter->n,
                                      iter->aux_arr,
                                      &iter->state_idx);
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
