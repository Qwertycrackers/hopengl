cmake_minimum_required (VERSION 3.1)
project (triangle)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(triangle
  main.cpp
)

target_link_libraries(triangle GL glfw3 X11 Threads::Threads GLEW Xrandr Xi dl)

add_custom_target(resources)
add_custom_command(TARGET resources 
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/*.glsl
    ${CMAKE_CURRENT_BINARY_DIR})

add_dependencies(triangle resources)
