cmake_minimum_required(VERSION 3.30)
project(Terminal_Graphics C)

set(CMAKE_C_STANDARD 23)

# Enable test coverage flags if needed
option(ENABLE_COVERAGE "Enable coverage flags" ON)

# Directories
set(SRC_DIR src)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set(INCLUDE_DIR include)
set(LIB_DIR lib)

# Include directories
include_directories(${INCLUDE_DIR})

# Source files and object files
file(GLOB SRC_FILES "${SRC_DIR}/*.c")
file(GLOB LIB_FILES "${LIB_DIR}/*.o")

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Executable target
add_executable(Terminal_Graphics ${SRC_FILES})

# Link external object files
target_link_libraries(Terminal_Graphics PRIVATE ${LIB_FILES} gcov)

# Add coverage flags if enabled
if(ENABLE_COVERAGE)
    target_compile_options(Terminal_Graphics PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(Terminal_Graphics PRIVATE -fprofile-arcs -ftest-coverage)
endif()

# Add a custom target for running the program
add_custom_target(run
        COMMAND Terminal_Graphics
        DEPENDS Terminal_Graphics
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running the program"
)

# Custom clean command to mimic test_clean and clean rules
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove *.gcda *.gcno *.gcov
        COMMENT "Cleaning build artifacts and coverage data"
)

# Custom test target
add_custom_target(test
        COMMAND cd ../ && ceedling test:all gcov:all utils:gcov
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean-all
        COMMENT "Running tests and cleaning up"
)

# Create the build directory
set_property(GLOBAL PROPERTY USE_FOLDERS ON)