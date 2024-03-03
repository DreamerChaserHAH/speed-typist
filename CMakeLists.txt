cmake_minimum_required(VERSION 3.29)
project(speed-typist)

add_executable(speed-typist src/main.cpp)

include_directories(src/application/repository)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
find_package(raylib CONFIG REQUIRED)

target_include_directories(speed-typist PRIVATE ${RAYGUI_INCLUDE_DIRS})
target_link_libraries(speed-typist PRIVATE fmt::fmt raylib unofficial::sqlite3::sqlite3)