cmake_minimum_required(VERSION 3.4)

project(SVD_OpenMP)

file(GLOB_RECURSE source_files householder.c utils.c)


add_executable(householder ${source_files})

target_link_libraries(householder m)