#include "permutations.h"

// Оптимизированная версия алгоритма минимальных изменений
void permutations_minimal_change_opt(int arr[], int n,  void (*callback)(int[], int)) {
    if (n <= 1) {
        if (n == 1) callback(arr, n);
        return;
    }
    
    int *a = (int*)pool_alloc(n * sizeof(int));
    int *b = (int*)pool_alloc(n * sizeof(int));
    char *c = (char*)pool_alloc(n * sizeof(char));
    
    if (!a || !b || !c) return;
    
    // Инициализация
    for (int i = 0; i < n; i++) {
        a[i] = arr[i];
        b[i] = 0;
        c[i] = 1;
    }
    
    callback(a, n);
    
    int k = 0;
    while (k < n) {
        b[k] += c[k];
        int j = b[k];
        
        if (j < 0 || j > k) {
            c[k] = -c[k];
            k = 0;
            continue;
        }
        
        if (j <= k) {
            SWAP(a, j, j + 1);
        }
        
        callback(a, n);
        
        if (b[k] == 0 || b[k] == k) {
            c[k] = -c[k];
            k = 0;
        } else {
            k++;
        }
    }
}

