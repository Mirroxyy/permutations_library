#include "permutations.h"

// 1. Проверка на утечки (многократное создание/удаление)
void test_memory_leaks() {
    printf("[STRESS] Memory Leak Check (5000 cycles)... ");
    int arr[] = {1, 2, 3, 4, 5};
    
    for(int i=0; i<5000; i++) {
        permutation_iterator_t* iter = iterator_create(ALGO_HEAP, arr, 5);
        if (!iter) {
            printf("FAIL: Memory exhausted!\n");
            exit(1);
        }
        // Делаем пару шагов
        iterator_next(iter);
        iterator_next(iter);
        
        // Главное — корректно удалить
        iterator_destroy(iter);
    }
    printf("OK\n");
}

// 2. Проверка скорости (без вывода в консоль, только счет)
void test_performance() {
    int n = 10; // 3,628,800 перестановок
    printf("[STRESS] Performance Check (N=%d)... ", n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) arr[i] = i;

    clock_t start = clock();
    
    permutation_iterator_t* iter = iterator_create(ALGO_HEAP, arr, n);
    unsigned long long count = 0;
    while(iterator_next(iter)) {
        count++;
    }
    iterator_destroy(iter);
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Done.\n    -> Generated %llu permutations in %.3f sec\n", count, time_taken);
    free(arr);
}

int main() {
    printf("=== RUNNING STRESS TESTS ===\n");
    test_memory_leaks();
    test_performance();
    printf("=== STRESS TESTS FINISHED ===\n");
    return 0;
}