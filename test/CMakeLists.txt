cmake_minimum_required(VERSION 3.10)
project(hyperoute_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

find_package(turtle REQUIRED)

set(TEST_OUTPUT_EXTENSION "txt")
if(TEST_OUTPUT STREQUAL "XML" OR TEST_OUTPUT STREQUAL "JUNIT")
    set(TEST_OUTPUT_EXTENSION "xml")
endif()

macro(add_hyperoute_test)
    cmake_parse_arguments(ADD_HYPEROUTE_TEST "BY_PASS" "NAME" ""  ${ARGN})

    unset(valgrind_launcher)
    if(TEST_WITH_VALGRIND AND NOT ADD_HYPEROUTE_TEST_BY_PASS)
        set(valgrind_launcher valgrind --leak-check=full --xml=yes --xml-file=valgrind_${ADD_HYPEROUTE_TEST_NAME}.xml)
    endif()

    add_test(NAME ${ADD_HYPEROUTE_TEST_NAME} COMMAND ${valgrind_launcher} ./${ADD_HYPEROUTE_TEST_NAME} --log_format=${TEST_OUTPUT} --log_level=all --log_sink=test_${ADD_HYPEROUTE_TEST_NAME}.${TEST_OUTPUT_EXTENSION})
endmacro()


add_executable(hyperoute_test main.cpp)

target_link_libraries(
    hyperoute_test
PRIVATE
    hyperoute
    #Boost::unit_test_framework
    Boost::headers
    turtle::turtle
)

target_compile_definitions(
    hyperoute_test
PUBLIC
    _CRTDBG_MAP_ALLOC
)
set_target_properties(hyperoute_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_hyperoute_test(NAME hyperoute_test)

#########################################################

add_executable(context_params_test context_params.cpp)

target_link_libraries(
    context_params_test
PRIVATE
    hyperoute
    Boost::headers
)


set_target_properties(context_params_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_hyperoute_test(NAME context_params_test)

#########################################################

add_executable(translate_route_test translate_route.cpp)

target_link_libraries(
    translate_route_test
PRIVATE
    hyperoute_translate
    hyperoute_error
    Boost::headers
)

target_include_directories(
    translate_route_test
PUBLIC
    ../include/private
)

set_target_properties(translate_route_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_hyperoute_test(NAME translate_route_test)


#########################################################

add_executable(route_trie_test route_trie.cpp)

target_link_libraries(
    route_trie_test
PRIVATE
    hyperoute_trie
    hyperoute_error
    Boost::headers
)

target_include_directories(
    route_trie_test
PUBLIC
    ../include/private
)

set_target_properties(route_trie_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_hyperoute_test(NAME route_trie_test)


#########################################################

add_executable(google_api_test google_api.cpp)

target_link_libraries(
    google_api_test
PRIVATE
    hyperoute
    Boost::headers
    turtle::turtle
)

set_target_properties(google_api_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_hyperoute_test(NAME google_api_test)

#########################################################

add_executable(github_api_test github_api.cpp)

target_link_libraries(
    github_api_test
PRIVATE
    hyperoute
    Boost::headers
    turtle::turtle
)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set_source_files_properties(github_api.cpp PROPERTIES COMPILE_OPTIONS /bigobj)
endif()

set_target_properties(github_api_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

# Bypass valgrind on github because it leads to timeout
add_hyperoute_test(NAME github_api_test BY_PASS TRUE)
