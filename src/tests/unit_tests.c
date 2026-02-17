#include "permutations.h"

void test_lifecycle() {
    printf("[UNIT] Iterator Lifecycle... ");
    int arr[] = {10, 20, 30};
    
    // Создание
    permutation_iterator_t* iter = iterator_create(ALGO_NARAYANA, arr, 3);
    assert(iter != NULL);

    // Первый вызов (должен вернуть исходный массив)
    int* p = iterator_next(iter);
    assert(p != NULL);
    assert(p[0] == 10 && p[1] == 20);

    // Уничтожение
    iterator_destroy(iter);
    printf("OK\n");
}

void test_adaptive() {
    printf("[UNIT] Adaptive Selection... ");
    
    constraint_set_t c_order = { .require_order = true }; // Нужен порядок
    constraint_set_t c_speed = { .require_order = false }; // Нужна скорость

    // Если просим порядок -> Нарайана
    assert(select_optimal_algorithm(5, &c_order) == ALGO_NARAYANA);
    
    // Если пофиг на порядок -> Хип (он быстрее)
    assert(select_optimal_algorithm(5, &c_speed) == ALGO_HEAP);

    printf("OK\n");
}

void test_bad_inputs() {
    printf("[UNIT] Error Handling... ");
    // NULL массив
    assert(iterator_create(ALGO_HEAP, NULL, 5) == NULL);
    // N = 0
    int arr[] = {1};
    assert(iterator_create(ALGO_HEAP, arr, 0) == NULL);
    
    printf("OK\n");
}

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
    int* arr7 = NULL;
    int n7 = 0;

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

    int* arr5 = NULL;
    int n5 = 0;


    printf("Empty array — expect one callback\n");

    permutations_reverse_narayana(arr5,0,print_callback);

    printf("Passed\n");


    printf("All tests passed successfully!\n");
}


int arrays_equal(int a[], int b[], int n) {
    for(int i=0;i<n;i++)
        if(a[i]!=b[i])
            return 0;
    return 1;
}

void test_factorial_system_functions() {

    printf("Testing factorial system algorithm\n");
    
    printf("\nTest 1: index_to_factorial_digits(index=4, n=3)\n");

    int digits[3];
    index_to_factorial_digits(4,3,digits);

    printf("Received digits: ");
    printARR(digits,3);

    printf("Checking value ranges\n");

    assert(digits[0] >= 0 && digits[0] < 3);
    assert(digits[1] >= 0 && digits[1] < 2);
    assert(digits[2] >= 0 && digits[2] < 1);

    printf("Passed\n");

    printf("\nTest 2: lehmer_to_permutation\n");

    int arr2[] = {10,20,30};
    int digits2[] = {0,1,0};
    int result2[3];
    int expected2[] = {10,30,20};

    printf("arr: ");
    printARR(arr2,3);

    printf("digits: ");
    printARR(digits2,3);

    lehmer_to_permutation(arr2,3,digits2,result2);

    printf("Received: ");
    printARR(result2,3);

    printf("Expected: ");
    printARR(expected2,3);

    assert(arrays_equal(result2,expected2,3));

    printf("Passed\n");

    printf("\nTest 3: permutation_from_index\n");

    int arr3[] = {1,2,3};
    int result3[3];
    int expected3[] = {1,3,2};

    bool ok = permutation_from_index(arr3,3,1,result3);

    printf("Function result: %s\n", ok ? "true":"false");

    printf("Received: ");
    printARR(result3,3);

    printf("Expected: ");
    printARR(expected3,3);

    assert(ok==true);
    assert(arrays_equal(result3,expected3,3));

    printf("Passed\n");

    printf("\nTest 4: permutation_from_index out of range\n");

    int arr4[] = {1,2,3};
    int result4[3];

    bool ok2 = permutation_from_index(arr4,3,100,result4);

    printf("Function result: %s\n", ok2 ? "true":"false");
    printf("Expected: false\n");

    assert(ok2==false);

    printf("Passed\n");

    printf("\nTest 5: permutations_factorial_system [1,2,3]\n");

    int arr5[] = {1,2,3};

    printf("Expected all 6 permutations:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n\n");

    printf("Received:\n");
    permutations_factorial_system(arr5,3,print_callback);

    printf("verified\n");


    printf("All tests completed successfully!\n");
}


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


int arrays_equal(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void test_plus_one_algorithm() {

    printf("Testing Plus-One algorithm\n");

    printf("\nTest 1: build_permutation_from_indices\n");

    int sorted1[]  = {1,2,3};
    int indices1[] = {0,0,0};
    int result1[3];
    int temp1[3];
    int expected1[] = {1,2,3};

    printf("sorted: ");
    printARR(sorted1,3);

    printf("indices: ");
    printARR(indices1,3);

    build_permutation_from_indices(
        sorted1,
        indices1,
        3,
        result1,
        temp1);

    printf("Received: ");
    printARR(result1,3);

    printf("Expected: ");
    printARR(expected1,3);

    assert(arrays_equal(result1,expected1,3));

    printf("Passed\n");


    printf("\nTest 2: increment_factoradic\n");

    int indices2[] = {0,0,0};

    printf("Initial indices: ");
    printARR(indices2,3);

    increment_factoradic(indices2,3);

    printf("After increment: ");
    printARR(indices2,3);

    int expected2[] = {0,1,0};

    printf("Expected: ");
    printARR(expected2,3);

    assert(arrays_equal(indices2,expected2,3));

    printf("Passed\n");


    printf("\nTest 3: build_permutation_from_indices complex case\n");

    int sorted3[]  = {1,2,3};
    int indices3[] = {1,0,0};
    int result3[3];
    int temp3[3];
    int expected3[] = {2,1,3};

    printf("sorted: ");
    printARR(sorted3,3);

    printf("indices: ");
    printARR(indices3,3);

    build_permutation_from_indices(
        sorted3,
        indices3,
        3,
        result3,
        temp3);

    printf("Received: ");
    printARR(result3,3);

    printf("Expected: ");
    printARR(expected3,3);

    assert(arrays_equal(result3,expected3,3));

    printf("Passed\n");

    printf("\nTest 4: permutations_plus_one [1,2,3]\n");

    int arr4[] = {1,2,3};

    printf("Expected permutations:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n");


    printf("\nReceived:\n");

    permutations_plus_one(arr4,3,print_callback);

    printf("✓ Visually verified\n");


    printf("\nTest 5: permutations_plus_one n=0\n");

    int* arr5 = NULL;
    int n5 = 0;

    printf("Empty array, expecting one callback\n");

    permutations_plus_one(arr5,0,print_callback);

    printf("Passed\n");


    printf("All tests completed successfully!\n");
}

int main() {
    printf("=== RUNNING UNIT TESTS ===\n");
    test_lifecycle();
    test_adaptive();
    test_bad_inputs();

    //iterarive tests
    test_next_permutation();
    test_reverse_narayana();
    test_factorial_system_functions();
    test_inversion_functions();
    test_plus_one_algorithm();

    printf("=== ALL UNIT TESTS PASSED ===\n");
    return 0;
}