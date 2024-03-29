cmake_minimum_required(VERSION 3.15)
project(cgame)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(
  cgame
  main.cpp
  src/core/Application.cpp
  src/core/Application.h
  src/core/Game.cpp
  src/core/Game.h
  src/util/registry.h
  src/components/Render.h
  src/components/Shader.h
  src/util/files.h
  src/system/render.cpp
  src/system/render.h
  src/util/files.cpp
  src/util/stb_image.h
  src/components/Transform.h
  src/system/transformations.cpp
  src/system/transformations.h
  src/util/Camera.cpp
  src/util/Camera.h
  src/system/interactions.cpp
  src/system/interactions.h
  src/core/Terrain.cpp
  src/core/Terrain.h
  src/core/UIManager.cpp
  src/core/UIManager.h
  src/core/ui/UIComponent.cpp
  src/core/ui/UIComponent.h
  src/core/Shader.cpp
  src/core/Shader.h
  src/util/Maths.h
  src/core/Window.cpp
  src/core/Window.h
  src/core/ui/Button.cpp
  src/core/ui/Button.h
        src/core/ui/CoreComponent.cpp src/core/ui/CoreComponent.h src/core/ui/Constraints.cpp src/core/ui/Constraints.h src/core/game-state/GameState.h src/gui/MainMenu.cpp src/gui/MainMenu.h src/gui/InventoryBar.cpp src/gui/InventoryBar.h)

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(external/entt/include)
include_directories(external/glm/include)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
target_include_directories(cgame PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(cgame glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${OPENGL_gl_LIBRARY})
