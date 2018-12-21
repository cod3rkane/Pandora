cmake_minimum_required (VERSION 3.13)
project(Pandora)

find_package(PkgConfig REQUIRED)
# set(OpenGL_GL_PREFERENCE "GLVND") # to use new openGL version

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES 
  src/Game.cpp
)

add_executable(Pandora ${SOURCE_FILES})
target_link_libraries(Pandora ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY})
