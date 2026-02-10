#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "permutations.h" 


static unsigned long long calculate_factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    
    unsigned long long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

bool core_verify_algorithm(permutation_algorithm_t algo, int n) {
    if (n <= 0) return false;

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return false; 

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    permutation_iterator_t* iter = iterator_create(algo, arr, n);
    
    if (!iter) {
        free(arr);
        return false; 
    }

    unsigned long long count = 0;
    while (iterator_next(iter) != NULL) {
        count++;
    }

    iterator_destroy(iter);
    free(arr);

    unsigned long long expected = calculate_factorial(n);

    if (count == expected) {
        return true; 
    } else {
        return false; // Провал
    }
}

bool run_unit_tests(void) {
    return core_verify_algorithm(ALGO_HEAP, 4);
}
