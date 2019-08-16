cmake_minimum_required(VERSION 2.8)
project(106-construct-binary-tree-from-inorder-and-postorder-traversal)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
