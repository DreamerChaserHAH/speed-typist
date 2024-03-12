cmake_minimum_required(VERSION 3.29)
project(speed-typist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/storage)
add_subdirectory(src/gui)
add_executable(speed-typist src/main.cpp)

include_directories(src/storage/include src/gui/include)

target_link_libraries(speed-typist speed-typist-storage-lib speed-typist-gui-lib)