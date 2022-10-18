file(
    GLOB_RECURSE SOURCE_FILES 
    LIST_DIRECTORIES false
    ROOT_PATH 
    **/*.cpp
    **/*.hpp
    **/*.hxx
)

find_program(
    CLANG_FORMAT
    NAMES clang-format
    HINTS "C:/Program Files/LLVM/bin"
)

foreach(SOURCE_FILE in LISTS SOURCE_FILES)
    execute_process(
        COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILE}
    )
endforeach()
