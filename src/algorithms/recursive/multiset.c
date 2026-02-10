#include "permutations.h"

static bool stop_generation = false;

static void multiset_helper(int arr[], int n, bool used[], int current[], int depth, void (*callback)(int[], int)) {
    if (stop_generation) return;
    if (depth == n) {
        callback(current, n);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        
        if (i > 0 && arr[i] == arr[i-1] && !used[i-1]) continue;

        used[i] = true;
        current[depth] = arr[i];
        multiset_helper(arr, n, used, current, depth + 1, callback);
        used[i] = false;
    }
}

void multiset_permutations(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;
    
    memory_pool_t* pool;
    size_t initial_offset = pool->offset;

    int* sorted_arr = (int*)pool_alloc(n * sizeof(int));
    memcpy(sorted_arr, arr, n * sizeof(int));
    qsort(sorted_arr, n, sizeof(int), compare_ints);

    bool* used = (bool*)pool_alloc(n * sizeof(bool));
    int* current = (int*)pool_alloc(n * sizeof(int));
    
    memset(used, 0, n * sizeof(bool));

    reset_stop_flag();
    multiset_helper(sorted_arr, n, used, current, 0, callback);

    pool->offset = initial_offset;
}
