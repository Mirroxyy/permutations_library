#include "permutations.h"

// Оптимизированная версия алгоритма циклических лидеров
void permutations_cycle_leader(int arr[], int n,  void (*callback)(int[], int)) {
    if (n <= 1) {
        if (n == 1) callback(arr, n);
        return;
    }
    
    int *perm = (int*)pool_alloc(n * sizeof(int));
    char *visited = (char*)pool_alloc(n * sizeof(char));
    
    if (!perm || !visited) return;
    
    for (int i = 0; i < n; i++) {
        perm[i] = arr[i];
        visited[i] = 0;
    }
    
    callback(perm, n);
    
    // Поиск циклов
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int len = 0;
            int j = i;
            
            do {
                visited[j] = 1;
                // Находим позицию элемента arr[j] в исходном массиве
                for (int k = 0; k < n; k++) {
                    if (arr[k] == perm[j]) {
                        j = k;
                        break;
                    }
                }
                len++;
            } while (j != i);
            
            // Генерация перестановок цикла
            if (len > 1) {
                int *cycle_perm = (int*)pool_alloc(n * sizeof(int));
                for (int s = 1; s < len; s++) {
                    for (int k = 0; k < n; k++) {
                        cycle_perm[k] = perm[k];
                    }
                    
                    // Циклический сдвиг
                    int first = cycle_perm[i];
                    for (int k = i; k < i + len - 1; k++) {
                        cycle_perm[k] = cycle_perm[k + 1];
                    }
                    cycle_perm[i + len - 1] = first;
                    
                    callback(cycle_perm, n);
                }
            }
        }
    }
}

