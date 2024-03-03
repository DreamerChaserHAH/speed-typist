cmake_minimum_required(VERSION 3.29)
project(speed-typist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/storage)
add_executable(speed-typist src/main.cpp)

include_directories(src/storage/include)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(speed-typist Qt5::Core Qt5::Widgets Qt5::Gui speed-typist-storage-lib)