#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "double_buffer.h"


/* Test Case */
static MunitResult initDoubleBufferSuccess(const MunitParameter params[], void* data)
{
	(void) params;  // Unused parameters
	(void) data;    // Unused user data

	DoubleBuffer* doubleBuffer = calloc(1, sizeof(DoubleBuffer));
    initDoubleBuffer(doubleBuffer);

	assert_ptr(doubleBuffer, !=, NULL);
	assert_ptr(doubleBuffer->backBuffer, !=, NULL);
	assert_ptr(doubleBuffer->frontBuffer, !=, NULL);
	assert_int(doubleBuffer->width, !=, 0);
	assert_int(doubleBuffer->height, !=, 0);
	assert_int(doubleBuffer->frontBufferSize, !=, 0);

	return MUNIT_OK;
}


/* Array of test cases */
static MunitTest double_buffer_test_suite_tests[] = {
    { "/initDoubleBufferSuccess", initDoubleBufferSuccess, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL } // End marker
};


/* Test Suite */
MunitSuite double_buffer_test_suite[] = {
	{ "/Double Buffer Test Suite", double_buffer_test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE },
	{ NULL }
};