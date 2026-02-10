
#include "iterative_algorithms.h"
#include "iterative_utils.h"

int findI(int arr[], int n) {
    for (int i = n-2; i >= 0; i--)
        if (arr[i] < arr[i+1])
            return i;
    return -1;
}

int findJ(int arr[], int n, int I) {
    for (int j = n-1; j > I; j--)
        if (arr[j] > arr[I])
            return j;
    return -1;
}

bool next_permutation_narayana(int arr[], int n) {
    if (n < 2) return false;
    int I = findI(arr, n);
    if (I == -1) return false;
    int J = findJ(arr, n, I);
    swap(&arr[I], &arr[J]);
    reverseTail(arr, I+1, n-1);
    return true;
}

void permutation_narayana(int arr[],int n,
                          void (*callback)(int perm[], int n)) {
    if (!callback || n<=0) return;

    int *work = malloc(n*sizeof(int));
    if(!work) return;

    copyARR(arr, work, n);
    bubble_sort(work, n);

    callback(work, n);
    while(next_permutation_narayana(work,n))
        callback(work,n);

    free(work);
}
