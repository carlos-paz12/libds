cmake_minimum_required(VERSION 3.28)

project(libds
    VERSION 1.0
    DESCRIPTION " Library of data structures to C++."
    LANGUAGES CXX
)

# Torna os headers disponíveis como uma 'interface' (sem .cpps para compilar)
add_library(ds INTERFACE)

# Adiciona o caminho para os headers
target_include_directories(ds INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Opcional: define padrão de C++
target_compile_features(ds INTERFACE cxx_std_17)

# Adiciona a biblioteca de testes
set(TEST_LIB test_manager)
add_subdirectory(lib/tm)
