include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(${PROJECT_NAME}_test_integ_traces ${SOURCE_FILES})
target_add_catch2(${PROJECT_NAME}_test_integ_traces)
target_link_libraries(${PROJECT_NAME}_test_integ_traces PRIVATE Eigen3::Eigen)

add_executable(${PROJECT_NAME}_test_integ_traces_unity EXCLUDE_FROM_ALL
               unity_source.cpp)
target_link_libraries(
    ${PROJECT_NAME}_test_integ_traces_unity
    PRIVATE Catch2::Catch2WithMain ApprovalTests::ApprovalTests Eigen3::Eigen
            ${PROJECT_NAME})
