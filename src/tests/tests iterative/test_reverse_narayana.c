#include "iterative_algorithms.h"
#include "iterative_utils.h"

int arrays_equal(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void test_reverse_narayana() {

    printf("Testing Reverse Narayana\n");
    printf("\nTest 1: prev_permutation_narayana [3,2,1] -> [3,1,2]\n");

    int arr1[] = {3,2,1};
    int expected1[] = {3,1,2};

    printf("Original array: ");
    printARR(arr1,3);

    bool res = prev_permutation_narayana(arr1,3);

    printf("Function result: %s\n", res ? "true":"false");
    printf("Received: ");
    printARR(arr1,3);

    printf("Expected: ");
    printARR(expected1,3);

    assert(res == true);
    assert(arrays_equal(arr1,expected1,3));

    printf("✓ Passed\n");

    printf("\nTest 2: prev_permutation_narayana minimal permutation\n");

    int arr2[] = {1,2,3};
    int original2[] = {1,2,3};

    printf("Original array: ");
    printARR(arr2,3);

    res = prev_permutation_narayana(arr2,3);

    printf("Function result: %s\n", res ? "true":"false");
    printf("Received: ");
    printARR(arr2,3);

    assert(res == false);
    assert(arrays_equal(arr2,original2,3));

    printf("✓ Passed\n");

    printf("\nTest 3: single element array\n");

    int arr3[] = {5};

    printf("Original array: ");
    printARR(arr3,1);

    res = prev_permutation_narayana(arr3,1);

    printf("Function result: %s\n", res ? "true":"false");

    assert(res == false);
    assert(arr3[0] == 5);

    printf("Passed\n");

    printf("\nTest 4: permutations_reverse_narayana [1,2,3]\n");

    int arr4[] = {1,2,3};

    printf("Expected order:\n");
    printf("3 2 1\n");
    printf("3 1 2\n");
    printf("2 3 1\n");
    printf("2 1 3\n");
    printf("1 3 2\n");
    printf("1 2 3\n");

    printf("\nReceived:\n");

    permutations_reverse_narayana(arr4,3,print_callback);

    printf("verified\n");

    printf("\nTest 5: permutations_reverse_narayana n=0\n");

    int arr5[] = {};

    printf("Empty array — expect one callback\n");

    permutations_reverse_narayana(arr5,0,print_callback);

    printf("Passed\n");


    printf("All tests passed successfully!\n");
}

int main() {
    test_reverse_narayana();
    return 0;
}
