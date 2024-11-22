#include <stdlib.h>
#include <stdio.h>
#include "double_buffer.h"

int main() 
{
    DoubleBuffer* doubleBuffer = calloc(1, sizeof(DoubleBuffer));
    initDoubleBuffer(doubleBuffer);

    sendBackBufferToFront(doubleBuffer);

    printf("%s", doubleBuffer->frontBuffer);

    freeDoubleBuffer(doubleBuffer);

    return 0; 
}