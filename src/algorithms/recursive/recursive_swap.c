#include "permutations.h"

static void swap_helper(int arr[], int n, int depth, void (*callback)(int[], int)) {
    if (stop_generation) return;

    if (depth == n - 1) {
        callback(arr, n);
        return;
    }

    for (int i = depth; i < n; i++) {
        swap(&arr[depth], &arr[i]);
        swap_helper(arr, n, depth + 1, callback);
        swap(&arr[depth], &arr[i]); // Backtrack
    }
}

void permutations_recursive_swap(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;
    reset_stop_flag();
    swap_helper(arr, n, 0, callback);
}

