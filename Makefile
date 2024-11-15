MAKEFLAGS += --no-print-directory


# Compiler
CC = gcc
CFLAGS = -g3 -O0 -I$(INCLUDE_DIR) -fprofile-arcs -ftest-coverage

###########################
#                         #
#      Main Codebase      #
#                         #
###########################

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIB_DIR = lib


# Source files, object files, and executable
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
LIB_FILES = $(wildcard $(LIB_DIR)/*.o)
TARGET = $(BUILD_DIR)/main


# Default rule
all: clean setup main $(TARGET)


# Build target binary from object files
main: $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(TARGET) -lgcov


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

# Cleanup
test_clean:
	rm -rf $(TEST_BUILD_DIR) *.gcda *.gcno *.gcov


# Run the tests
test: all
	@echo "#####################################################################################################################################################################################"
	@echo "##################################################################################  Running Tests  ##################################################################################"
	@echo "#####################################################################################################################################################################################"
	@ceedling test:all gcov:all utils:gcov
	@$(MAKE) test_clean
	@$(MAKE) clean


#################################
# Additional convenience commands
.PHONY: all clean run setup main test_clean
.SILENT: all clean run setup test_clean
