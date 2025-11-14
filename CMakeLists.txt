cmake_minimum_required(VERSION 4.0)
project(voxel-game LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (voxel-game
    src/main.cpp
    src/glad.c
)

target_include_directories(voxel-game PRIVATE include)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_link_libraries(voxel-game PRIVATE
    ${OpenGL_LIBS}
    ${GLFW_LIBRARIES}
)
