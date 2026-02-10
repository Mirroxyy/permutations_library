#include "iterative_algorithms.h"
#include "iterative_utils.h"

void test_inversion_functions() {

    printf("Testing algorithm using inversion table\n");

    printf("\nTest 1: factorial_int(5) -> 120\n");
    long f = factorial(5);
    printf("Got: %ld\n", f);
    printf("Expected: 120\n");
    assert(f == 120);
    printf("Passed\n");

    printf("\nTest 2: is_valid_inversion_table\n");

    int valid[] = {0,1,0};
    int invalid[] = {0,5,0};

    bool r1 = is_valid_inversion_table(valid,3);
    bool r2 = is_valid_inversion_table(invalid,3);

    printf("Expected: true, false\n");
    printf("Got: %s, %s\n",
           r1 ? "true" : "false",
           r2 ? "true" : "false");

    assert(r1 == true);
    assert(r2 == false);

    printf("Passed\n");

    printf("\nTest 3: index_to_inversion_table(3, n=3)\n");

    int inv[3];
    index_to_inversion_table(3,inv,3);

    printf("Generated inversion table: ");
    printARR(inv,3);

    printf("Checking value ranges\n");

    assert(inv[0] >= 0 && inv[0] < 3);
    assert(inv[1] >= 0 && inv[1] < 2);
    assert(inv[2] >= 0 && inv[2] < 1);

    printf("Passed\n");

    printf("\nTest 4: permutation_from_inversion_table\n");

    int sorted[] = {1,2,3};
    int inv_zero[] = {0,0,0};
    int result[3];
    int expected[] = {1,2,3};

    printf("sorted: ");
    printARR(sorted,3);

    printf("inv: ");
    printARR(inv_zero,3);

    permutation_from_inversion_table(
        inv_zero,
        sorted,
        3,
        result);

    printf("Got permutation: ");
    printARR(result,3);

    printf("Expected: ");
    printARR(expected,3);

    for (int i = 0; i < 3; i++)
        assert(result[i] == expected[i]);

    printf("Passed\n");


    printf("\nTest 5: permutations_inversion_table [1,2,3]\n");
    printf("Expected all 6 permutations:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n\n");

    int arr[] = {1,2,3};

    printf("Got:\n");
    permutations_inversion_table(arr,3,print_callback);

    printf("checked\n");

    printf("All tests completed successfully!\n");
}

int main() {
    test_inversion_functions();
    return 0;
}
