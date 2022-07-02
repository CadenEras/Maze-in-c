cmake_minimum_required(VERSION 3.22)
project(maze_test C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.c)
set(CMAKE_C_STANDARD 17)

add_executable(maze_test main.c)

target_link_libraries(mingw32 SDL2main SDL2)