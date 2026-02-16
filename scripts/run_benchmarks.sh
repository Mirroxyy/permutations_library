#!/bin/bash

# Получаем абсолютный путь к директории, где лежит сам скрипт
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Корень проекта — это папка выше скриптов
PROJECT_ROOT="$( cd "$SCRIPT_DIR/.." && pwd )"

# Цвета для красоты
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${BLUE}=== Permutation Library: Full Automation ===${NC}"

# 1. Сборка
echo -e "\n${GREEN}[1/4] Building project...${NC}"
mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build" || exit

# Запускаем cmake, указывая на корень проекта
cmake "$PROJECT_ROOT" > /dev/null
make -j$(nproc) > /dev/null

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

# 2. Запуск бенчмарков (теперь мы точно в build)
echo -e "\n${GREEN}[2/4] Running Performance Benchmarks...${NC}"
if [ -f "./performance_benchmark" ]; then
    ./performance_benchmark
else
    echo -e "${RED}performance_benchmark not found!${NC}"
fi

echo -e "\n${GREEN}[3/4] Running Memory Benchmarks...${NC}"
if [ -f "./memory_benchmark" ]; then
    ./memory_benchmark
else
    echo -e "${RED}memory_benchmark not found!${NC}"
fi

# 3. Генерация отчета/графа
echo -e "\n${GREEN}[4/4] Running Comparison & Generating Graph...${NC}"
if [ -f "./comparison_benchmark" ]; then
    ./comparison_benchmark
fi

# Проверяем, создался ли граф (если твой app/benchmark его генерит)
if [ -f "graph.png" ]; then
    echo -e "${BLUE}Graph generated successfully in build/graph.png${NC}"
fi

echo -e "\n${BLUE}===========================================${NC}"