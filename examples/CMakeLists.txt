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

add_example(simple_plot get_started/simple_plot.cpp)
add_example_output(simple_plot simple_plot.html)

add_example(add_titles get_started/add_titles.cpp)
add_example_output(add_titles add_titles.html)

add_example(use_figure_builder get_started/use_figure_builder.cpp)
add_example_output(use_figure_builder use_figure_builder.html)

add_example(boxes_create_simple_box boxes/create_simple_box.cpp)
add_example_output(boxes_create_simple_box boxes_create_simple_box.html)

add_example(boxes_create_multiple_boxes boxes/create_multiple_boxes.cpp)
add_example_output(boxes_create_multiple_boxes boxes_create_multiple_boxes.html)

add_example(boxes_show_mean_and_stddev boxes/show_mean_and_stddev.cpp)
add_example_output(boxes_show_mean_and_stddev boxes_show_mean_and_stddev.html)

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

add_example(scatter_create_scatter_using_figure_builder
            scatters/create_scatter_using_figure_builder.cpp)
add_example_output(scatter_create_scatter_using_figure_builder
                   scatter_create_scatter_using_figure_builder.html)

add_example(scatter_select_modes scatters/select_modes.cpp)
add_example_output(scatter_select_modes scatter_select_modes.html)

add_example(scatters_plot_many_points_using_web_gl
            scatters/plot_many_points_using_web_gl.cpp)
add_example_output(scatters_plot_many_points_using_web_gl
                   scatters_plot_many_points_using_web_gl.html)

add_example(violins_create_simple_violin violins/create_simple_violin.cpp)
add_example_output(violins_create_simple_violin
                   violins_create_simple_violin.html)

add_example(violins_create_multiple_violins violins/create_multiple_violins.cpp)
add_example_output(violins_create_multiple_violins
                   violins_create_multiple_violins.html)

add_example(violins_show_box_and_mean violins/show_box_and_mean.cpp)
add_example_output(violins_show_box_and_mean violins_show_box_and_mean.html)
