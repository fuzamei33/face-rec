cmake_minimum_required(VERSION 3.9)
project(facedlib)

set(CMAKE_CXX_STANDARD 11)
ADD_SUBDIRECTORY(src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
add_executable(facedlib main.cpp)
target_link_libraries(facedlib givefacerec)
