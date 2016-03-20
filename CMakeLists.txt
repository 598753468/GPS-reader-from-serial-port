project(Serial)
cmake_minimum_required(VERSION 2.8)
link_libraries (pthread)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set( CMAKE_BUILD_TYPE Debug )
