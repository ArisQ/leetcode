cmake_minimum_required(VERSION 2.8)
project(37-sudoku-solver)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
