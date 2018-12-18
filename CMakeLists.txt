cmake_minimum_required (VERSION 3.13)
project(Pandora)

find_package(PkgConfig REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES 
  src/Game.cpp
)

add_executable(Pandora ${SOURCE_FILES})
target_link_libraries(Pandora ${SDL2_LIBRARIES})
