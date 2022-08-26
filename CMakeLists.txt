cmake_minimum_required(VERSION 3.10)
project(hyperoute)

option(BUILD_TEST ON)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(hyperscan REQUIRED)
find_package(robin_hood REQUIRED)
add_library(
    hyperoute
    
    src/translate.cpp
    src/builder.cpp
    src/builder_route_modifier.cpp
    src/router.cpp

    src/backend/hyperscan_router.cpp
    src/backend/hyperscan_matcher.cpp
    src/backend/hyperscan.cpp

    src/backend/boost_router.cpp
    src/backend/boost_matcher.cpp
    src/backend/boost.cpp
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
    robin_hood::robin_hood
)

set_target_properties(hyperoute PROPERTIES CXX_STANDARD 17)

add_subdirectory(test)