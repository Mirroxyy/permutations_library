#include "permutations.h"

void printARR(int* arr, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static bool stop_flag = false;

void reset_stop_flag() {
    stop_flag = false;
}

void request_stop() {
    stop_flag = true;
}


bool is_valid_inversion_table(int* inv, int n) {
    for (int i = 0; i < n; i++) {
        if (inv[i] < 0 || inv[i] > (n - i - 1))
            return false;
    }
    return true;
}

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void copyARR(int arr[], int copy[], int n){
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];
}

void reverseTail(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

long factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
