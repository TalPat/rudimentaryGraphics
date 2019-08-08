cmake_minimum_required(VERSION 3.0)
project(renderer)

project(nibbler)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    include_directories(~/.brew/include)
    link_directories(~/.brew/lib)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL REQUIRED sdl2)

include_directories(
  ./include
)

set(SOURCE_FILES 
  ./src/Renderer.cpp
)

add_library(renderer STATIC ${SOURCE_FILES})

include_directories(${SDL_INCLUDE_DIRS})
target_link_libraries(renderer ${SDL_LIBRARIES})

# CMake instructions to test using the static lib

set( TEST_EXE rendererTest )

add_executable( ${TEST_EXE} main.cpp ) 

target_link_libraries( ${TEST_EXE} renderer )