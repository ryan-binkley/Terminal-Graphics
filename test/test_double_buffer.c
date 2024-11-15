#include <stdlib.h>

#include "unity.h"
#include "double_buffer.h"
#include "terminal_utils.h"
#include "mock_terminal_utils.h"
#include "errors.h"


void test_initDoubleBuffer_Success(void)
{
    // Arrange
    DoubleBuffer* doubleBuffer = calloc(1, sizeof(DoubleBuffer));

    void modify_return_values_getTerminalSize(int* width, int* height)
    {
        *width = 10;
        *height = 10;
    }
    getTerminalSize_fake.custom_fake = modify_return_values_getTerminalSize;

    // Act
    initDoubleBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_EQUAL(1, getTerminalSize_fake.call_count);

    // Cleanup
    freeDoubleBuffer(doubleBuffer);
}
