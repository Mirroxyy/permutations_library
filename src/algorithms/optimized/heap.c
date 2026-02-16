#include "permutations.h"

// Optimized version of Heap's algorithm
void permutations_heap(int arr[], int n,  void (*callback)(int[], int)) {
    if (n <= 0) return;
    
    int *perm = (int*)pool_alloc(n * sizeof(int));
    int *c = (int*)pool_alloc(n * sizeof(int));
    
    if (!perm || !c) return;
    
    // fast copy
    for (int i = 0; i < n; i++) {
        perm[i] = arr[i];
        c[i] = 0;
    }
    
    callback(perm, n);
    
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i & 1) { // Checking parity via bit operation
                SWAP(perm, c[i], i);
            } else {
                SWAP(perm, 0, i);
            }
            
            callback(perm, n);
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
}

