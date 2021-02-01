cmake_minimum_required(VERSION 3.7)
project(ZafferDB)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(OpenSSL REQUIRED)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_library(Zaffer ${SOURCES})


add_executable(zafferdb_server "src/server.cpp")
add_executable(zafferdb "src/client.cpp")

target_link_libraries(zafferdb_server OpenSSL::SSL)
target_link_libraries(zafferdb OpenSSL::SSL)
target_link_libraries(zafferdb_server Zaffer)
target_link_libraries(zafferdb Zaffer)

