cmake_minimum_required(VERSION 2.8)


project(MainBoardFADEC)

find_library(UAVCAN_LIB uavcan REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -pthread")

include_directories(FADEC_Defines_H)
include_directories(FADEC_Functions_C)
include_directories(FADEC_Functions_H)
include_directories(TJ200)

file(GLOB_RECURSE SOURCES
        FADEC_Defines_H/*.h
        FADEC_Functions_C/*.c
        FADEC_Functions_H/*.h
        TJ200/*.c
        TJ200/*.h
)

add_executable(MainBoardFADEC MainBoardFADEC.cpp platform_linux.cpp ${SOURCES})

target_link_libraries(MainBoardFADEC ${UAVCAN_LIB} rt)



