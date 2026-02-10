#include "permutations.h"

static bool stop_generation = false;

static void backtrack_helper(int arr[], int n, bool used[], int current[], int depth, void (*callback)(int[], int)) {
    if (stop_generation) return;

    if (depth == n) {
        callback(current, n);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            current[depth] = arr[i];
            backtrack_helper(arr, n, used, current, depth + 1, callback);
            used[i] = false; // Backtrack
        }
    }
}

void permutations_backtrack(int arr[], int n, memory_pool_t* pool, void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;
    if (n == 1){  callback(arr, n); return;} 

    size_t initial_offset = pool->offset;

    bool* used = (bool*)pool_alloc(n * sizeof(bool));
    int* current = (int*)pool_alloc(n * sizeof(int));

    memset(used, 0, n * sizeof(bool));

    reset_stop_flag();
    backtrack_helper(arr, n, used, current, 0, callback);

    pool->offset = initial_offset;
}