
#ifndef ITERATIVE_ALGORITHMS_H
#define ITERATIVE_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//narayana
int findI(int arr[], int n);
int findJ(int arr[], int n, int I);
bool next_permutation_narayana(int arr[], int n);
void permutation_narayana(int arr[],int n,
                          void (*callback)(int perm[], int n));

//factorial_system
void index_to_factorial_digits(long index,int n,int digits[]);
void lehmer_to_permutation(int arr[],int n,int digits[],int result[]);
bool permutation_from_index(int arr[],int n,long index,int result[]);
void permutations_factorial_system(int arr[],int n,
    void (*callback)(int perm[],int n));

//inversion_table
void index_to_inversion_table(long index,int inv[],int n);
void permutation_from_inversion_table(int inv[],int sorted[],
                                        int n,int result[]);
void permutations_inversion_table(int arr[],int n,
                        void (*callback)(int perm[],int n));

//plus_one
void build_permutation_from_indices(
    int sorted[],int indices[],
    int n,int result[],int temp[]);
void increment_factoradic(int indices[],int n);
void permutations_plus_one(int arr[],int n,
    void (*callback)(int perm[],int n));

//reverse_narayana
int findI_reverse(int arr[],int n);
int findJ_reverse(int arr[],int n,int I);
bool prev_permutation_narayana(int arr[],int n);
void permutations_reverse_narayana(
    int arr[],int n,
    void (*callback)(int perm[],int n));


#endif
