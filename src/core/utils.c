#include "../permutations_library/include/permutations.h"

typedef struct
{
    int forbidden_map[10][2];

    int must_follow[2];

} ConstraintRules;
 


// Функция для обмена элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Компаратор для сортировки (нужен для лексикографического порядка)
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Флаг для механизма раннего прекращения (можно вынести в структуру контекста)
static bool stop_generation = false;

void reset_stop_flag() {
    stop_generation = false;
}

// Позволяет пользователю остановить генерацию из callback
void request_stop() {
    stop_generation = true;
}

