cmake_minimum_required(VERSION 3.5)
project(cavity_mt)
include_directories(./include /usr/include)
ADD_DEFINITIONS(-g -W -Wall -lrt -lpthread)
link_directories(/lib/x86_64-linux-gnu)
SET(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILES   include/cav_impl.h
                    src/cav_impl.cpp
                    src/pthread_mc.cpp
                    include/pthread_mc.h
                    src/cav.cpp
                    include/cav.h
                    include/handle.h
                    src/ocs_sim.cpp
        include/ocs_sim.h)

add_executable(cavity_mt ${SOURCE_FILES} )