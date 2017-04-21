cmake_minimum_required(VERSION 3.5)
project(cavity_mt)
include_directories(./include /usr/include)
ADD_DEFINITIONS(-g -W -Wall -lrt -lpthread -lstdc++ )
link_directories(/lib/x86_64-linux-gnu)
link_libraries("/usr/lib/x86_64-linux-gnu/librt.so")
SET(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILE     main.cpp
                    include/cav.h src/cav.cpp
                    include/cav_impl.h src/cav_impl.cpp
                    include/handle.h src/handle.cpp
                    include/ocs_sim.h src/ocs_sim.cpp
                    include/pthread_mc.h src/pthread_mc.cpp
                    )

add_executable(cavity_mt ${SOURCE_FILE})