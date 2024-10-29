cmake_minimum_required(VERSION 3.10)

project(yahtzee)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS OFF)

find_package(Curses REQUIRED)

if (Curses_FOUND)
    message(STATUS "Found ncurses")
else()
    message((WARNING "ncurses not found"))
endif()

file(GLOB SOURCES "src/*.c")

file(GLOB HEADERS "include/*.h")

# 実行可能ファイルを追加
add_executable(yahtzee ${SOURCES} ${HEADERS})

add_definitions(-DDATA_PATH="${CMAKE_SOURCE_DIR}/data/")

# ncursesライブラリをリンク
target_link_libraries(yahtzee PRIVATE ${Curses_LIBRARIES})

target_compile_options(yahtzee PRIVATE -Wall -Wextra -g3 -O2)

# インクルードディレクトリを指定
target_include_directories(yahtzee PRIVATE ${Curses_INCLUDE_DIRS} include)

target_link_libraries(yahtzee PRIVATE ${Curses_LIBRARIES} ncursesw)

add_compile_definitions(_POSIX_C_SOURCE=200809L)