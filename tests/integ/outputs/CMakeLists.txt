include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(${PROJECT_NAME}_test_integ_outputs ${SOURCE_FILES})
target_link_libraries(
    ${PROJECT_NAME}_test_integ_outputs
    PRIVATE Catch2::Catch2WithMain ApprovalTests::ApprovalTests ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test_integ_outputs
                           PRIVATE ${${UPPER_PROJECT_NAME}_TEST_INCLUDE_DIR})

if(${UPPER_PROJECT_NAME}_WRITE_JUNIT)
    set(CATCH2_REPORT_OPTIONS
        -r
        junit
        -o
        ${${UPPER_PROJECT_NAME}_JUNIT_DIR}/${PROJECT_NAME}_test_integ_outputs.xml
    )
else()
    set(CATCH2_REPORT_OPTIONS -r console)
endif()

if(POETRY_EXECUTABLE)
    add_test(
        NAME ${PROJECT_NAME}_test_integ_outputs
        COMMAND ${POETRY_EXECUTABLE} run python tests/integ/outputs/run_test.py
                --build_dir ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${${UPPER_PROJECT_NAME}_SOURCE_DIR})
else()
    add_test(
        NAME ${PROJECT_NAME}_test_integ_outputs
        COMMAND ${PROJECT_NAME}_test_integ_outputs ${CATCH2_REPORT_OPTIONS}
        WORKING_DIRECTORY ${${UPPER_PROJECT_NAME}_TEMP_TEST_DIR})
endif()
set_tests_properties(${PROJECT_NAME}_test_integ_outputs
                     PROPERTIES TIMEOUT 180 ENVIRONMENT "TZ=UTC")

add_executable(${PROJECT_NAME}_test_integ_outputs_unity EXCLUDE_FROM_ALL
               unity_source.cpp)
target_link_libraries(
    ${PROJECT_NAME}_test_integ_outputs_unity
    PRIVATE Catch2::Catch2WithMain ApprovalTests::ApprovalTests ${PROJECT_NAME})
