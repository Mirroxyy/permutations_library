
#include "iterative_algorithms.h"
#include "iterative_utils.h"

void build_permutation_from_indices(
    int sorted[],int indices[],
    int n,int result[],int temp[]){

    copyARR(sorted,temp,n);
    int size=n;

    for(int i=0;i<n;i++){
        int idx=indices[i];
        result[i]=temp[idx];
        for(int j=idx;j<size-1;j++)
            temp[j]=temp[j+1];
        size--;
    }
}

void increment_factoradic(int indices[],int n){
    for(int i=n-1;i>=0;i--){
        indices[i]++;
        if(indices[i]<n-i)
            return;
        indices[i]=0;
    }
}

void permutations_plus_one(int arr[],int n,
    void (*callback)(int perm[],int n)){

    if(!callback) return;

    int *sorted=malloc(n*sizeof(int));
    int *indices=malloc(n*sizeof(int));
    int *result=malloc(n*sizeof(int));
    int *temp=malloc(n*sizeof(int));

    if(!sorted||!indices||!result||!temp) return;

    copyARR(arr,sorted,n);
    bubble_sort(sorted,n);

    for(int i=0;i<n;i++)
        indices[i]=0;

    long total=factorial(n);

    for(long i=0;i<total;i++){
        build_permutation_from_indices(
            sorted,indices,n,result,temp);
        callback(result,n);
        increment_factoradic(indices,n);
    }

    free(sorted);
    free(indices);
    free(result);
    free(temp);
}

