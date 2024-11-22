#include <stdlib.h>

#include "unity.h"
#include "double_buffer.h"
#include "terminal_utils.h"
#include "mock_terminal_utils.h"
#include "errors.h"

/* Global Variables */
DoubleBuffer* doubleBuffer;


/* Mock functions */
void getTerminalSize_return_good_values(int* width, int* height)
{
    *width = 10;
    *height = 10;
} 

/* SetUp */

void setUp(void)
{
    doubleBuffer = calloc(1, sizeof(DoubleBuffer));
}

/* TearDown */

void tearDown(void)
{
    freeDoubleBuffer(doubleBuffer);
}

/*****************/
/*     Tests     */
/*****************/

void test_initDoubleBuffer_backBuffer_initialized(void)
{
    // Arrange
    getTerminalSize_fake.custom_fake = getTerminalSize_return_good_values;

    // Act
    initDoubleBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_EQUAL(1, getTerminalSize_fake.call_count);
    TEST_ASSERT_NOT_NULL(doubleBuffer->backBuffer);
}

void test_setFrontBufferSize_frontBufferSize_set(void)
{
    // Arrange
    doubleBuffer->width = 2;
    doubleBuffer->height = 2;

    // Act
    setFrontBufferSize(doubleBuffer);

    // Assert
    TEST_ASSERT_EQUAL(6, doubleBuffer->frontBufferSize);
}

void test_allocateBackBuffer_backBuffer_initialized(void)
{
    // Arrange

    // Act
    allocateBackBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_NOT_NULL(doubleBuffer->backBuffer);
}

void test_freeBackBuffer_backBuffer_isnull(void)
{
    // Arrange
    doubleBuffer->backBuffer = malloc(sizeof(char*));

    // Act
    freeBackBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_NULL(doubleBuffer->backBuffer);
}

void test_allocateFrontBuffer_frontBuffer_initialized(void)
{
    // Arrange
    doubleBuffer->frontBufferSize = 2;

    // Act
    allocateFrontBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_NOT_NULL(doubleBuffer->frontBuffer);
}

void test_freeFrontbuffer_frontBuffer_isnull(void)
{
    // Arrange
    doubleBuffer->frontBuffer = malloc(sizeof(char));

    // Act
    freeFrontBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_NULL(doubleBuffer->frontBuffer);
}

void test_freeDoubleBuffer_buffers_arenull(void)
{
    // Arrange
    doubleBuffer->backBuffer = malloc(sizeof(char*));
    doubleBuffer->frontBuffer = malloc(sizeof(char));

    // Act
    freeDoubleBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_NULL(doubleBuffer->backBuffer);
    TEST_ASSERT_NULL(doubleBuffer->frontBuffer);
}

void test_resetBackBuffer_backBufferFirstIndex_isperiod(void)
{
    // Arrange
    doubleBuffer->width = 1;
    doubleBuffer->height = 1;
    doubleBuffer->backBuffer = malloc((doubleBuffer->height + 1) * sizeof(char *));
    doubleBuffer->backBuffer[0] = calloc(doubleBuffer->width, sizeof(char));

    // Act
    resetBackBuffer(doubleBuffer);

    // Assert
    TEST_ASSERT_EQUAL('.', doubleBuffer->backBuffer[0][0]);
}

void test_sendBackBufferToFront_frontBuffer_containsBackBufferContents(void)
{
    // Arrange
    doubleBuffer->width = 1;
    doubleBuffer->height = 1;
    doubleBuffer->backBuffer = malloc((doubleBuffer->height + 1) * sizeof(char *));
    doubleBuffer->backBuffer[0] = calloc(doubleBuffer->width, sizeof(char));
    doubleBuffer->frontBuffer = calloc(2 * sizeof(char), sizeof(char));
    doubleBuffer->backBuffer[0][0] = '.';

    // Act
    sendBackBufferToFront(doubleBuffer);

    // Assert
    TEST_ASSERT_EQUAL('.', doubleBuffer->frontBuffer[0]);
}