cmake_minimum_required(VERSION 3.10)
project(myalloc_consumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find the installed myalloc package
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../myalloc/install")

find_package(myalloc REQUIRED)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE myalloc::myalloc)

# Verify the include paths are correct
get_target_property(MYALLOC_INCLUDES myalloc::myalloc INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "myalloc include directories: ${MYALLOC_INCLUDES}")

# Verify the library is found
get_target_property(MYALLOC_LOCATION myalloc::myalloc LOCATION)
message(STATUS "myalloc library location: ${MYALLOC_LOCATION}")