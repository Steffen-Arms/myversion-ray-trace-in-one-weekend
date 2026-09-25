cmake_minimum_required(VERSION 4.4)

# Turn on the experimental 'import std' support.
# This UUID belongs to CMake 4.4.3. It must come BEFORE project().
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)

add_executable(raytracer src/main.cpp)
target_sources(raytracer PRIVATE
    FILE_SET CXX_MODULES FILES src/vec3.cppm
)
