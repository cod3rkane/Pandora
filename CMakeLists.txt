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
    src/Game.h
    src/Game.cpp
    src/core/Window.h
    src/core/StbImage.h
    src/core/Texture.h
    src/core/Texture.cpp
    src/core/Object.h
    src/core/Sprite.h
    src/core/Sprite.cpp
    src/core/Player.h
    src/core/Player.cpp
    src/core/Clock.h
    src/core/TileMap.h
    src/core/TileMap.cpp
    src/core/Tile.h
    src/core/Tile.cpp
)

add_executable(PuzzleGame ${SOURCE_FILES})

# Third Party libraries
set(OpenGL_GL_PREFERENCE "GLVND") # preference to the new openGL

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(${GLM_DEFINITIONS})

target_link_libraries(PuzzleGame
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARY}
    ${GLM_LIBRARY_DIRS}
    )

