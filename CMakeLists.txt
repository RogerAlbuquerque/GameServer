# 1. Define a versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# 2. Define o nome do projeto e a linguagem
project(MeuProjeto CXX)

# Procura recursivamente por todos os arquivos .cpp e .h na pasta atual e subpastas
file(GLOB_RECURSE FONTES_PROJETO "Src/*.cpp" "Src/*.h")

# 3. Especifica o nome do executável e os arquivos de origem
add_executable(meu_executavel ${FONTES_PROJETO})

target_include_directories(meu_executavel PRIVATE Src/headers)