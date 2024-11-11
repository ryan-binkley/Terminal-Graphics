#include "munit.h"


/* Declarations for test suites */
extern MunitSuite double_buffer_test_suite[];



/* Master Test Suite List */
static const MunitSuite test_suite[] = {
	{ "", NULL, double_buffer_test_suite, 1, MUNIT_SUITE_OPTION_NONE },
	{ NULL }
};





/* Main function to run the test suite */
int main(int argc, char* argv[]) 
{
    return munit_suite_main(test_suite, NULL, argc, argv);
}