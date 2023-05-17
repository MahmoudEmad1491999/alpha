cmake_minimum_required(VERSION 3.16)

project(alpha VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/ArrayTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/ListTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/StackTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/QueueTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/TreeTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/BstTest)
