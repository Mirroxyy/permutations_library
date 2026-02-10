#include "permutations.h"

void permutations_recursive_lexicographic(int arr[], int n, memory_pool_t* pool, void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;
    
    size_t initial_offset = pool->offset;

    // 1. Сортируем копию, чтобы гарантировать порядок
    int* sorted_arr = (int*)pool_alloc(n * sizeof(int));
    memcpy(sorted_arr, arr, n * sizeof(int));
    qsort(sorted_arr, n, sizeof(int), compare_ints);

    // 2. Запускаем стандартный бэктрекинг (он сохранит порядок)
    permutations_backtrack(sorted_arr, n, pool, callback);

    pool->offset = initial_offset;
}