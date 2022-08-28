include_directories(
    . 
    r3/include
    r3/3rdparty
)
add_definitions(-DHAVE_STRDUP)
add_definitions(-DHAVE_STRNDUP)

add_subdirectory(r3/3rdparty)

# find_library(ZLIB REQUIRED)
# 
# add_library(lib3rdparty INTERFACE)
# 
# target_link_libraries(
#     lib3rdparty INTERFACE ZLIB::ZLIB
# )

add_subdirectory(r3/src)
