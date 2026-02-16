#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>

// Global counter for the current generation session */
static unsigned long long g_count = 0;

// Print the current state of the array and increment the counter
void print_permutation(int* arr, int n) {
    g_count++;
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

// Empty callback to increment the counter without outputting to the console
 
void quiet_callback(int* arr, int n) {
    (void)arr;
    (void)n;
    g_count++;
}

/**
* SMART MODE: 
*/
void run_smart_mode(void) {
    int n, sorted_input;

    printf("\n=== SMART MODE (ADAPTIVE) ===\n");
    printf("Enter N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid N!\n");
        return;
    }

    printf("Need lexicographic order? (1=yes, 0=no): ");
    scanf("%d", &sorted_input);

    constraint_set_t c = {
        .require_order = (sorted_input == 1),
        .max_memory_mb = 0,
        .time_limit_ms = 0
    };

    int* arr = malloc(n * sizeof(int));
    if (!arr) return;

    for (int i = 0; i < n; i++) arr[i] = i + 1;

    void (*cb)(int*, int) = (n <= 5) ? print_permutation : quiet_callback;

    g_count = 0; // Сброс счетчика перед запуском
    printf("\nRunning adaptive algorithm...\n");
    generate_permutations_adaptive(arr, n, &c, cb);

    printf("\nTotal permutations: %llu\n", g_count);
    free(arr);
}

/**
* MANUAL MODE: 
*/
void run_manual_mode(void) {
    int n, algo_id;

    printf("\n=== MANUAL MODE ===\n");
    printf("Enter N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid N!\n");
        return;
    }

    printf("Select Algorithm:\n");
    printf("1. Backtracking\n2. Recursive Swap\n3. Narayana\n4. Factorial System\n"
           "5. Johnson–Trotter\n6. Heap\n7. Minimal Change\n8. Cycle Leader\n"
           "9. Binary Masks\n10. Pseudo-Lexicographic\nEnter ID: ");

    if (scanf("%d", &algo_id) != 1 || algo_id < 1 || algo_id > 10) {
        printf("Invalid algorithm ID!\n");
        return;
    }

    int* arr = malloc(n * sizeof(int));
    if (!arr) return;

    for (int i = 0; i < n; i++) arr[i] = i + 1;

    void (*cb)(int*, int) = (n <= 5) ? print_permutation : quiet_callback;

    g_count = 0; 
    generate_permutations((permutation_algorithm_t)algo_id, arr, n, cb);

    printf("\nTotal permutations: %llu\n", g_count);
    printf("Generation finished.\n");
    printf("Visualize this algorithm? (1=yes, 0=no): ");
    int vis_choice;
    scanf("%d", &vis_choice);

    if (vis_choice == 1) {
        if (n > 5) {
            printf("N is too large for visualization! Keeping it to N=4.\n");
            visualize_algorithm_to_png((permutation_algorithm_t)algo_id, 4);
    }else {
        visualize_algorithm_to_png((permutation_algorithm_t)algo_id, n);
    }
}
    free(arr);
}

// Application entry point

int main(void) {
    int choice;

    pool_init(1024 * 1024 * 10); 

    while (1) {
        pool_reset();

        printf("\n================================\n");
        printf(" PERMUTATION LIBRARY MASTER APP \n");
        printf("================================\n");
        printf("1. Smart Mode (Adaptive)\n2. Manual Mode (Choose Algorithm)\n3. Exit\n");
        printf("Select option: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }

        switch (choice) {
            case 1: run_smart_mode(); break;
            case 2: run_manual_mode(); break;
            default: printf("Invalid choice.\n");
        }
    }

    pool_destroy();
    return 0;
}