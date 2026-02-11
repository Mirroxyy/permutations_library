cmake_minimum_required(VERSION 3.10)
project(PermutationsProject C)

set(CMAKE_C_STANDARD 99)
# Определение флагов компиляции в зависимости от компилятора
if(MSVC)
    # Флаги для Visual Studio (Windows)
    # /W4 - высокий уровень предупреждений (аналог -Wall -Wextra)
    add_compile_options(/W4)
else()
    # Флаги для GCC/Clang (Linux, macOS, MinGW)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# ==========================================
# 1. СОБИРАЕМ БИБЛИОТЕКУ (ЯДРО)
# ==========================================

# Ищем все .c файлы в алгоритмах и утилитах
# ВАЖНО: Мы НЕ берем main.c сюда, иначе будет ошибка "multiple definition of main"
file(GLOB_RECURSE LIB_SOURCES 
    "src/algorithms/*.c"
    "src/utils/*.c"
    "src/permutation_core.c" 
)

# Создаем статическую библиотеку 'perm_lib'
add_library(perm_lib STATIC ${LIB_SOURCES})

# Говорим CMake, где искать заголовочные файлы (.h)
# PUBLIC означает, что любой, кто использует эту либу, тоже увидит папку include
target_include_directories(perm_lib PUBLIC include)

# ==========================================
# 2. СОБИРАЕМ ГЛАВНОЕ ПРИЛОЖЕНИЕ
# ==========================================
add_executable(app src/main.c)
target_link_libraries(app perm_lib)

# ==========================================
# 3. СОБИРАЕМ БЕНЧМАРКИ
# ==========================================

# Сравнение алгоритмов
if(EXISTS "${CMAKE_SOURCE_DIR}/benchmarks/comparison_benchmark.c")
    add_executable(bench_compare benchmarks/comparison_benchmark.c)
    target_link_libraries(bench_compare perm_lib)
endif()

# Тест памяти
if(EXISTS "${CMAKE_SOURCE_DIR}/benchmarks/memory_benchmark.c")
    add_executable(bench_mem benchmarks/memory_benchmark.c)
    target_link_libraries(bench_mem perm_lib)
endif()

# Тест производительности
if(EXISTS "${CMAKE_SOURCE_DIR}/benchmarks/performance_benchmark.c")
    add_executable(bench_perf benchmarks/performance_benchmark.c)
    target_link_libraries(bench_perf perm_lib)
endif()