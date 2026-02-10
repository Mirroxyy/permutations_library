#include "permutations.h"

// Оптимизированная версия алгоритма Джонсона-Троттера
void permutations_johnson_trotter_opt(int arr[], int n, perm_callback_t callback) {
    if (n <= 0) return;
    
    // Используем пул памяти для оптимизации
    int *perm = (int*)pool_alloc(n * sizeof(int));
    int *pos = (int*)pool_alloc(n * sizeof(int));
    char *dir = (char*)pool_alloc(n * sizeof(char));
    
    if (!perm || !pos || !dir) {
        return;
    }
    
    // Инициализация
    for (int i = 0; i < n; i++) {
        perm[i] = arr[i];
        pos[arr[i] - 1] = i;
        dir[i] = -1; // ←
    }
    
    callback(perm, n);
    
    while (true) {
        // Поиск наибольшего подвижного элемента
        int max_mobile = -1;
        int max_mobile_pos = -1;
        
        for (int i = n-1; i >= 0; i--) { // Ищем с конца для оптимизации
            int p = pos[i];
            int neighbor = p + dir[p];
            
            if (neighbor >= 0 && neighbor < n && perm[neighbor] < perm[p]) {
                if ((i+1) > max_mobile) {
                    max_mobile = i + 1;
                    max_mobile_pos = p;
                }
            }
        }
        
        if (max_mobile_pos == -1) break;
        
        // Обмен с соседом
        int neighbor_pos = max_mobile_pos + dir[max_mobile_pos];
        int mobile_val = perm[max_mobile_pos];
        int neighbor_val = perm[neighbor_pos];
        
        SWAP(perm, max_mobile_pos, neighbor_pos);
        pos[mobile_val - 1] = neighbor_pos;
        pos[neighbor_val - 1] = max_mobile_pos;
        
        // Изменение направлений
        for (int i = max_mobile-1; i < n; i++) {
            dir[pos[i]] = -dir[pos[i]];
        }
        
        callback(perm, n);
    }
}

