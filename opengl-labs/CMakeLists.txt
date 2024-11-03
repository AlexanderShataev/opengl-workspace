cmake_minimum_required(VERSION 3.0.0)   # Selects the minimum version of CMake required to run this file
project(GL_LABS VERSION 0.0.1)          # Here we select the project name and version

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)        # Don't build Documentation
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)       # Don't build Tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)    # Don't build Examples
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)           # Don't build Installation Information
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)     # Add variables to use High Performance Graphics Card if available
add_subdirectory(vendor/glfw)                       # Build the GLFW project to use later as a library

set(GLAD_SOURCE vendor/glad/src/gl.c)
set(VENDOR_SOURCES ${GLAD_SOURCE} ${IMGUI_SOURCES})

include_directories(
        vendor/
        vendor/glfw/include
        vendor/glad/include
        vendor/glm
        vendor/imgui
        vendor/utils
        library/
)


set(GL_LAB_LIBRARY
    library/shader.h
    library/shader.cpp
    library/sb_image_imp.cpp
)


add_executable(GL_LAB1_TEXTURES ${GL_LAB_LIBRARY} ${VENDOR_SOURCES} labs/l1-textures/l1_textures.cpp)
target_link_libraries(GL_LAB1_TEXTURES glfw)

