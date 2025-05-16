#== SETTING LIBRARY ==#
add_library(${TEST_LIB} test_manager.cpp)
set_target_properties(${TEST_LIB} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER test_manager.hpp)
# Make header available for other targets in the project.
target_include_directories(${TEST_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} .)
target_compile_features( ${TEST_LIB} PRIVATE cxx_std_17 )
target_compile_options( ${TEST_LIB} PRIVATE -Wall -pedantic -O3)
