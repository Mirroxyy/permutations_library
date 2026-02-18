#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables for building the DOT graph
static FILE* dot_out = NULL;
static char prev_node_id[256] = "";


static void get_node_id(int arr[], int n, char* buf) {
    sprintf(buf, "p");
    for (int i = 0; i < n; i++) {
        char temp[16];
        sprintf(temp, "%d", arr[i]);
        strcat(buf, temp);
    }
}

// Callback that doesn't just print, but writes connections to the DOT file
static void dot_step_callback(int perm[], int n) {
    if (!dot_out) return;

    char current_node_id[256];
    get_node_id(perm, n, current_node_id);

    // Draw the node
    fprintf(dot_out, "    %s [label=\"", current_node_id);
    for (int i = 0; i < n; i++) fprintf(dot_out, "%d%s", perm[i], (i == n - 1) ? "" : " ");
    fprintf(dot_out, "\"];\n");

    // Draw an edge from the previous permutation
    if (strlen(prev_node_id) > 0) {
        fprintf(dot_out, "    %s -> %s;\n", prev_node_id, current_node_id);
    }

    strcpy(prev_node_id, current_node_id);
}

void visualize_algorithm_to_png(permutation_algorithm_t algo, int n) {
    if (n <= 0) return;

    // Prepare the array for generation
    int* temp_arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp_arr[i] = i + 1;

    const char* dot_filename = "permutation_graph.dot";
    dot_out = fopen(dot_filename, "w");
    if (!dot_out) {
        free(temp_arr);
        return;
    }

    fprintf(dot_out, "digraph G {\n    rankdir=LR;\n");
    prev_node_id[0] = '\0';

    // Run generation with our DOT callback
    generate_permutations(algo, temp_arr, n, dot_step_callback);

    fprintf(dot_out, "}\n");
    fclose(dot_out);
    free(temp_arr);
    
    // 1. Convert to PNG
    system("dot -Tpng permutation_graph.dot -o graph.png");

    printf("Opening graph.png...\n");

    #ifdef __linux__
        system("xdg-open graph.png &"); 
    #elif _WIN32
        system("start graph.png");      
        system("open graph.png");      
    #endif
}

bool core_verify_algorithm(permutation_algorithm_t algo, int n) {
    unsigned long long expected = 1;
    for (int i = 1; i <= n; i++) expected *= i;

    int* test_arr = malloc(n * sizeof(int));
    if (!test_arr) return false;
    for (int i = 0; i < n; i++) test_arr[i] = i + 1;

  
    benchmark_result_t res = benchmark_algorithm(algo, test_arr, n, 1);

    free(test_arr);
    return res.count == expected;
}   