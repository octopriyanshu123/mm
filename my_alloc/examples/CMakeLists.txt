cmake_minimum_required(VERSION 3.10)
project(myalloc_consumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(myalloc REQUIRED)
include_directories(include)

add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE myalloc)