#include "permutations.h"

static bool stop_generation = false;

void permutations_recursive_lexicographic(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;
    
    static memory_pool_t* pool;
    size_t initial_offset = pool->offset;

    // 1. Сортируем копию, чтобы гарантировать порядок
    int* sorted_arr = (int*)pool_alloc(n * sizeof(int));
    memcpy(sorted_arr, arr, n * sizeof(int));
    qsort(sorted_arr, n, sizeof(int), compare_ints);

    // 2. Запускаем стандартный бэктрекинг
    permutations_backtrack(sorted_arr, n, callback);

    pool->offset = initial_offset;
}