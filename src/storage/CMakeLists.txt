cmake_minimum_required(VERSION 3.29)
project(speed-typist-storage)

include_directories(include)

add_library(speed-typist-storage-lib STATIC src/storage.cpp)
add_executable(speed-typist-storage src/main.cpp)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(unofficial-lmdb CONFIG REQUIRED)

target_link_libraries(speed-typist-storage-lib PRIVATE unofficial::sqlite3::sqlite3 unofficial::lmdb::lmdb)
target_link_libraries(speed-typist-storage PRIVATE speed-typist-storage-lib)
