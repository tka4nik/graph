cmake_minimum_required(VERSION 3.20)
project(Graph)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(googletests_graph)
add_executable(maindir source/main.cpp)

#links all of graph to maindir
target_include_directories(maindir PUBLIC graph/)