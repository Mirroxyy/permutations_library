#include <stdlib.h>

#include "permutations.h"

// convert lexicographic index to inversion table
void index_to_inversion_table(long index, int inv[], int n){
    // iterate positions
    for(int i = 0; i < n; i++){
        // compute inversion value
        inv[i] = index % (n-i);
        // reduce index
        index /= (n-i);
    }
}

// build permutation using inversion table
void permutation_from_inversion_table(
    int inv[], int sorted[], int n, int result[]){
    // temporary available elements
    int available[32];

    for(int i = 0; i < n; i++)
        available[i] = sorted[i];

    int size=n;
    for(int i = 0; i < n; i++) {
        // index from inversion table
        int idx = inv[i];
        result[i] = available[idx];

        // remove used element from available list
        for(int j = idx; j < size-1; j++)
            available[j] = available[j+1];
        // reduce available count    
        size--;
    }
}

// generate all permutations using inversion tables
void permutations_inversion_table(int arr[],int n,
    void (*callback)(int perm[],int n)){

    if(!callback)
        return;

    // sorted working array    
    int *sorted = (int*)pool_alloc(n * sizeof(int));
    // inversion table buffer
    int *inv = (int*)pool_alloc(n * sizeof(int));
    // result permutation buffer
    int *result = (int*)pool_alloc(n * sizeof(int));

    if(!sorted || !inv || !result)
        return;

    copyARR(arr, sorted, n);
    bubble_sort(sorted, n);

    long total = factorial(n);
    
    // iterate all indices
    for(long i = 0; i < total; i++){
        // build inversion table
        index_to_inversion_table(i, inv, n);
        // build perm
        permutation_from_inversion_table(inv, sorted, n, result);
        // output permutation
        callback(result, n);
    }
}