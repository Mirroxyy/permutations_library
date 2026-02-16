#ifndef BENCHMARK_H
#define BENCHMARK_H

typedef struct {
    unsigned long long count;
    double time_seconds;
    unsigned long memory_peak;
} benchmark_result_t;

benchmark_result_t benchmark_algorithm(permutation_algorithm_t algo,
                                       int arr[], int n,
                                       int iterations);

#endif

