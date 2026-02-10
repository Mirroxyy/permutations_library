#include "permutations.h"

// Оптимизированная гибридная версия
void permutations_hybrid_opt(int arr[], int n,  void (*callback)(int[], int)) {
    if (n <= 0) return;
    
    AlgorithmConfig config = get_algorithm_config();
    
    // Автоматический выбор алгоритма на основе n
    if (n <= config.hybrid_threshold_small) {
        permutations_binary_masks_opt(arr, n, callback);
    } else if (n <= config.hybrid_threshold_medium) {
        permutations_heap_opt(arr, n, callback);
    } else {
        permutations_johnson_trotter_opt(arr, n, callback);
    }
}

