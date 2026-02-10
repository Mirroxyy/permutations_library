#include "permutations.h"

// Рекурсивная функция для битовых масок
static void generate_masks(int pos, uint32_t mask, int arr[], int n, 
                          int *current,  void (*callback)(int[], int)) {
    if (pos == n) {
        callback(current, n);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!(mask & (1u << i))) {
            current[pos] = arr[i];
            generate_masks(pos + 1, mask | (1u << i), arr, n, current, callback);
        }
    }
}

// Оптимизированная версия алгоритма двоичных масок
void permutations_binary_masks_opt(int arr[], int n,  void (*callback)(int[], int)) {
    if (n > BIT_MASK_LIMIT|| n <= 0) return;
    
    int *current = (int*)pool_alloc(n * sizeof(int));
    if (!current) return;
    
    generate_masks(0, 0, arr, n, current, callback);
}
