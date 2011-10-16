cmake_minimum_required (VERSION 2.6)
project (ChessEngine)

add_definitions("-DLINUX")

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include")


add_executable(chess main.c)
target_link_libraries(chess ChessLib)
