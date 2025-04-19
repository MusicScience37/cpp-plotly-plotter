include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${${UPPER_PROJECT_NAME}_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
           $<BUILD_INTERFACE:${${UPPER_PROJECT_NAME}_GENERATED_HEADER_DIR}>)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC yyjson::yyjson fmt::fmt
                           $<BUILD_INTERFACE:${PROJECT_NAME}_cpp_warnings>)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd4251)
endif()

# Configurations to use as libraries.
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES C_VISIBILITY_PRESET hidden
               CXX_VISIBILITY_PRESET hidden
               VISIBILITY_INLINES_HIDDEN 1
               DEBUG_POSTFIX d
               VERSION ${PROJECT_VERSION})
include(GenerateExportHeader)
generate_export_header(
    ${PROJECT_NAME}
    EXPORT_FILE_NAME
        "${${UPPER_PROJECT_NAME}_GENERATED_HEADER_DIR}/${PROJECT_NAME}/details/${PROJECT_NAME}_export.h"
)

if(${UPPER_PROJECT_NAME}_USE_UNIX_SUBPROCESS)
    set(PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS_BIN 1)
else()
    set(PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS_BIN 0)
endif()
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${${UPPER_PROJECT_NAME}_GENERATED_HEADER_DIR}/${PROJECT_NAME}/details/config.h
)

# For clang-tidy.
add_library(${PROJECT_NAME}_unity EXCLUDE_FROM_ALL unity_source.cpp)
target_include_directories(
    ${PROJECT_NAME}_unity
    PUBLIC $<BUILD_INTERFACE:${${UPPER_PROJECT_NAME}_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
           $<BUILD_INTERFACE:${${UPPER_PROJECT_NAME}_GENERATED_HEADER_DIR}>)
target_link_libraries(
    ${PROJECT_NAME}_unity
    PUBLIC yyjson::yyjson fmt::fmt
           $<BUILD_INTERFACE:${PROJECT_NAME}_cpp_warnings>)
target_compile_features(${PROJECT_NAME}_unity PUBLIC cxx_std_17)
