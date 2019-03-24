cmake_minimum_required (VERSION 3.13)
project(Pandora)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

find_package(Lua REQUIRED lua)
include_directories(${LUA_INCLUDE_DIR})
# set(OpenGL_GL_PREFERENCE "GLVND") # to use new openGL version

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

# find_package(glfw3 3.2 REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)
# include_directories(${GLFW_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES 
  src/Game.cpp
  src/core/StbImage.h
  src/core/sol.hpp
)

add_executable(Pandora ${SOURCE_FILES})
target_link_libraries(Pandora ${LUA_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY})
