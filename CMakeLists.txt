cmake_minimum_required(VERSION 2.8)

project(OGL)

set (CMAKE_CXX_STANDARD 11)
set (EXECUTABLE_OUTPUT_PATH bin)

add_executable(ogl 
    src/main.cpp
    src/geometry.cpp
    src/glad.c

    include/utils.h
    include/shader.h)

add_custom_command(
    TARGET ogl 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/shaders
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.1 REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLFW_INCLUDE_DIRS} include )

target_link_libraries(ogl ${OPENGL_LIBRARIES} glfw ${CMAKE_DL_LIBS})