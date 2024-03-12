cmake_minimum_required(VERSION 3.29)
project(speed-typist-gui)

include_directories(include)

add_library(speed-typist-gui-lib STATIC gui.cpp)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(speed-typist-gui-lib PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui)
