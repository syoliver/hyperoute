cmake_minimum_required(VERSION 3.10)
project(hyperoute_test)

option(WITH_R3 OFF)
find_package(benchmark REQUIRED)

add_executable(hyperoute_bench main_hyperoute.cpp)

if(WITH_R3)
    add_subdirectory(third-parties)
    target_compile_definitions(hyperoute_bench PRIVATE -DWITH_R3)
endif()



target_link_libraries(
    hyperoute_bench
PRIVATE
    hyperoute
    benchmark::benchmark
)

if(WITH_R3)
    target_include_directories(
        hyperoute_bench
    PUBLIC
        third-parties/r3/include
    )


    target_link_libraries(
        hyperoute_bench
    PRIVATE
        r3
    )
endif()


set_target_properties(hyperoute_bench PROPERTIES CXX_STANDARD 17)


add_executable(params_bench main_params.cpp)

target_link_libraries(
    params_bench
PRIVATE
    hyperoute
    benchmark::benchmark
)


set_target_properties(params_bench PROPERTIES CXX_STANDARD 17)
