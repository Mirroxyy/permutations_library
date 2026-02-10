#include <stdlib.h>
#include <stdbool.h>

#include "permutations.h"

// find the rightmost position I where arr[i] < arr[i+1]
int findI(int arr[], int n) {
    for (int i = n-2; i >= 0; i--)
        if (arr[i] < arr[i+1])
            return i;
    return -1;
}

// find element J greater than arr[I] from the right side
int findJ(int arr[], int n, int I) {
    for (int j = n-1; j > I; j--)
        if (arr[j] > arr[I])
            return j;
    return -1;
}

// generate next lexicographic permutation (Narayana algorithm)
bool next_permutation_narayana(int arr[], int n) {
    if (n < 2) 
        return false;

    int I = findI(arr, n);

    if (I == -1)
        return false;

    int J = findJ(arr, n, I);

    swap(&arr[I], &arr[J]);
    reverseTail(arr, I+1, n-1);

    return true;
}

// generate all permutations using Narayana method
void permutation_narayana(int arr[],int n,
                          void (*callback)(int perm[], int n)) {
    if (!callback || n<=0)
        return;

    int *work = (int*)pool_alloc(n * sizeof(int));
    
    if(!work)
        return;

    copyARR(arr, work, n);
    bubble_sort(work, n);

    callback(work, n);
    while(next_permutation_narayana(work,n))
        callback(work,n);
}