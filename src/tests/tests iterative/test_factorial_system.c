#include "iterative_algorithms.h"
#include "iterative_utils.h"

int arrays_equal(int a[], int b[], int n) {
    for(int i=0;i<n;i++)
        if(a[i]!=b[i])
            return 0;
    return 1;
}

void test_factorial_system_functions() {

    printf("==============================================\n");
    printf("Тестирование алгоритма факториальной системы\n");
    printf("==============================================\n");


    // ============================================================
    printf("\nТест 1: index_to_factorial_digits(index=4, n=3)\n");

    int digits[3];
    index_to_factorial_digits(4,3,digits);

    printf("Получили digits: ");
    printARR(digits,3);

    printf("Проверяем диапазоны значений\n");

    assert(digits[0] >= 0 && digits[0] < 3);
    assert(digits[1] >= 0 && digits[1] < 2);
    assert(digits[2] >= 0 && digits[2] < 1);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 2: lehmer_to_permutation\n");

    int arr2[] = {10,20,30};
    int digits2[] = {0,1,0};
    int result2[3];
    int expected2[] = {10,30,20};

    printf("arr: ");
    printARR(arr2,3);

    printf("digits: ");
    printARR(digits2,3);

    lehmer_to_permutation(arr2,3,digits2,result2);

    printf("Получили: ");
    printARR(result2,3);

    printf("Ожидали: ");
    printARR(expected2,3);

    assert(arrays_equal(result2,expected2,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 3: permutation_from_index\n");

    int arr3[] = {1,2,3};
    int result3[3];
    int expected3[] = {1,3,2};

    bool ok = permutation_from_index(arr3,3,1,result3);

    printf("Результат функции: %s\n", ok ? "true":"false");

    printf("Получили: ");
    printARR(result3,3);

    printf("Ожидали: ");
    printARR(expected3,3);

    assert(ok==true);
    assert(arrays_equal(result3,expected3,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 4: permutation_from_index выход за диапазон\n");

    int arr4[] = {1,2,3};
    int result4[3];

    bool ok2 = permutation_from_index(arr4,3,100,result4);

    printf("Результат функции: %s\n", ok2 ? "true":"false");
    printf("Ожидали: false\n");

    assert(ok2==false);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 5: permutations_factorial_system [1,2,3]\n");

    int arr5[] = {1,2,3};

    printf("Ожидали все 6 перестановок:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n\n");

    printf("Получили:\n");
    permutations_factorial_system(arr5,3,print_callback);

    printf("✓ Визуально проверено\n");


    printf("\n==============================================\n");
    printf("Все тесты завершены успешно!\n");
    printf("==============================================\n");
}

int main() {
    test_factorial_system_functions();
    return 0;
}
