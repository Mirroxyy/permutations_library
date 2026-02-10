#include "permutations.h"

// build permutation from factoradic indices
void build_permutation_from_indices(
    int sorted[], int indices[],
    int n, int result[], int temp[]){

    copyARR(sorted, temp, n);
    int size=n;

    for(int i = 0; i < n; i++){
        // select index from factoradic digits
        int idx = indices[i];
        // choose element for permutation
        result[i] = temp[idx];

        // remove used element from temp list    
        for(int j = idx; j < size-1; j++)
            temp[j] = temp[j+1];
        // reduce available elements    
        size--;
    }
}

// increment factoradic representation (plus-one algorithm)
void increment_factoradic(int indices[], int n){
    // process digits from right to left
    for(int i = n-1; i >= 0; i--){
        // increment current digit
        indices[i]++;
        // if no overflow stop
        if(indices[i] < n-i)
            return;
        // reset digit on overflow
        indices[i] = 0;
    }
}

// generate permutations using plus-one incremental method
void permutations_plus_one(int arr[], int n,
    void (*callback)(int perm[], int n)){

    if(!callback)
        return;
    
    // sorted input copy
    int *sorted = (int*)pool_alloc(n * sizeof(int));
    // factoradic indices
    int *indices = (int*)pool_alloc(n * sizeof(int));
    // result permutation
    int *result = (int*)pool_alloc(n * sizeof(int));
    // temporary buffer
    int *temp = (int*)pool_alloc(n * sizeof(int));

    if(!sorted || !indices || !result || !temp)
        return;

    copyARR(arr, sorted, n);
    bubble_sort(sorted, n);

    for(int i = 0; i < n; i++)
        // initialize factoradic digits
        indices[i] = 0;

    long total = factorial(n);

    for(long i = 0; i < total; i++){
        // build permutation
        build_permutation_from_indices(
            sorted, indices, n, result, temp);
        // output permutation    
        callback(result, n);
        // move to next index
        increment_factoradic(indices, n);
    }
}