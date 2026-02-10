#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "permutations.h"

// Считает, сколько позиций отличается в двух массивах
int count_differences(int* a, int* b, int n) {
    int diff = 0;
    for(int i=0; i<n; i++) if(a[i] != b[i]) diff++;
    return diff;
}

void test_heap_property() {
    printf("[PROPERTY] Heap Minimal Change (Diff=2)... ");
    
    int n = 4;
    int arr[] = {1, 2, 3, 4};
    permutation_iterator_t* iter = iterator_create(ALGO_HEAP, arr, n);
    
    int* prev = (int*)malloc(n * sizeof(int));
    int* curr = iterator_next(iter); // Первая перестановка
    
    // Копируем первую
    memcpy(prev, curr, n * sizeof(int));
    
    while((curr = iterator_next(iter)) != NULL) {
        int diff = count_differences(prev, curr, n);
        
        // У Хипа ВСЕГДА меняются только 2 элемента (swap)
        if (diff != 2) {
            printf("FAIL! Diff is %d\n", diff);
            exit(1);
        }
        memcpy(prev, curr, n * sizeof(int));
    }
    
    free(prev);
    iterator_destroy(iter);
    printf("OK\n");
}

int main() {
    printf("=== RUNNING PROPERTY TESTS ===\n");
    test_heap_property();
    printf("=== ALL PROPERTY TESTS PASSED ===\n");
    return 0;
}