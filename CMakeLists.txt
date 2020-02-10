cmake_minimum_required(VERSION 3.12)

project(SVD_OpenMP)

file(GLOB_RECURSE source_files householder.c utils.c main.c)

add_executable(main ${source_files})

find_package(OpenMP REQUIRED) # Find the package

#target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})
target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)
