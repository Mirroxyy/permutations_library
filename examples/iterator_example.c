#include "iterative_algorithms.h"
#include "iterative_utils.h"

/* ============================================================
   Пример 1 — Алгоритм Нарайаны (next_permutation)
   ============================================================ */
void example_narayana() {

    printf("\n==============================\n");
    printf("Пример: Алгоритм Нарайаны\n");
    printf("==============================\n");

    int arr[] = {1,2,3};

    printf("Исходный массив:\n");
    printARR(arr,3);

    printf("\nВсе перестановки:\n");
    permutation_narayana(arr,3,print_callback);
}

/* ============================================================
   Пример 2 — Факториальная система
   ============================================================ */
void example_factorial_system() {

    printf("\n==============================\n");
    printf("Пример: Факториальная система\n");
    printf("==============================\n");

    int arr[] = {1,2,3};

    printf("Все перестановки:\n");
    permutations_factorial_system(arr,3,print_callback);

    printf("\nПерестановка по индексу 4:\n");

    int result[3];
    if(permutation_from_index(arr,3,4,result))
        printARR(result,3);
}

/* ============================================================
   Пример 3 — Таблица инверсий
   ============================================================ */
void example_inversion_table() {

    printf("\n==============================\n");
    printf("Пример: Таблица инверсий\n");
    printf("==============================\n");

    int arr[] = {1,2,3};

    printf("Все перестановки:\n");
    permutations_inversion_table(arr,3,print_callback);
}

/* ============================================================
   Пример 4 — Алгоритм плюс-один
   ============================================================ */
void example_plus_one() {

    printf("\n==============================\n");
    printf("Пример: Алгоритм Плюс-один\n");
    printf("==============================\n");

    int arr[] = {1,2,3};

    printf("Все перестановки:\n");
    permutations_plus_one(arr,3,print_callback);
}

/* ============================================================
   Пример 5 — Reverse Narayana
   ============================================================ */
void example_reverse_narayana() {

    printf("\n==============================\n");
    printf("Пример: Reverse Narayana\n");
    printf("==============================\n");

    int arr[] = {1,2,3};

    printf("Все перестановки (обратный порядок):\n");
    permutations_reverse_narayana(arr,3,print_callback);
}

int main() {

   
    printf("   ITERATIVE ALGORITHMS EXAMPLES\n");
    
    example_narayana();
    example_factorial_system();
    example_inversion_table();
    example_plus_one();
    example_reverse_narayana();

    printf(" END OF EXAMPLES\n");
    
    return 0;
}
