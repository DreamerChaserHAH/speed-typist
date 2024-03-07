cmake_minimum_required(VERSION 3.29)
project(speed-typist)
set(CMAKE_FIND_DEBUG_MODE on)

add_executable(speed-typist src/main.cpp)

include(C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_include_directories(speed-typist PRIVATE ${RAYGUI_INCLUDE_DIRS})
target_link_libraries(speed-typist PRIVATE fmt::fmt raylib unofficial::sqlite3::sqlite3)