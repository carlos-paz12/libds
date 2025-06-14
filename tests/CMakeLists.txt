function(add_data_structure_tests data_structure)
    file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ds/${data_structure}/*.cpp)

    set(TEST_EXECUTABLE "test_${data_structure}")

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

    set_target_properties(${TEST_EXECUTABLE} PROPERTIES
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )

    target_include_directories(${TEST_EXECUTABLE} PRIVATE
        ${CMAKE_SOURCE_DIR}/include/ds/${data_structure}
        ${CMAKE_SOURCE_DIR}/lib/tm
    )

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${TEST_LIB} ds)
endfunction()

add_data_structure_tests(deque)
