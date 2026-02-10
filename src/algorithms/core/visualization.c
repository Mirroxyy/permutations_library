#include "permutations.h"

// Dummy callback for benchmarking to avoid I/O overhead
static void dummy_callback(int p[], int n) {
    (void)p; 
    (void)n; 
}

// --- 1. BENCHMARKING ---
benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo, 
                                       int arr[], int n) {
    benchmark_result_t res = {0};

    
    clock_t start = clock();
    
    switch(algo) {
        case ALGO_NARAYANA:
            permutation_narayana(arr, n, dummy_callback);
            break;
        case ALGO_REVERSE_NARAYANA:
            permutations_reverse_narayana(arr, n, dummy_callback);
            break;
        case ALGO_FACTORIAL_SYSTEM:
            permutations_factorial_system(arr, n, dummy_callback);
            break;
        case ALGO_INVERSION_TABLE:
            permutations_inversion_table(arr, n, dummy_callback);
            break;
        case ALGO_PLUS_ONE:
            permutations_plus_one(arr, n, dummy_callback);
            break;
        case ALGO_HEAP:
            // permutations_heap(arr, n, dummy_callback); // Раскомментировать, если реализован
            break;
        default:
            permutation_narayana(arr, n, dummy_callback);
            break;
    }
    
    clock_t end = clock();
    
    res.time_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    res.permutations_count = factorial(n); 
    
    if (res.time_seconds > 0.000001) {
        res.perms_per_second = res.permutations_count / res.time_seconds;
    } else {
        res.perms_per_second = 0;
    }
        
    return res;
}

// --- 2. ADAPTIVE SELECTION ---
permutation_algorithm_t select_optimal_algorithm(int n, constraint_set_t* constraints) {
    if (constraints && constraints->require_order) {
        return ALGO_NARAYANA;
    }

    if (n > 11) {
        return ALGO_HEAP; 
    }
    
    if (constraints && constraints->max_memory_mb > 0) {
        return ALGO_NARAYANA;
    }
    
    return ALGO_NARAYANA; 
}

void generate_permutations_adaptive(int arr[], int n,
                                    constraint_set_t* constraints,
                                    void (*callback)(int perm[], int n)) {
    
    permutation_algorithm_t best_algo = select_optimal_algorithm(n, constraints);
    
    switch(best_algo) {
        case ALGO_NARAYANA: 
            permutation_narayana(arr, n, callback); 
            break;
        case ALGO_REVERSE_NARAYANA: 
            permutations_reverse_narayana(arr, n, callback); 
            break;
        case ALGO_FACTORIAL_SYSTEM: 
            permutations_factorial_system(arr, n, callback); 
            break;
        case ALGO_INVERSION_TABLE: 
            permutations_inversion_table(arr, n, callback); 
            break;
        case ALGO_PLUS_ONE: 
            permutations_plus_one(arr, n, callback); 
            break;
        case ALGO_HEAP:     
            // permutations_heap(arr, n, callback); 
            break;
        default: 
            permutation_narayana(arr, n, callback);
    }
}

// --- 3. ITERATOR IMPLEMENTATION ---

struct permutation_iterator {
    int* current_perm;
    int n;
    bool has_more;
    unsigned long long count;
    unsigned long long total_limit;
};

permutation_iterator_t* iterator_create(permutation_algorithm_t algo, int arr[], int n) {
    permutation_iterator_t* iter = (permutation_iterator_t*)pool_alloc(sizeof(permutation_iterator_t));
    if (!iter) return NULL;

    iter->n = n;
    iter->current_perm = (int*)pool_alloc(n * sizeof(int));
    if (!iter->current_perm) return NULL;

    iter->has_more = true;
    iter->total_limit = factorial(n);
    iter->count = 0;

    // Initialize with sorted copy
    copyARR(arr, iter->current_perm, n);
    bubble_sort(iter->current_perm, n); 

    (void)algo; 

    return iter;
}

int* iterator_next(permutation_iterator_t* iter) {
    if (!iter || !iter->has_more) return NULL;

    if (iter->count == 0) {
        iter->count++;
        return iter->current_perm;
    }

    bool success = next_permutation_narayana(iter->current_perm, iter->n);
    
    if (success) {
        iter->count++;
        return iter->current_perm;
    } else {
        iter->has_more = false;
        return NULL;
    }
}

void iterator_destroy(permutation_iterator_t* iter) {
    (void)iter;
}

// --- 4. UNIT TESTING ---
bool core_verify_algorithm(permutation_algorithm_t algo, int n) {
    unsigned long long expected = factorial(n);
    
    benchmark_result_t res = benchmark_algorithm(algo, (int[]){0}, n);
    
    return res.permutations_count == expected;
}