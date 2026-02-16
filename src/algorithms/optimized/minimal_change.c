#include "permutations.h"

void permutations_minimal_change(int arr[], int n, void (*callback)(int[], int)) {
    if (n <= 0 || !arr || !callback) return;

    if (n == 1) {
        callback(arr, n);
        return;
    }

    /* Allocate state buffers from the memory pool */
    int *p = (int*)pool_alloc(n * sizeof(int));     // Current permutation
    int *pos = (int*)pool_alloc(n * sizeof(int));   // Positions of elements 1..N
    int *dir = (int*)pool_alloc(n * sizeof(int));   // Directions: -1 (left), 1 (right)

    if (!p || !pos || !dir) return;

    /* Initialize state: p = [1..N], all directions pointing left */
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        pos[i] = i;
        dir[i] = -1;
    }

    callback(p, n);

    while (1) {
        int mobile = -1;
        int mobile_val = -1;

        /* Find the largest mobile element */
        for (int i = 0; i < n; i++) {
            int val = i + 1;
            int next_pos = pos[i] + dir[i];

            if (next_pos >= 0 && next_pos < n) {
                if (p[next_pos] < val) {
                    if (val > mobile_val) {
                        mobile_val = val;
                        mobile = i;
                    }
                }
            }
        }

        /* Termination condition: no mobile elements found */
        if (mobile == -1) break;

        /* Swap the mobile element with its neighbor in current direction */
        int p1 = pos[mobile];
        int p2 = p1 + dir[mobile];

        int tmp = p[p1];
        p[p1] = p[p2];
        p[p2] = tmp;

        /* Update position records for the swapped elements */
        pos[p[p1] - 1] = p1;
        pos[p[p2] - 1] = p2;

        callback(p, n);

        /* Reverse directions of all elements larger than the current mobile value */
        for (int i = 0; i < n; i++) {
            if (i + 1 > mobile_val) {
                dir[i] = -dir[i];
            }
        }
    }
}