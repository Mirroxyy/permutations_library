#ifndef ITERATIVE_UTILS_H
#define ITERATIVE_UTILS_H

#include <stdbool.h>

void swap(int* a, int* b); 
void reset_stop_flag(void); 
void request_stop(void);
void bubble_sort(int arr[], int size);
void copyARR(int arr[], int copy[], int n);
void reverseTail(int arr[], int start, int end);
long factorial(int n);
void print_callback(int perm[], int n);
void printARR(int* arr, int n);
bool is_valid_inversion_table(int* inv, int n);

#endif