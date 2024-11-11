#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "double_buffer.h"

/* Global Mocks */
void __wrap_getTerminalSize(int* width, int* height)
{
    // Mock return values
    *width = 80;
    *height = 24;
}


/* Test Cases */
static MunitResult initDoubleBuffer_Success(const MunitParameter params[], void* data)
{
	(void) params;  // Unused parameters
	(void) data;    // Unused user data

	// Arrange
	DoubleBuffer* doubleBuffer = calloc(1, sizeof(DoubleBuffer));
    
	// Act
    __wrap_getTerminalSize(&doubleBuffer->width, &doubleBuffer->height);
    setFrontBufferSize(doubleBuffer);
    allocateBackBuffer(doubleBuffer);
    allocateFrontBuffer(doubleBuffer);
    resetBackBuffer(doubleBuffer);

    // Assert
	assert_ptr(doubleBuffer, !=, NULL);
	assert_ptr(doubleBuffer->backBuffer, !=, NULL);
	assert_ptr(doubleBuffer->frontBuffer, !=, NULL);
	assert_int(doubleBuffer->width, ==, 80);
	assert_int(doubleBuffer->height, ==, 24);
	assert_int(doubleBuffer->frontBufferSize, ==, 1944);

	return MUNIT_OK;
}

static MunitResult initDoubleBuffer_FailOnGetTerminalSize(const MunitParameter params[], void* data)
{
	(void) params;  // Unused parameters
	(void) data;    // Unused user data

	// Arrange
	DoubleBuffer* doubleBuffer = calloc(1, sizeof(DoubleBuffer));

	void __wrap_getTerminalSize(int* width, int* height)
	{
	    // Mock return values
	    *width = 0;
	    *height = 0;
	}
    
	// Act
    __wrap_getTerminalSize(&doubleBuffer->width, &doubleBuffer->height);

    // Assert
	assert_int(doubleBuffer->width, ==, 0);
	assert_int(doubleBuffer->height, ==, 0);

	return MUNIT_OK;
}


/* Array of test cases */
static MunitTest double_buffer_test_suite_tests[] = {
    { "/initDoubleBuffer_Success", initDoubleBuffer_Success, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/initDoubleBuffer_FailOnGetTerminalSize", initDoubleBuffer_FailOnGetTerminalSize, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL } // End marker
};


/* Test Suite */
MunitSuite double_buffer_test_suite[] = {
	{ "/Double Buffer Test Suite", double_buffer_test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE },
	{ NULL }
};