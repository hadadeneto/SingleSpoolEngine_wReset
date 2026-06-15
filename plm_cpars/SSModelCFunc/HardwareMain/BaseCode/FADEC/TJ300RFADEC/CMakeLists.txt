cmake_minimum_required(VERSION 2.8)


project(MainBoardFADEC)

find_library(UAVCAN_LIB uavcan REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -pthread")

include_directories(ModelCFunc)

file(GLOB_RECURSE SOURCES
    	ModelCFunc/*.h
    	ModelCFunc/*.c
)

add_executable(MainBoardFADEC MainBoardFADEC.cpp platform_linux.cpp ${SOURCES})

target_link_libraries(MainBoardFADEC ${UAVCAN_LIB} rt)



