cmake_minimum_required(VERSION 3.10)
project(hyperoute)

option(BUILD_TEST ON)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(hyperscan REQUIRED)

add_library(
    hyperoute
    
    src/translate.cpp
    src/builder.cpp
    src/router.cpp

    src/route_scratch.cpp
)

target_include_directories(
    hyperoute
PUBLIC
    include/public
PRIVATE
    include/private
)

target_link_libraries(
    hyperoute
PRIVATE
    hyperscan::chimera
)

set_target_properties(hyperoute PROPERTIES CXX_STANDARD 17)

add_subdirectory(test)