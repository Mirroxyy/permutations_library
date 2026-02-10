#include "../include/permutations.h"
// Добавь #include ...

unsigned long long calc_factorial(int n) {
    unsigned long long f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

void run_comparison_benchmark() {
    int n = 11;
    unsigned long long total_perms = calc_factorial(n);
    int* arr = (int*)pool_alloc(n * sizeof(int));
    
    struct {
        permutation_algorithm_t algo;
        const char* name;
    } contenders[] = {
        {ALGO_NARAYANA, "Narayana"},
        {ALGO_REVERSE_NARAYANA, "Rev. Narayana"},
        {ALGO_HEAP, "Heap"},
        {ALGO_FACTORIAL_SYSTEM, "Factorial"},
        {ALGO_INVERSION_TABLE, "Inversion"},
        {ALGO_PLUS_ONE, "PlusOne"},
        {ALGO_BINARY_MASKS, "BinMasks"} 
    };

    int count = sizeof(contenders) / sizeof(contenders[0]);

    printf("--- Algo Comparison (N=%d, Count=%llu) ---\n", n, total_perms);

    for (int i = 0; i < count; i++) {
        for(int k=0; k<n; k++) arr[k] = k;

        benchmark_result_t res = benchmark_algorithm(contenders[i].algo, arr, n);
        
        // Считаем скорость сами: Факториал / Время
        unsigned long long pps = (res.time_seconds > 0.0001) ? 
                                 (unsigned long long)(total_perms / res.time_seconds) : 0;

        printf("%-15s: %.4fs (%llu ops/sec)\n", 
               contenders[i].name, 
               res.time_seconds, 
               pps);
    }
}

int main() {
    pool_init(1024 * 1024 * 50);
    run_comparison_benchmark();
    pool_destroy();
    return 0;
}