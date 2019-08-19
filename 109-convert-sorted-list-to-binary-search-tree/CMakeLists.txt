cmake_minimum_required(VERSION 2.8)
project(109-convert-sorted-list-to-binary-search-tree)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
