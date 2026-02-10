#include <stdio.h>

#include "permutations.h"

void generate_permutations(permutation_algorithm_t algo,
                            int arr[], int n,
                            permutation_callback_t callback) {
                                
    if (arr == NULL){
        printf("Error: Передан пустой указатель на массив!\n");
        return;
    }

    if (!(n > 0)){
        printf("Error: Неккоректный размер массива\n");
        return;
    }
    
    if (!callback){
        printf("Error: Не задан Callback\n");
        return;
    }

    switch (algo) {
        case ALGO_BACKTRACK:
            printf("Запуск алгоритма BACKTRACK...\n");
            // run_backtrack(arr, n, callback);
            break;

        case ALGO_RECURSIVE_SWAP:
            printf("Запуск алгоритма RECURSIVE_SWAP...\n");
            // run_recursive_swap(arr, n, callback);
            break;

        case ALGO_NARAYANA:
            printf("Запуск алгоритма NARAYANA...\n");
            // run_narayana(arr, n, callback);
            break;

        case ALGO_FACTORIAL_SYSTEM:
            printf("Запуск алгоритма FACTORIAL_SYSTEM...\n");
            // run_factorial_system(arr, n, callback);
            break;

        case ALGO_JOHNSON_TROTTER:
            printf("Запуск алгоритма JOHNSON_TROTTER...\n");
            // run_johnson_trotter(arr, n, callback);
            break;
        
        case ALGO_HEAP:
            printf("Запуск алгоритма HEAP...\n");
            // run_heap_algorithm(arr, n, callback);
            break;

        case ALGO_MINIMAL_CHANGE:
            printf("Запуск алгоритма MINIMAL_CHANGE...\n");
            // run_minimal_change(arr, n, callback);
            break;

        case ALGO_CYCLE_LEADER:
            printf("Запуск алгоритма CYCLE_LEADER...\n");
            // run_cycle_leader(arr, n, callback);
            break;

        case ALGO_BINARY_MASKS:
            printf("Запуск алгоритма BINARY_MASKS...\n");
            // run_binary_masks(arr, n, callback);
            break;

        case ALGO_PSEUDO_LEXICOGRAPHIC:
            printf("Запуск алгоритма PSEUDO_LEXICOGRAPHIC...\n");
            // run_pseudo_lexicographic(arr, n, callback);
            break;

        default:
            printf("Error: Неизвестный алгоритм (код: %d)\n", algo);
            return;
    }
                             
}
