cmake_minimum_required(VERSION 2.8)


project(MainBoardModel)

find_library(UAVCAN_LIB uavcan REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -pthread")

include_directories(FADEC_Defines_H)
include_directories(FADEC_Functions_C)
include_directories(FADEC_Functions_H)
include_directories(GEJ85)
include_directories(GET700)
include_directories(HIL_Functions_C)
include_directories(HIL_Functions_H)
include_directories(TF1200)
include_directories(TG200)
include_directories(TJ1200)
include_directories(TJ200)
include_directories(TJ300AR)
include_directories(TJ300R)
include_directories(TJ40)
include_directories(TJ700)

file(GLOB_RECURSE SOURCES
        FADEC_Defines_H/*.h
        FADEC_Functions_C/*.c
        FADEC_Functions_H/*.h
        GEJ85/*.c
        GEJ85/*.h
        GET700/*.c
        GET700/*.h
        HIL_Functions_C/*.c
        HIL_Functions_H/*.h
        TF1200/*.c
        TF1200/*.h
        TG200/*.c
        TG200/*.h
        TJ1200/*.c
        TJ1200/*.h
        TJ200/*.c
        TJ200/*.h
        TJ300AR/*.c
        TJ300AR/*.h
        TJ300R/*.c
        TJ300R/*.h
        TJ40/*.c
        TJ40/*.h
        TJ700/*.c
        TJ700/*.h
)

add_executable(MainBoardModel MainBoardModel.cpp platform_linux.cpp ${SOURCES})

target_link_libraries(MainBoardModel ${UAVCAN_LIB} rt)



