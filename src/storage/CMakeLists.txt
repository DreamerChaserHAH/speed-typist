cmake_minimum_required(VERSION 3.29)
project(speed-typist-storage)

include_directories(src/include)

add_library(speed-typist-storage-lib src/storage.cpp)
add_executable(speed-typist-storage src/main.cpp)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

target_link_libraries(speed-typist-storage-lib PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(speed-typist-storage PRIVATE speed-typist-storage-lib)
