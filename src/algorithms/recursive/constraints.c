#include "permutations.h"

static bool stop_generation = false;

static void constraint_helper(int arr[], int n, bool used[], int current[], int depth,
                             bool (*constraint)(int[], int, int, void*),
                             void* data, void (*callback)(int[], int)) {
    if (stop_generation) return;
    if (depth == n) {
        callback(current, n);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            // Forward checking: проверяем ограничение до входа в рекурсию
            if (constraint(current, depth, arr[i], data)) {
                used[i] = true;
                current[depth] = arr[i];
                constraint_helper(arr, n, used, current, depth + 1, constraint, data, callback);
                used[i] = false;
            }
        }
    }
}

void permutations_with_constraints(int arr[], int n,
                                    memory_pool_t* pool,
                                    bool (*constraint)(int[], int, int, void*),
                                    void* constraint_data,
                                    void (*callback)(int[], int)) {
    if (n <= 0 || arr == NULL) return;

    size_t initial_offset = pool->offset;

    bool* used = (bool*)pool_alloc(n * sizeof(bool));
    int* current = (int*)pool_alloc(n * sizeof(int));

    memset(used, 0, n * sizeof(bool));

    reset_stop_flag();
    constraint_helper(arr, n, used, current, 0, constraint, constraint_data, callback);

    pool->offset = initial_offset;
}

// Позиционные (элемент i не может быть на позиции j)
bool pos_constraint(int partial[], int k, int next, void* data) {
    ConstraintRules* rules = (ConstraintRules*)data;
    if (rules->forbidden_map[k][0] == 1 && next == rules->forbidden_map[k][1]){
        return false;
    }
    return true;
}

//Относительные (элемент x должен быть перед элементом y)

bool rel_constraint(int partial[], int k, int next, void* data){
    ConstraintRules* rules = (ConstraintRules*)data;
    int bef_var = rules->must_follow[0];
    int aft_const = rules->must_follow[1];
    bool f = false;
    if (next == bef_var){
        for (int i = 0; i < k; i ++){
            if (partial[i] == aft_const) f = true;
    }
        if (f == true) return false;
    }
    return true;
}