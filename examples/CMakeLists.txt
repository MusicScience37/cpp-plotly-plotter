option(${UPPER_PROJECT_NAME}_TEST_EXAMPLES
       "test examples of ${FULL_PROJECT_NAME}" OFF)

set(${UPPER_PROJECT_NAME}_EXAMPLE_OUTPUTS_DIR
    ${${UPPER_PROJECT_NAME}_SOURCE_DIR}/doc/sphinx/src/examples/outputs)

function(add_example TARGET SOURCE)
    add_executable(${TARGET} ${SOURCE})
    target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME})
    if(${UPPER_PROJECT_NAME}_TESTING AND ${UPPER_PROJECT_NAME}_TEST_EXAMPLES)
        add_test(NAME ${TARGET} COMMAND ${TARGET})
    endif()
endfunction()
function(add_example_output TARGET OUTPUT_NAME)
    if(${UPPER_PROJECT_NAME}_BUILD_DOC)
        add_custom_command(
            OUTPUT ${${UPPER_PROJECT_NAME}_EXAMPLE_OUTPUTS_DIR}/${OUTPUT_NAME}
            COMMAND ${TARGET}
            DEPENDS ${TARGET}
            WORKING_DIRECTORY ${${UPPER_PROJECT_NAME}_EXAMPLE_OUTPUTS_DIR}
            COMMENT "Running example ${TARGET}.")
        add_custom_target(
            ${TARGET}_output ALL
            DEPENDS ${${UPPER_PROJECT_NAME}_EXAMPLE_OUTPUTS_DIR}/${OUTPUT_NAME})
        if(${UPPER_PROJECT_NAME}_BUILD_DOC_SPHINX)
            add_dependencies(${PROJECT_NAME}_doc_sphinx_html ${TARGET}_output)
        endif()
    endif()
endfunction()

add_example(simple_plot simple_plot.cpp)
add_example_output(simple_plot simple_plot.html)

add_example(add_titles add_titles.cpp)
add_example_output(add_titles add_titles.html)
