#include "../permutations_library/include/permutations.h"

typedef struct
{
    int forbidden_map[10][2];

    int must_follow[2];

} ConstraintRules;
 

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}


static bool stop_generation = false;

void reset_stop_flag() {
    stop_generation = false;
}

void request_stop() {
    stop_generation = true;
}

void print_perm(int perm[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) printf("%d%s", perm[i], i == n - 1 ? "" : ", ");
    printf("]\n");
}