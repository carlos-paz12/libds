add_library(${TEST_LIB} test_manager.cpp)

set_target_properties(${TEST_LIB} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER test_manager.hpp
)

target_include_directories(${TEST_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
