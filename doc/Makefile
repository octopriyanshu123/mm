# # Compiler
# CXX = g++
# # Compiler flags
# CXXFLAGS = -Wall -Wextra -O2 -std=c++17
# # Output executable
# TARGET = memory
# # Source files
# SRC = myalloc.cpp

# # Default target: Compile the program
# all: $(TARGET)

# $(TARGET): $(SRC)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# # Run the program
# run: $(TARGET)
# 	./$(TARGET)

# # Clean up compiled files
# clean:
# 	rm -f $(TARGET)


# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Google Test flags
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Targets
MAIN_TARGET = memory
TEST_TARGET = test_basic_gtest

# Source files
MAIN_SRC = my_alloc.cpp main.cpp
TEST_SRC = my_alloc.cpp test_basic.cpp

.PHONY: all clean run test

# Build everything
all: $(MAIN_TARGET) $(TEST_TARGET)

# Build the main allocator program
$(MAIN_TARGET): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) $(MAIN_SRC)

# Build the test executable using Google Test
$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(GTEST_LIBS)

# Run the main program
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run the Google Test suite
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean all generated binaries
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET)
