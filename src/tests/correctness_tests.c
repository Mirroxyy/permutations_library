#include "permutations.h"

// Макрос для красивого вывода
#define PRINT_STATUS(name, result) \
    printf("[CORRECTNESS] Checking %-15s ... %s\n", name, (result) ? "PASS" : "FAIL")

int main() {
    printf("=== RUNNING CORRECTNESS TESTS ===\n");
    
    bool all_passed = true;

    // 1. Тестируем Нарайану (лексикографический)
    bool narayana_ok = true;
    for (int n = 3; n <= 5; n++) {
        // Вызываем функцию из src/algorithms/core/testing.c
        if (!core_verify_algorithm(ALGO_NARAYANA, n)) {
            narayana_ok = false;
            printf("    -> Failed at N=%d\n", n);
            break;
        }
    }
    PRINT_STATUS("Narayana", narayana_ok);
    if (!narayana_ok) all_passed = false;

    // 2. Тестируем Хипа (Heap's Algo)
    bool heap_ok = true;
    for (int n = 3; n <= 5; n++) {
        if (!core_verify_algorithm(ALGO_HEAP, n)) {
            heap_ok = false;
            printf("    -> Failed at N=%d\n", n);
            break;
        }
    }
    PRINT_STATUS("Heap", heap_ok);
    if (!heap_ok) all_passed = false;

    // Итог
    printf("=================================\n");
    return all_passed ? 0 : 1;
}