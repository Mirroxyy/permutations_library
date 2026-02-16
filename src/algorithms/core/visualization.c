#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Глобальные переменные для построения графа DOT
static FILE* dot_out = NULL;
static char prev_node_id[256] = "";

/**
 * Вспомогательная функция для создания ID узла на основе массива
 * [1, 2, 3] -> "p123"
 */
static void get_node_id(int arr[], int n, char* buf) {
    sprintf(buf, "p");
    for (int i = 0; i < n; i++) {
        char temp[16];
        sprintf(temp, "%d", arr[i]);
        strcat(buf, temp);
    }
}

/**
 * Колбэк, который не просто печатает, а пишет связи в DOT-файл
 */
static void dot_step_callback(int perm[], int n) {
    if (!dot_out) return;

    char current_node_id[256];
    get_node_id(perm, n, current_node_id);

    // Рисуем узел
    fprintf(dot_out, "    %s [label=\"", current_node_id);
    for (int i = 0; i < n; i++) fprintf(dot_out, "%d%s", perm[i], (i == n - 1) ? "" : " ");
    fprintf(dot_out, "\"];\n");

    // Рисуем ребро от предыдущей перестановки
    if (strlen(prev_node_id) > 0) {
        fprintf(dot_out, "    %s -> %s;\n", prev_node_id, current_node_id);
    }

    strcpy(prev_node_id, current_node_id);
}

void visualize_algorithm_to_png(permutation_algorithm_t algo, int n) {
    if (n <= 0) return;

    // Подготавливаем массив для генерации
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

    // Запускаем генерацию с нашим DOT-колбэком
    generate_permutations(algo, temp_arr, n, dot_step_callback);

    fprintf(dot_out, "}\n");
    fclose(dot_out);
    free(temp_arr);
    
    // 1. Конвертация в PNG
    system("dot -Tpng permutation_graph.dot -o graph.png");

    // 2. Автоматическое открытие картинки
    printf("Opening graph.png...\n");

    #ifdef __linux__
        system("xdg-open graph.png &"); // Для Linux (твоя система)
    #elif _WIN32
        system("start graph.png");      // Для Windows
    #elif __APPLE__
        system("open graph.png");       // Для macOS
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