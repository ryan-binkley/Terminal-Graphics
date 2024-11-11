# Compiler
CC = gcc
CFLAGS = -g3 -O0 -I$(INCLUDE_DIR) -fprofile-arcs -ftest-coverage
TEST_CFLAGS = -I$(TEST_INCLUDE_DIR) -I$(INCLUDE_DIR) -fprofile-arcs -ftest-coverage

###########################
#                         #
#      Main Codebase      #
#                         #
###########################

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include


# Source files, object files, and executable
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TARGET = $(BUILD_DIR)/main


# Default rule
all: clean setup main $(TARGET)


# Build target binary from object files
main: $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET) -lgcov


# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | setup
	$(CC) $(CFLAGS) -c $< -o $@


# Ensure build directory exists
setup:
	mkdir -p $(BUILD_DIR)


# Cleanup
clean: test_clean
	rm -rf $(BUILD_DIR) *.gcda *.gcno *.gcov


# Run the program
run: all
	$(TARGET)


###########################
#                         #
#          Tests          #
#                         #
###########################


# Directories
TEST_SRC_DIR = tests/tests
TEST_BUILD_DIR = tests/build
TEST_INCLUDE_DIR = tests/include


# Source files, object files, and executable
TEST_SRC_FILES = $(wildcard $(TEST_SRC_DIR)/*.c)
SRC_OBJ_FILES = $(filter-out build/main.o, $(wildcard $(BUILD_DIR)/*.o))
TEST_OBJ_FILES = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRC_FILES))
TEST_TARGET = $(TEST_BUILD_DIR)/test_main


# Default test rule
test_all: test_clean test_setup test_main $(TEST_TARGET)


# Build target binary from object files
test_main: $(TEST_OBJ_FILES) | $(TEST_BUILD_DIR)
	$(CC) $(TEST_CFLAGS) $(TEST_OBJ_FILES) $(SRC_OBJ_FILES) -o $(TEST_TARGET) -lgcov


# Compile each source file into an object file
$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.c | test_setup
	$(CC) $(TEST_CFLAGS) -c $< -o $@


# Ensure build directory exists
test_setup:
	mkdir -p $(TEST_BUILD_DIR)


# Cleanup
test_clean:
	rm -rf $(TEST_BUILD_DIR) *.gcda *.gcno *.gcov


# Run the tests
test: all test_all
	$(TEST_TARGET)
	@$(MAKE) generate_coverage


generate_coverage:
	@echo "#################################  Generating Coverage Report...  #################################"
	@gcov -o $(BUILD_DIR) $(SRC_FILES) > /dev/null 2>&1
	@$(MAKE) test_clean
	@gcovr -r . --print-summary


# Additional convenience commands
.PHONY: all clean run setup main generate_coverage test_clean