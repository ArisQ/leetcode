cmake_minimum_required(VERSION 2.8)
project(48-rotate-image)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
