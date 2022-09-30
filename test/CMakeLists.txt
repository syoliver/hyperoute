cmake_minimum_required(VERSION 3.10)
project(hyperoute_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

find_package(turtle REQUIRED)

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

add_test(NAME hyperoute_test COMMAND hyperoute_test)


#########################################################

add_executable(context_params_test context_params.cpp)

target_link_libraries(
    context_params_test
PRIVATE
    hyperoute
    Boost::headers
)


set_target_properties(context_params_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_test(NAME context_params_test COMMAND context_params_test)

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

add_test(NAME translate_route_test COMMAND translate_route_test)


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

add_test(NAME route_trie_test COMMAND route_trie_test)


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

add_test(NAME google_api_test COMMAND google_api_test)

#########################################################

add_executable(github_api_test github_api.cpp)

target_link_libraries(
    github_api_test
PRIVATE
    hyperoute
    Boost::headers
    turtle::turtle
)

set_target_properties(github_api_test PROPERTIES CXX_STANDARD ${HYPEROUTE_CXX_STANDARD})

add_test(NAME github_api_test COMMAND github_api_test)