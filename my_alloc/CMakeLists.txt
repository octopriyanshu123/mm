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


# cmake_minimum_required(VERSION 3.10)

# project(my_alloc)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable_testing()

# find_package(Threads REQUIRED)
# find_package(GTest REQUIRED)

# # Add shared library
# add_library(myalloc SHARED src/my_alloc.cpp)
# target_include_directories(myalloc PUBLIC include)

# # Main executable
# add_executable(main_executable src/main.cpp)
# target_include_directories(main_executable PRIVATE include)
# target_link_libraries(main_executable myalloc Threads::Threads)

# # Unit test executable
# add_executable(unit_test test/unit_test.cpp)
# target_include_directories(unit_test PRIVATE include)
# target_link_libraries(unit_test myalloc Threads::Threads GTest::GTest GTest::Main)

# add_test(NAME CUnitTest COMMAND unit_test)

# # Custom targets
# add_custom_target(run
#     COMMAND main_executable
#     DEPENDS main_executable
#     COMMENT "Running the main executable")

# add_custom_target(run_tests
#     COMMAND unit_test
#     DEPENDS unit_test
#     COMMENT "Running unit tests")

# # Install targets
# install(TARGETS myalloc
#     LIBRARY DESTINATION ${PROJECT_NAME}/proj/lib)

# install(DIRECTORY include/ DESTINATION ${PROJECT_NAME}/proj/include)



# cmake_minimum_required(VERSION 3.10)
# project(my_alloc VERSION 1.0 LANGUAGES CXX)

# # Set C++ version
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Enable testing framework
# enable_testing()

# # Find required packages
# find_package(Threads REQUIRED)
# find_package(GTest REQUIRED)

# # Include directories
# include_directories(include)

# # === Build the shared library ===
# add_library(myalloc SHARED src/my_alloc.cpp)
# target_include_directories(myalloc PUBLIC 
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )
# set_target_properties(myalloc PROPERTIES
#     VERSION ${PROJECT_VERSION}
#     SOVERSION 1
#     EXPORT_NAME myalloc
# )

# # === Main executable for examples/demo ===
# add_executable(main_executable src/main.cpp)
# target_link_libraries(main_executable PRIVATE myalloc Threads::Threads)

# # === Unit tests using Google Test ===
# add_executable(unit_test test/unit_test.cpp)
# target_link_libraries(unit_test PRIVATE myalloc Threads::Threads GTest::GTest GTest::Main)
# add_test(NAME UnitTests COMMAND unit_test)

# # === Installation ===
# include(GNUInstallDirs)

# install(TARGETS myalloc
#     EXPORT myallocTargets
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# install(DIRECTORY include/
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myalloc
#     FILES_MATCHING PATTERN "*.hpp"
# )

# # Create and install package config files
# include(CMakePackageConfigHelpers)
# configure_package_config_file(
#     cmake/myallocConfig.cmake.in
#     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
#     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myalloc
# )

# write_basic_package_version_file(
#     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
#     VERSION ${PROJECT_VERSION}
#     COMPATIBILITY SameMajorVersion
# )

# install(EXPORT myallocTargets
#     FILE myallocTargets.cmake
#     NAMESPACE myalloc::
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myalloc
# )

# install(FILES
#     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
#     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myalloc
# )

# # Keep your custom installation paths
# # install(TARGETS myalloc
# #     EXPORT myallocTargets  # Required for find_package
# #     LIBRARY DESTINATION lib/${PROJECT_NAME}/lib
# #     ARCHIVE DESTINATION lib/${PROJECT_NAME}/lib
# #     RUNTIME DESTINATION bin/${PROJECT_NAME}
# #     INCLUDES DESTINATION include/${PROJECT_NAME}/include
# # )

# # install(DIRECTORY include/
# #     DESTINATION include/${PROJECT_NAME}/include
# #     FILES_MATCHING PATTERN "*.hpp"
# # )

# # # Package configuration (unchanged)
# # include(CMakePackageConfigHelpers)
# # configure_package_config_file(
# #     cmake/myallocConfig.cmake.in
# #     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
# #     INSTALL_DESTINATION lib/${PROJECT_NAME}/cmake
# # )

# # write_basic_package_version_file(
# #     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
# #     VERSION ${PROJECT_VERSION}
# #     COMPATIBILITY SameMajorVersion
# # )

# # install(EXPORT myallocTargets
# #     FILE myallocTargets.cmake
# #     NAMESPACE myalloc::
# #     DESTINATION lib/${PROJECT_NAME}/cmake
# # )

# # install(FILES
# #     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
# #     ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
# #     DESTINATION lib/${PROJECT_NAME}/cmake
# # )


# # === Custom build targets ===
# add_custom_target(run
#     COMMAND main_executable
#     DEPENDS main_executable
#     COMMENT "Running the main executable")

# add_custom_target(run_tests
#     COMMAND unit_test
#     DEPENDS unit_test
#     COMMENT "Running unit tests")

# install(TARGETS myalloc
#     LIBRARY DESTINATION lib/${PROJECT_NAME}/lib)

# install(DIRECTORY include/
#     DESTINATION include/${PROJECT_NAME}/include
#     FILES_MATCHING PATTERN "*.hpp")    



#-=------------------------------------------------ copy the libmyalloc.so to the /usr/local/lib but not assess by find_package 

# cmake_minimum_required(VERSION 3.10)
# project(my_alloc VERSION 1.0 LANGUAGES CXX)

# # Set C++ version
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Enable testing framework
# enable_testing()

# # Find required packages
# find_package(Threads REQUIRED)
# find_package(GTest REQUIRED)

# # Include directories
# include_directories(include)

# # === Build the shared library ===
# add_library(myalloc SHARED src/my_alloc.cpp)
# target_include_directories(myalloc PUBLIC include)

# # === Unit tests using Google Test ===
# add_executable(unit_test test/unit_test.cpp)
# target_link_libraries(unit_test PRIVATE myalloc Threads::Threads GTest::GTest GTest::Main)
# add_test(NAME UnitTests COMMAND unit_test)

# # === Custom build targets ===
# add_custom_target(run
#     COMMAND main_executable
#     DEPENDS main_executable
#     COMMENT "Running the main executable")

# add_custom_target(run_tests
#     COMMAND unit_test
#     DEPENDS unit_test
#     COMMENT "Running unit tests")


# install(TARGETS myalloc
#     LIBRARY DESTINATION lib/${PROJECT_NAME}/lib)

# install(DIRECTORY include/
#     DESTINATION include/${PROJECT_NAME}/include
#     FILES_MATCHING PATTERN "*.hpp")

#------------------------------------------------- copy the libmyalloc.so to the /usr/local/lib and access by find_package 

cmake_minimum_required(VERSION 3.10)
project(my_alloc VERSION 1.0 LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing framework
enable_testing()

# Find required packages
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# Include directories
include_directories(include)

# === Build the shared library ===
add_library(myalloc SHARED src/my_alloc.cpp)
target_include_directories(myalloc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)
set_target_properties(myalloc PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/my_alloc.hpp"
)

# === Unit tests using Google Test ===
add_executable(unit_test test/unit_test.cpp)
target_link_libraries(unit_test PRIVATE myalloc Threads::Threads GTest::GTest GTest::Main)
add_test(NAME UnitTests COMMAND unit_test)

# === Installation ===
install(TARGETS myalloc
    EXPORT myallocTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

install(EXPORT myallocTargets
    FILE myallocTargets.cmake
    NAMESPACE myalloc::
    DESTINATION lib/cmake/myalloc
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/myallocConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
    INSTALL_DESTINATION lib/cmake/myalloc
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/myallocConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/myallocConfigVersion.cmake
    DESTINATION lib/cmake/myalloc
)

# === Custom build targets ===
add_custom_target(run_tests
    COMMAND unit_test
    DEPENDS unit_test
    COMMENT "Running unit tests"
)