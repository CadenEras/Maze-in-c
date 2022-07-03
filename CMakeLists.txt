cmake_minimum_required(VERSION 3.22)
project(maze_test C)

set(SOURCE_FILES main.c)
set(CMAKE_C_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/Users/gries/Downloads/SDL2-2.0.22/include)
set(SDL2_LIB_DIR C:/Users/gries/Downloads/SDL2-2.0.22/lib/x64)
set(SDL2_IMAGE_INCLUDE_DIR C:/Users/gries/Downloads/SDL2_image-2.0.5/include)
set(SDL2_IMAGE_LIB_DIR C:/Users/gries/Downloads/SDL2_image-2.0.5/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(maze_test main.c maze.c textures.c drawMap.c drawMap.h map.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image.dll)