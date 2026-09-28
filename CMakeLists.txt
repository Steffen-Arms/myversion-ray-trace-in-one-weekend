cmake_minimum_required(VERSION 3.28)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Microsoft.GSL CONFIG REQUIRED)

# Collect all .cpp files in src/ and its subfolders
file(GLOB_RECURSE RAYTRACER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(raytracer ${RAYTRACER_SOURCES}
    src/ray.h)

target_link_libraries(raytracer PRIVATE Microsoft.GSL::GSL)

# Lets you write #include "vec3.hpp" from any file in src/
target_include_directories(raytracer PRIVATE src)
