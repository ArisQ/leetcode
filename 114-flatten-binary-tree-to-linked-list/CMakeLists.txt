cmake_minimum_required(VERSION 2.8)
project(114-flatten-binary-tree-to-linked-list)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
