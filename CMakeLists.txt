cmake_minimum_required(VERSION 3.22)
project(libds VERSION 1.0 DESCRIPTION "Library of data structures in C++." LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall # Avisos comuns
    -Wextra # Avisos adicionais
    -Wpedantic # Fiel ao padrão C++
    -Wconversion # Conversões implícitas suspeitas
    -Wshadow # Variáveis que escondem outras
    -Wnon-virtual-dtor # Classes base com destrutores não-virtuais
    -Wold-style-cast # Casts no estilo C
    -Wnull-dereference # Acesso a ponteiros nulos
    -Wextra-semi # Ponto-e-vírgula desnecessário
    -O2 # Otimização equilibrada
)

add_library(ds INTERFACE)
target_include_directories(ds INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set(TEST_LIB test_manager)
add_subdirectory(lib/tm)

set(TEST_DRIVER test_driver)
add_subdirectory(tests)
