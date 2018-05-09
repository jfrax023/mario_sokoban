cmake_minimum_required(VERSION 3.10)
project(mario_sokoban C)

set(CMAKE_C_STANDARD 99)

# Set include directory
include_directories(include)
# Get all .c file located in src directory and name it src_file also get .h located in include
file(GLOB_RECURSE src_files src/*.c *.h)

# Get SDL lib
find_package(SDL REQUIRED)
# Check with a sdl variable
if(!SDL_FOUND)
    message(FATAL_ERROR "Lib SDL not found")
endif()
# Get SDL_image lib
find_package(SDL_image)
if(!SDL_IMAGE_FOUND)
    message(FATAL_ERROR "Lib SDL_image not found")
endif ()
# Included directories from a path variable
include_directories(${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS})
# Included executable by using a defined variable set at top
add_executable(mario_sokoban main.c ${src_files})