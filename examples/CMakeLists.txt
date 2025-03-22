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

add_example(configurations_customize_hover_texts
            configurations/customize_hover_texts.cpp)
add_example_output(configurations_customize_hover_texts
                   configurations_customize_hover_texts.html)

add_example(configurations_set_error_bars configurations/set_error_bars.cpp)
add_example_output(configurations_set_error_bars
                   configurations_set_error_bars.html)

add_example(configurations_set_axes_to_log_scale
            configurations/set_axes_to_log_scale.cpp)
add_example_output(configurations_set_axes_to_log_scale
                   configurations_set_axes_to_log_scale.html)

add_example(scatter_select_modes scatters/select_modes.cpp)
add_example_output(scatter_select_modes scatter_select_modes.html)

add_example(scatters_plot_many_points_using_web_gl
            scatters/plot_many_points_using_web_gl.cpp)
add_example_output(scatters_plot_many_points_using_web_gl
                   scatters_plot_many_points_using_web_gl.html)
