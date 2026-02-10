#include "permutations.h"

void test_lifecycle() {
    printf("[UNIT] Iterator Lifecycle... ");
    int arr[] = {10, 20, 30};
    
    // Создание
    permutation_iterator_t* iter = iterator_create(ALGO_NARAYANA, arr, 3);
    assert(iter != NULL);

    // Первый вызов (должен вернуть исходный массив)
    int* p = iterator_next(iter);
    assert(p != NULL);
    assert(p[0] == 10 && p[1] == 20);

    // Уничтожение
    iterator_destroy(iter);
    printf("OK\n");
}

void test_adaptive() {
    printf("[UNIT] Adaptive Selection... ");
    
    constraint_set_t c_order = { .require_order = true }; // Нужен порядок
    constraint_set_t c_speed = { .require_order = false }; // Нужна скорость

    // Если просим порядок -> Нарайана
    assert(select_optimal_algorithm(5, &c_order) == ALGO_NARAYANA);
    
    // Если пофиг на порядок -> Хип (он быстрее)
    assert(select_optimal_algorithm(5, &c_speed) == ALGO_HEAP);

    printf("OK\n");
}

void test_bad_inputs() {
    printf("[UNIT] Error Handling... ");
    // NULL массив
    assert(iterator_create(ALGO_HEAP, NULL, 5) == NULL);
    // N = 0
    int arr[] = {1};
    assert(iterator_create(ALGO_HEAP, arr, 0) == NULL);
    
    printf("OK\n");
}

int main() {
    printf("=== RUNNING UNIT TESTS ===\n");
    test_lifecycle();
    test_adaptive();
    test_bad_inputs();
    printf("=== ALL UNIT TESTS PASSED ===\n");
    return 0;
}