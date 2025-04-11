# # Set minimum required CMake version
# cmake_minimum_required(VERSION 3.10)

# # Define the project
# project(my_alloc)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Enable testing
# enable_testing()

# # Find necessary packages
# find_package(Threads REQUIRED)      # For pthreads
# find_package(GTest REQUIRED)        # For GoogleTest (make sure you have it installed)  
# # Include directories for headers
# include_directories(include)

# # Add the shared library for the allocator
# add_library(myalloc SHARED src/my_alloc.cpp)

# # Add the executable for the main program
# add_executable(main_executable src/main.cpp)

# # Link the main executable with myalloc and pthread
# target_link_libraries(main_executable myalloc Threads::Threads)

# # Add unit tests (assuming you have a unit test file in test/unit_test.cpp)
# add_executable(unit_test test/unit_test.cpp)

# # Link the unit test executable with myalloc, pthread, and GoogleTest
# target_link_libraries(unit_test myalloc Threads::Threads GTest::GTest GTest::Main)

# # Add test to CTest (CMake's built-in testing tool)
# add_test(NAME CUnitTest COMMAND unit_test)

# # Create a custom 'run' command to run the main executable
# add_custom_target(run
#     COMMAND main_executable
#     DEPENDS main_executable
#     COMMENT "Running the main executable"
# )

# # Create a custom 'test' command to run the unit tests
# add_custom_target(test_
#     COMMAND unit_test
#     DEPENDS unit_test
#     COMMENT "Running unit tests"
# )

# # store in the 
# install( TARGETS myalloc
# LIBRARY DESTINATION ${project}/proj/lib)   

# install(DIRECTORY include/ DESTINATION ${project}/proj/inlcude)


cmake_minimum_required(VERSION 3.10)

project(my_alloc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# Add shared library
add_library(myalloc SHARED src/my_alloc.cpp)
target_include_directories(myalloc PUBLIC include)

# Main executable
add_executable(main_executable src/main.cpp)
target_include_directories(main_executable PRIVATE include)
target_link_libraries(main_executable myalloc Threads::Threads)

# Unit test executable
add_executable(unit_test test/unit_test.cpp)
target_include_directories(unit_test PRIVATE include)
target_link_libraries(unit_test myalloc Threads::Threads GTest::GTest GTest::Main)

add_test(NAME CUnitTest COMMAND unit_test)

# Custom targets
add_custom_target(run
    COMMAND main_executable
    DEPENDS main_executable
    COMMENT "Running the main executable")

add_custom_target(run_tests
    COMMAND unit_test
    DEPENDS unit_test
    COMMENT "Running unit tests")

# Install targets
install(TARGETS myalloc
    LIBRARY DESTINATION ${PROJECT_NAME}/proj/lib)

install(DIRECTORY include/ DESTINATION ${PROJECT_NAME}/proj/include)
