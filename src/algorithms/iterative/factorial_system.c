#include "iterative_algorithms.h"
#include "iterative_utils.h"

// convert index into factorial number system digits
void index_to_factorial_digits(long index, int n, int digits[]) {
    for(int i = 1; i <= n; i++){
        digits[n-i] = index%i;
        index /= i;
    }
}

// build permutation from Lehmer code digits
void lehmer_to_permutation(int arr[], int n, int digits[], int result[]) {
    // list of available indices
    int *available=malloc(n*sizeof(int));
    if(!available)
        return;

    for(int i = 0; i < n; i++)
        available[i] = i;

    for(int i = 0; i < n; i++){
        int pos = digits[i];
        result[i] = arr[available[pos]];

        // remove used element from available list
        for(int j = pos; j < n-i-1; j++)
            available[j] = available[j+1];
    }

    free(available);
}

// get permutation by its lexicographic index
bool permutation_from_index(int arr[], int n, long index, int result[]) {
    long total = factorial(n);
    // check index range
    if (index < 0 || index >= total)
        return false;

    int *digits = malloc(n*sizeof(int));
    if (!digits)
        return false;

        
    index_to_factorial_digits(index,n,digits);
    lehmer_to_permutation(arr,n,digits,result);

    free(digits);
    return true;
}

// generate all permutations using factorial system
void permutations_factorial_system(int arr[], int n,
    void (*callback)(int perm[], int n)) {

    if(!callback||n<=0)
        return;

    // sorted working copy
    int *work=malloc(n*sizeof(int));
    // buffer for permutation
    int *perm=malloc(n*sizeof(int));
    if(!work || !perm)
        return;

    copyARR(arr,work,n);
    bubble_sort(work,n);

    long total = factorial(n);
    // iterate all indices
    for(long i = 0; i < total; i++)
        if(permutation_from_index(work, n, i, perm))
            // output permutation
            callback(perm, n);

    free(work);
    free(perm);
}

