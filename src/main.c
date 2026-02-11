#include "permutations.h"

// Простой callback для вывода перестановки на экран
void print_permutation(int* arr, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Callback-пустышка (чтобы не спамить в консоль при замерах скорости)
void quiet_callback(int* arr, int n) {
    (void)arr; (void)n; // Ничего не делаем
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void run_smart_mode() {
    int n, sorted_input;
    printf("\n=== SMART MODE (ADAPTIVE) ===\n");
    printf("Enter N (size of permutation): ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid N!\n"); return; }

    printf("Do you need Sorted (Lexicographic) order? (1=Yes, 0=No): ");
    scanf("%d", &sorted_input);
    
    constraint_set_t constraints;
    constraints.require_order = (sorted_input == 1);
    constraints.max_memory_mb = 0; // Без ограничений
    constraints.time_limit_ms = 0;

    int* arr = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) arr[i] = i + 1;

    printf("\nThinking... (Checking history and heuristics)...\n");
    
    // Используем нашу "умную" функцию
    // ВАЖНО: Если N маленькое (<=5), выводим на экран. Если большое - просто считаем.
    void (*cb)(int*, int) = (n <= 5) ? print_permutation : quiet_callback;

    if (n > 5) printf("Running calculation (output suppressed for speed)...\n");

    generate_permutations_adaptive(arr, n, &constraints, cb);

    printf("\nDone! Result has been recorded to 'algo_history.dat'.\n");
    free(arr);
}

void run_manual_mode() {
    int n, algo_id;
    printf("\n=== MANUAL MODE ===\n");
    printf("Enter N: ");
    scanf("%d", &n);

    printf("Select Algorithm:\n");
    printf("0. Narayana (Lexicographic)\n");
    printf("1. Heap (Fastest)\n");
    printf("2. Johnson-Trotter\n");
    printf("Enter ID: ");
    scanf("%d", &algo_id);

    int* arr = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) arr[i] = i + 1;

    // Создаем итератор вручную
    permutation_iterator_t* iter = iterator_create((permutation_algorithm_t)algo_id, arr, n);
    
    if (!iter) {
        printf("Error: Could not create iterator (invalid algo or memory).\n");
        free(arr);
        return;
    }

    int* p;
    unsigned long long count = 0;
    while ((p = iterator_next(iter)) != NULL) {
        if (n <= 5) print_permutation(p, n);
        count++;
    }

    printf("\nTotal permutations generated: %llu\n", count);
    iterator_destroy(iter);
    free(arr);
}

int main() {
    int choice;
    while (1) {
        printf("\n================================\n");
        printf(" PERMUTATION LIBRARY MASTER APP \n");
        printf("================================\n");
        printf("1. Smart Mode (Auto-Learn)\n");
        printf("2. Manual Mode\n");
        printf("3. Exit\n");
        printf("Select option: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Очистка буфера при ошибке ввода
            continue;
        }

        switch (choice) {
            case 1: run_smart_mode(); break;
            case 2: run_manual_mode(); break;
            case 3: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}