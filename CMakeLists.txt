cmake_minimum_required (VERSION 3.13)
project (Pandora)

find_package(PkgConfig REQUIRED)

set(SOURCE_FILES 
  src/Game.cpp
)

add_executable(Pandora ${SOURCE_FILES})

# include_directories(${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
# target_link_libraries(Lov ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} SOIL ${FREETYPE_LIBRARIES} ${GLUT_LIBRARY})
