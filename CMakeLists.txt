cmake_minimum_required(VERSION 3.15)
project(cgame)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(cgame main.cpp src/core/Application.cpp src/core/Application.h src/core/Game.cpp src/core/Game.h src/util/registry.h src/components/Render.h src/components/Shader.h src/util/files.h src/system/render.cpp src/system/render.h src/util/files.cpp src/util/stb_image.h src/components/Transform.h src/system/transformations.cpp src/system/transformations.h src/util/Camera.cpp src/util/Camera.h)

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(external/entt/include)
include_directories(external/glm/include)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
target_include_directories(cgame PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(cgame glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${OPENGL_gl_LIBRARY})
