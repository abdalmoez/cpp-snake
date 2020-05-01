cmake_minimum_required(VERSION 3.0)
project(cpp_snake)

include_directories(inc)


file(GLOB SNAKE_SRC_FILES
    src/util/*.cpp
    src/menu/*.cpp
    src/*.cpp
)

add_executable(cpp_snake ${SNAKE_SRC_FILES})
target_link_libraries(cpp_snake -lsfml-graphics -lsfml-window -lsfml-system -g -ggdb)
add_custom_command(TARGET cpp_snake PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/PKG/ $<TARGET_FILE_DIR:cpp_snake>)
