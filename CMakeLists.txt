cmake_minimum_required(VERSION 3.10)
project(hyperoute)

option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARK "Build benchmarks" ON)


include(CTest)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(hyperscan REQUIRED)

add_library(
    hyperoute

    src/translate.cpp
    src/builder.cpp
    src/builder_route_modifier.cpp
    src/router.cpp
    src/error.cpp
    src/error_category.cpp

    src/context_params.cpp
    src/route_trie.cpp

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
)

set_target_properties(hyperoute PROPERTIES CXX_STANDARD 17)


if(BUILD_TESTING)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()
