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

set_target_properties(hyperoute_test PROPERTIES CXX_STANDARD 17)

add_test(NAME hyperoute_test COMMAND hyperoute_test)


#########################################################

add_executable(translate_route_test translate_route.cpp)

target_link_libraries(
    translate_route_test
PRIVATE
    hyperoute
    Boost::headers
)

target_include_directories(
    translate_route_test
PUBLIC
    ../include/private
)

set_target_properties(translate_route_test PROPERTIES CXX_STANDARD 17)

add_test(NAME translate_route_test COMMAND translate_route_test)

