#include <stdlib.h>
#include <stdio.h>

void killProgram(const char* message)
{
    // Print the error message and exit the program gracefully
    perror(message);
    exit(EXIT_FAILURE);
}

void ensurePointerNotNull(void* pointer)
{
    if (pointer == NULL)
    {
      killProgram("memory allocation error -- pointer was null");
    }
}