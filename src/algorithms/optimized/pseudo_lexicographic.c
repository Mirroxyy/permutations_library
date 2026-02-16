#include "permutations.h"
#include <string.h>

static void recursive_lex_helper(int arr[], int n, int index, void (*callback)(int[], int)) {
    if (index == n - 1) {
        callback(arr, n);
        return;
    }

    for (int i = index; i < n; i++) {
        /* Store the current element to move it to the 'index' position */
        int temp = arr[i];

        /* Shift elements to the right to maintain sorted order for the rest */
        for (int j = i; j > index; j--) {
            arr[j] = arr[j - 1];
        }
        arr[index] = temp;

        recursive_lex_helper(arr, n, index + 1, callback);

        /* Backtrack: restore original order of elements */
        for (int j = index; j < i; j++) {
            arr[j] = arr[j + 1];
        }
        arr[i] = temp;
    }
}


void permutations_recursive_lexicographic(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || !arr || !callback) return;

    /* Use pool memory for the working array copy */
    int *perm = (int*)pool_alloc(n * sizeof(int));
    if (!perm) return;

    memcpy(perm, arr, n * sizeof(int));

    recursive_lex_helper(perm, n, 0, callback);
}