cmake_minimum_required(VERSION 3.10)
project(
    hyperoute
    VERSION 0.1.0
    DESCRIPTION "Http route library"
    # HOMEPAGE_URL "https://github.com/syoliver/hyperoute"
    LANGUAGES CXX
)

option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARK "Build benchmarks" ON)


include(CTest)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(hyperscan REQUIRED)

add_library(
    hyperoute

    src/builder.cpp
    src/builder_route_modifier.cpp
    src/router.cpp
    src/error.cpp
    src/error_category.cpp
    
    src/context_params.cpp

    src/backend/hyperscan_router.cpp
    src/backend/hyperscan_matcher.cpp
    src/backend/hyperscan.cpp

    src/backend/boost_router.cpp
    src/backend/boost_matcher.cpp
    src/backend/boost.cpp

    src/backend/simple_router.cpp
    src/backend/simple_matcher.cpp
    src/backend/simple.cpp
)


include(GenerateExportHeader)
generate_export_header(
    hyperoute
    BASE_NAME hyperoute
    EXPORT_FILE_NAME export/hyperoute/hyperoute_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(hyperoute PUBLIC HYPEROUTE_STATIC_DEFINE)
endif()


set_target_properties(
    hyperoute PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME hyperoute
    OUTPUT_NAME hyperoute
)

target_include_directories(
    hyperoute

PUBLIC
    include/public
    ${CMAKE_CURRENT_BINARY_DIR}/export

PRIVATE
    include/private
)



set_target_properties(hyperoute PROPERTIES CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(${CMAKE_VERSION} VERSION_LESS "3.14" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        target_link_libraries(hyperoute PRIVATE "-Wl,--exclude-libs,ALL")
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(hyperoute PRIVATE "-Wl,--exclude-libs,ALL")
endif()



#####################################################################

add_library(
    hyperoute_error

STATIC
    src/error.cpp
    src/error_category.cpp
)

target_include_directories(
    hyperoute_error

PUBLIC
    include/public
    ${CMAKE_CURRENT_BINARY_DIR}/export

PRIVATE
    include/private
)

set_target_properties(hyperoute_error PROPERTIES CXX_STANDARD              17
                                                     POSITION_INDEPENDENT_CODE ON)

#####################################################################


add_library(
    hyperoute_translate

STATIC
    src/translate.cpp
)

target_include_directories(
    hyperoute_translate

PUBLIC
    include/public
    ${CMAKE_CURRENT_BINARY_DIR}/export

PRIVATE
    include/private
)

set_target_properties(hyperoute_translate PROPERTIES CXX_STANDARD              17
                                                     POSITION_INDEPENDENT_CODE ON)

#####################################################################

add_library(
    hyperoute_trie

STATIC
    src/route_trie.cpp
)

target_include_directories(
    hyperoute_trie

PUBLIC
    include/public
    ${CMAKE_CURRENT_BINARY_DIR}/export

PRIVATE
    include/private
)

set_target_properties(hyperoute_trie PROPERTIES CXX_STANDARD 17
                                                POSITION_INDEPENDENT_CODE ON)

target_link_libraries(
    hyperoute
PRIVATE
    hyperscan::chimera
    hyperoute_translate
    hyperoute_trie
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()
