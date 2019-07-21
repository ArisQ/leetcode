cmake_minimum_required(VERSION 2.8)
project(30-substring-with-concatenation-of-all-words)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
