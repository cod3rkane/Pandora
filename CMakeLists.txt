cmake_minimum_required (VERSION 3.8)
project (Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

set(SOURCE_FILES
	src/main.cpp
  include/glad.c
  src/util/registry.hpp
  src/core/app.hpp
  src/core/app.cpp
)

add_executable(Game ${SOURCE_FILES})

# Third Party libraries
set(OpenGL_GL_PREFERENCE "GLVND") # preference to the new openGL

target_include_directories(Game
  PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/src"
  )

find_package(PkgConfig REQUIRED)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(${GLM_DEFINITIONS})

target_link_libraries(Game
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARY}
    ${GLM_LIBRARY_DIRS}
    -ldl
    )

