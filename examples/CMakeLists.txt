option(${UPPER_PROJECT_NAME}_TEST_EXAMPLES
       "test examples of ${FULL_PROJECT_NAME}" OFF)

function(add_example TARGET)
    add_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME})
    if(${UPPER_PROJECT_NAME}_TESTING AND ${UPPER_PROJECT_NAME}_TEST_EXAMPLES)
        add_test(NAME ${TARGET} COMMAND ${TARGET})
    endif()
endfunction()

add_example(simple_plot simple_plot.cpp)
add_example(add_titles add_titles.cpp)
