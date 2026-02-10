
#include "iterative_algorithms.h"
#include "iterative_utils.h"

// find pivot index for previous permutation (reverse Narayana)
int findI_reverse(int arr[], int n){
    for(int i = n-2; i >= 0; i--)
        if(arr[i] > arr[i+1])
            return i;
    return -1;
}

// find element smaller than arr[I] from the right side
int findJ_reverse(int arr[],int n,int I){
    for(int j=n-1;j>I;j--)
        if(arr[j]<arr[I])
            return j;
    return -1;
}

// generate previous lexicographic permutation
bool prev_permutation_narayana(int arr[],int n){
    if (n < 2)
        return false;

    int I = findI_reverse(arr,n);
    if( I == -1)
        return false;

    int J = findJ_reverse(arr,n,I);
    if( J == -1)
        return false;

    swap(&arr[I],&arr[J]);
    reverseTail(arr,I+1,n-1);
    return true;
}

// generate all permutations in reverse lexicographic order
void permutations_reverse_narayana(
    int arr[], int n,
    void (*callback)(int perm[],int n)){

    if(!callback) return;

    // allocate working copy
    int *work=malloc(n*sizeof(int));
    if(!work)
        return;

    copyARR(arr,work, n);
    bubble_sort(work, n);
    reverseTail(work, 0 , n-1);

    callback(work, n);

    // generate previous perms
    while(prev_permutation_narayana(work, n))
        // output each permutation
        callback(work, n);

    free(work);
}

