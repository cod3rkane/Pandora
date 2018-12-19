cmake_minimum_required (VERSION 3.13)
project(Pandora)

find_package(PkgConfig REQUIRED)

# set(OpenGL_GL_PREFERENCE "GLVND") # to use new openGL version

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES 
  src/Game.cpp
  src/management/Render.h
  src/management/Render.cpp
  src/core/GridMap.h
  src/core/GridMap.cpp
)

add_executable(Pandora ${SOURCE_FILES})
target_link_libraries(Pandora ${SDL2_LIBRARIES})
