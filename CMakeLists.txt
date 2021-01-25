cmake_minimum_required(VERSION 3.7)
project(ZefferDB)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(OpenSSL REQUIRED)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(ZefferDb src/main.cpp)

target_link_libraries(ZefferDb OpenSSL::SSL)

