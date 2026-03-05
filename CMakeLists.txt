cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_COMPILER clang++)
project(OGL)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_USE_HUNTER ON)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/assimp)
include_directories(libs/stb)

find_package(OpenGL REQUIRED)

add_executable(OGL src/main.cpp)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE MODULES_SOURCE interfaces/*.ixx)
target_sources(OGL PRIVATE ${SOURCES}
        PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
        ${MODULES_SOURCE}
        libs/glm/glm/glm.cppm
)

target_link_libraries(OGL
        glfw
        glad
        OpenGL::GL
        assimp::assimp
        ${CMAKE_DL_LIBS}
)