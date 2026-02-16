#include "permutations.h"

/**
 * Performs a cyclic left shift of a sub-array.
 * [A, B, C, D] -> [B, C, D, A]
 */
static void cycle_shift_left(int arr[], int start, int end) {
    if (start >= end) return;
    int first = arr[start];
    for (int i = start; i < end; i++) {
        arr[i] = arr[i + 1];
    }
    arr[end] = first;
}

/**
 * Internal recursive generator using cyclic rotations.
 */
static void cycle_recursive(int arr[], int n, int k, void (*callback)(int[], int)) {
    if (k == 1) {
        callback(arr, n);
        return;
    }

    for (int i = 0; i < k; i++) {
        cycle_recursive(arr, n, k - 1, callback);
        
        /* Rotate the first k elements to prepare for the next subset */
        cycle_shift_left(arr, 0, k - 1);
    }
}

/**
 * Generates all permutations using the Cyclic Leader (Rotation) method.
 *
 * @param arr      The input array.
 * @param n        Size of the array.
 * @param callback Function called for each generated permutation.
 */
void permutations_cycle_leader(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || !arr || !callback) return;

    /* Create a working copy to avoid mutating the original input array */
    int *perm = (int*)pool_alloc(n * sizeof(int));
    if (!perm) return;

    for (int i = 0; i < n; i++) {
        perm[i] = arr[i];
    }

    /* Start recursion from the full size N */
    cycle_recursive(perm, n, n, callback);
}