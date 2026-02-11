#include "permutations.h"

static void dummy_callback(int p[], int n) {
    (void)p; (void)n; 
}

benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo, 
                                       int arr[], int n, 
                                       int iterations) {
    benchmark_result_t res = {0};
    
    // Защита от дурака
    if (iterations < 1) iterations = 1;

    // Выделяем память под временный массив
    int* temp_arr = (int*)malloc(n * sizeof(int));
    if (!temp_arr) return res;

    double total_time_seconds = 0;
    
    // === ЦИКЛ ПОВТОРЕНИЙ (Твой for) ===
    for (int i = 0; i < iterations; i++) {
        
        // 1. Сбрасываем массив в исходное состояние перед каждым прогоном!
        // (Используем memcpy, это быстрее цикла)
        memcpy(temp_arr, arr, n * sizeof(int));
        
        // 2. Замеряем время
        clock_t start = clock();

        switch(algo) {
            case ALGO_BACKTRACK:
                permutations_backtrack(temp_arr, n, dummy_callback);
                break;
            case ALGO_RECURSIVE_SWAP:
                permutations_recursive_swap(temp_arr, n, dummy_callback);
                break;
            case ALGO_NARAYANA:
                permutation_narayana(temp_arr, n, dummy_callback);
                break;
            case ALGO_FACTORIAL_SYSTEM:
                permutations_factorial_system(temp_arr, n, dummy_callback);
                break;
            case ALGO_JOHNSON_TROTTER:
                permutations_johnson_trotter(temp_arr, n, dummy_callback);
                break;
            case ALGO_HEAP:
                permutations_heap(temp_arr, n, dummy_callback);
                break;
            default:
                permutation_narayana(temp_arr, n, dummy_callback);
                break;
        }

        clock_t end = clock();
        
        // Суммируем время
        total_time_seconds += (double)(end - start) / CLOCKS_PER_SEC;
    }
    // === КОНЕЦ ЦИКЛА ===

    free(temp_arr);

    // Заполняем результаты
    res.time_seconds = total_time_seconds / iterations; // Среднее время
    res.permutations_count = factorial(n); 
    
    if (res.time_seconds > 0.000000001) {
        res.perms_per_second = res.permutations_count / res.time_seconds;
    } else {
        res.perms_per_second = 0;
    }

    return res;
}

// --- 2. ADAPTIVE SELECTION ---
permutation_algorithm_t select_optimal_algorithm(int n, constraint_set_t* constraints) {
    if (constraints && constraints->require_order) return ALGO_NARAYANA;
    if (n <= 5) return ALGO_BACKTRACK;
    if (n > 5) return ALGO_HEAP; 
    return ALGO_NARAYANA; 
}

void generate_permutations_adaptive(int arr[], int n,
                                    constraint_set_t* constraints,
                                    void (*callback)(int perm[], int n)) {
    
    permutation_algorithm_t best_algo = select_optimal_algorithm(n, constraints);
    
    switch(best_algo) {
        case ALGO_BACKTRACK: permutations_backtrack(arr, n, callback); break;
        case ALGO_RECURSIVE_SWAP: permutations_recursive_swap(arr, n, callback); break;
        case ALGO_NARAYANA: permutation_narayana(arr, n, callback); break;
        case ALGO_FACTORIAL_SYSTEM: permutations_factorial_system(arr, n, callback); break;
        case ALGO_JOHNSON_TROTTER: permutations_johnson_trotter(arr, n, callback); break;
        case ALGO_HEAP: permutations_heap(arr, n, callback); break;
        default: permutation_narayana(arr, n, callback);
    }
}

// --- 3. UNIT TESTING ---
bool core_verify_algorithm(permutation_algorithm_t algo, int n) {
    unsigned long long expected = factorial(n);
    
    int* test_arr = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) test_arr[i] = i+1;

    benchmark_result_t res = benchmark_algorithm(algo, test_arr, n, 1);
    
    free(test_arr);
    // Теперь поле permutations_count видно
    return res.permutations_count == expected;
} 
// Убедись, что тут нет лишних букв после закрывающей скобки!