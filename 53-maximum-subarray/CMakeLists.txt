cmake_minimum_required(VERSION 2.8)
project(53-maximum-subarray)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
