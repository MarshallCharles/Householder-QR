cmake_minimum_required(VERSION 3.4)

project(SVD_OpenMP)

file(GLOB_RECURSE source_files householder.c utils.c main.c)

add_executable(main ${source_files})

target_link_libraries(main m)
