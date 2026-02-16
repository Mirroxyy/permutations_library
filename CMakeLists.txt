cmake_minimum_required(VERSION 3.10)
project(PermutationsProject C)

set(CMAKE_C_STANDARD 99)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# ==========================================
# 1. СОБИРАЕМ БИБЛИОТЕКУ perm_lib
# ==========================================

# Автоматически собираем ВСЕ .c файлы, кроме main.c
file(GLOB_RECURSE LIB_SOURCES
    "src/algorithms/*.c"
    "src/core/*.c"
    "src/tests/*.c"
)

# Удаляем main.c, если он случайно попал в список
list(FILTER LIB_SOURCES EXCLUDE REGEX "main\\.c$")

add_library(perm_lib STATIC ${LIB_SOURCES})

target_include_directories(perm_lib PUBLIC include)

# ==========================================
# 2. ПРИЛОЖЕНИЕ
# ==========================================

add_executable(app src/main.c)
target_link_libraries(app perm_lib)

# ==========================================
# 3. БЕНЧМАРКИ (если существуют)
# ==========================================

foreach(BENCH_FILE
    "benchmarks/comparison_benchmark.c"
    "benchmarks/memory_benchmark.c"
    "benchmarks/performance_benchmark.c"
)
    if(EXISTS "${CMAKE_SOURCE_DIR}/${BENCH_FILE}")
        get_filename_component(BENCH_NAME ${BENCH_FILE} NAME_WE)
        add_executable(${BENCH_NAME} ${BENCH_FILE})
        target_link_libraries(${BENCH_NAME} perm_lib)
    endif()
endforeach()
