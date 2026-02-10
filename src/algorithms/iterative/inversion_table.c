
#include "iterative_algorithms.h"
#include "iterative_utils.h"

void index_to_inversion_table(long index,int inv[],int n){
    for(int i=0;i<n;i++){
        inv[i]=index%(n-i);
        index/=(n-i);
    }
}

void permutation_from_inversion_table(
    int inv[],int sorted[],int n,int result[]){
    int available[32];
    for(int i=0;i<n;i++)
        available[i]=sorted[i];

    int size=n;
    for(int i=0;i<n;i++){
        int idx=inv[i];
        result[i]=available[idx];
        for(int j=idx;j<size-1;j++)
            available[j]=available[j+1];
        size--;
    }
}

void permutations_inversion_table(int arr[],int n,
    void (*callback)(int perm[],int n)){

    if(!callback) return;

    int *sorted=malloc(n*sizeof(int));
    int *inv=malloc(n*sizeof(int));
    int *result=malloc(n*sizeof(int));

    if(!sorted||!inv||!result) return;

    copyARR(arr,sorted,n);
    bubble_sort(sorted,n);

    long total=factorial(n);

    for(long i=0;i<total;i++){
        index_to_inversion_table(i,inv,n);
        permutation_from_inversion_table(inv,sorted,n,result);
        callback(result,n);
    }

    free(sorted);
    free(inv);
    free(result);
}

