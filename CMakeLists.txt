cmake_minimum_required(VERSION 3.29)
project(speed-typist)
set(CMAKE_FIND_DEBUG_MODE on)

add_executable(speed-typist src/main.cpp)

include(C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(fmt CONFIG REQUIRED)

target_link_libraries(speed-typist PRIVATE fmt::fmt)