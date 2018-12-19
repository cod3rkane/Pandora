cmake_minimum_required (VERSION 3.13)
project(Pandora)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

# set(OpenGL_GL_PREFERENCE "GLVND") # to use new openGL version

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

include_directories(${GLUT_INCLUDE_DIRS})

set(SOURCE_FILES 
  src/Game.cpp
  src/management/Render.h
  src/management/Render.cpp
  src/core/GridMap.h
  src/core/GridMap.cpp
)

add_executable(Pandora ${SOURCE_FILES})
target_link_libraries(Pandora ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY})
