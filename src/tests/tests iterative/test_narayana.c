#include "permutations.h"

void test_next_permutation() {
    printf("=== Testing next_permutation_narayana ===\n\n");
    
    // Test 1: [1, 2, 4, 3] -> [1, 3, 2, 4]
    printf("Test 1: [1, 2, 4, 3] -> [1, 3, 2, 4]\n");
    printf("Initial array: ");
    int arr1[] = {1, 2, 4, 3};
    printARR(arr1, 4);
    
    int expected1[] = {1, 3, 2, 4};
    bool has_next = next_permutation_narayana(arr1, 4);
    
    printf("Function result: %s\n", has_next ? "true" : "false");
    printf("Result array: ");
    printARR(arr1, 4);
    
    assert(has_next == true);
    for (int i = 0; i < 4; i++) {
        assert(arr1[i] == expected1[i]);
    }
    printf("Passed\n");
    
    // Test 2: [3, 1, 4, 2] -> [3, 2, 1, 4]
    printf("\nTest 2: [3, 1, 4, 2] -> [3, 2, 1, 4]\n");
    printf("Initial array: ");
    int arr2[] = {3, 1, 4, 2};
    printARR(arr2, 4);
    
    int expected2[] = {3, 2, 1, 4};
    has_next = next_permutation_narayana(arr2, 4);
    
    printf("Function result: %s\n", has_next ? "true" : "false");
    printf("Result array: ");
    printARR(arr2, 4);
    
    assert(has_next == true);
    for (int i = 0; i < 4; i++) {
        assert(arr2[i] == expected2[i]);
    }
    printf("Passed\n");
    
    // Test 3: [4, 3, 2, 1] -> last permutation (false)
    printf("\nTest 3: [4, 3, 2, 1] -> last permutation (should return false)\n");
    printf("Initial array: ");
    int arr3[] = {4, 3, 2, 1};
    printARR(arr3, 4);
    
    int original3[] = {4, 3, 2, 1};
    has_next = next_permutation_narayana(arr3, 4);
    
    printf("Function result: %s\n", has_next ? "true" : "false");
    printf("Result array: ");
    printARR(arr3, 4);
    
    assert(has_next == false);
    for (int i = 0; i < 4; i++) {
        assert(arr3[i] == original3[i]);
    }
    printf("Passed\n");
    
    // Test 4: All permutations [1, 2, 3] (should be 3! = 6 permutations)
    printf("\nTest 4: All permutations [1, 2, 3] (should be 6 permutations)\n");
    int arr4[] = {1, 2, 3};
    int all_permutations[6][3] = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };
    
    printf("Initial permutation: ");
    printARR(arr4, 3);
    for (int i = 0; i < 3; i++) {
        assert(arr4[i] == all_permutations[0][i]);
    }
    
    int count = 0;
    while (next_permutation_narayana(arr4, 3)) {
        count++;
        printf("Call %d, function result: true\n", count);
        printf("Permutation %d: ", count + 1);
        printARR(arr4, 3);
        
        for (int i = 0; i < 3; i++) {
            assert(arr4[i] == all_permutations[count][i]);
        }
    }
    
    printf("Call %d, function result: false (no more permutations)\n", count + 1);
    
    assert(count == 5);
    printf("Total successful next_permutation calls: %d\n", count);
    printf("Passed (got %d permutations total)\n", count + 1);
    
    // Test 5: After last permutation should return false
    printf("\nTest 5: Verify false after all permutations\n");
    printf("Current array: ");
    printARR(arr4, 3);
    has_next = next_permutation_narayana(arr4, 3);
    printf("Function result: %s\n", has_next ? "true" : "false");
    assert(has_next == false);
    printf("Passed\n");
    
    // Test 6: Single element array
    printf("\nTest 6: Single element array [5]\n");
    printf("Initial array: ");
    int arr6[] = {5};
    printARR(arr6, 1);
    
    has_next = next_permutation_narayana(arr6, 1);
    printf("Function result: %s\n", has_next ? "true" : "false");
    printf("Result array: ");
    printARR(arr6, 1);
    
    assert(has_next == false);
    assert(arr6[0] == 5);
    printf("Passed\n");
    
    // Test 7: Empty array
    printf("\nTest 7: Empty array (n=0)\n");
    printf("Empty array, n=0\n");
    int arr7[] = {};
    has_next = next_permutation_narayana(arr7, 0);
    printf("Function result: %s\n", has_next ? "true" : "false");
    assert(has_next == false);
    printf("Passed\n");
    
    // Test 8: Additional test [2, 1, 3]
    printf("\nTest 8: Additional test [2, 1, 3]\n");
    printf("Initial array: ");
    int arr8[] = {2, 1, 3};
    printARR(arr8, 3);
    
    has_next = next_permutation_narayana(arr8, 3);
    printf("Function result: %s\n", has_next ? "true" : "false");
    printf("Result array: ");
    printARR(arr8, 3);
    
    int expected8[] = {2, 3, 1};
    assert(has_next == true);
    for (int i = 0; i < 3; i++) {
        assert(arr8[i] == expected8[i]);
    }
    printf("Passed\n");
    
    printf("All tests passed successfully!\n");
}

int main() {
    test_next_permutation();
    return 0;
}
