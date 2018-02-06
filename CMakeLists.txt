cmake_minimum_required(VERSION 3.9)
project(facedlib)

set(CMAKE_CXX_STANDARD 11)
ADD_SUBDIRECTORY(src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

add_executable(main main.cpp)
add_executable(facerec facerec.cpp)
add_executable(identify identify.cpp)

target_link_libraries(main givefacerec)
target_link_libraries(facerec givefacerec)
target_link_libraries(identify givefacerec)
