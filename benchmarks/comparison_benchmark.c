#include "permutations.h"

static const char* algo_name(permutation_algorithm_t algo) {
    switch (algo) {
        case ALGO_BACKTRACK: return "Backtracking";
        case ALGO_RECURSIVE_SWAP: return "Recursive Swap";
        case ALGO_NARAYANA: return "Narayana";
        case ALGO_FACTORIAL_SYSTEM: return "Factorial System";
        case ALGO_JOHNSON_TROTTER: return "Johnson–Trotter";
        case ALGO_HEAP: return "Heap";
        case ALGO_MINIMAL_CHANGE: return "Minimal Change";
        case ALGO_CYCLE_LEADER: return "Cycle Leader";
        case ALGO_BINARY_MASKS: return "Binary Masks";
        case ALGO_PSEUDO_LEXICOGRAPHIC: return "Pseudo-Lexicographic";
        default: return "Unknown";
    }
}

int main() {
    pool_init(50 * 1024 * 1024);

    int n = 8;
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    permutation_algorithm_t algos[] = {
        ALGO_BACKTRACK, ALGO_RECURSIVE_SWAP, ALGO_NARAYANA,
        ALGO_FACTORIAL_SYSTEM, ALGO_JOHNSON_TROTTER, ALGO_HEAP,
        ALGO_MINIMAL_CHANGE, ALGO_CYCLE_LEADER, ALGO_BINARY_MASKS,
        ALGO_PSEUDO_LEXICOGRAPHIC
    };

    printf("=== Comparison Benchmark ===\n");
    printf("%-25s | %-12s | %-12s | %-12s\n",
           "Algorithm", "Time (s)", "Perms", "Memory (B)");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        benchmark_result_t r = benchmark_algorithm(algos[i], arr, n, 1);

        printf("%-25s | %-12.4f | %-12llu | %-12lu\n",
               algo_name(algos[i]),
               r.time_seconds,
               r.count,
               r.memory_peak);
    }

    free(arr);
    pool_destroy();
    return 0;
}
