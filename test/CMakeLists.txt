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

target_include_directories(
    hyperoute_test
PUBLIC
    ../include/private
)

set_target_properties(hyperoute_test PROPERTIES CXX_STANDARD 17)
