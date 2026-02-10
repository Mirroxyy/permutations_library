#include "iterative_utils.h"

/*void swap(int *a,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}*/

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


/*void printARR(int arr[], int n){
    for (int h = 0; h < n; h++) 
        printf("%d ", arr[h]);

    printf("\n");
}

void print_callback(int perm[], int n) {
    printARR(perm, n);
}
*/