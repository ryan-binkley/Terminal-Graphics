#include <stdlib.h>
#include "terminal_utils.h"
#include "double_buffer.h"
#include "errors.h"


void initDoubleBuffer(DoubleBuffer* doubleBuffer)
{
    getTerminalSize(&doubleBuffer->width, &doubleBuffer->height);
    setFrontBufferSize(doubleBuffer);
    allocateBackBuffer(doubleBuffer);
    allocateFrontBuffer(doubleBuffer);
    resetBackBuffer(doubleBuffer);
}


void setFrontBufferSize(DoubleBuffer* doubleBuffer)
{
    doubleBuffer->frontBufferSize = doubleBuffer->width * doubleBuffer->height + doubleBuffer->height;
}

void allocateBackBuffer(DoubleBuffer* doubleBuffer)
{
    doubleBuffer->backBuffer = malloc((doubleBuffer->height + 1) * sizeof(char *));
    for (int i = 0; i < doubleBuffer->height; i++) {
        doubleBuffer->backBuffer[i] = calloc(doubleBuffer->width, sizeof(char));
        ensurePointerNotNull(doubleBuffer->backBuffer[i]);
    }
    ensurePointerNotNull(doubleBuffer->backBuffer);
}

void freeBackBuffer(DoubleBuffer* doubleBuffer)
{
    if (doubleBuffer->backBuffer != NULL) {
        for (int i = 0; i < doubleBuffer->height; i++) {
            if (doubleBuffer->backBuffer[i] != NULL) {
                free(doubleBuffer->backBuffer[i]);
                doubleBuffer->backBuffer[i] = NULL; // Avoid dangling pointers
            }
        }
        free(doubleBuffer->backBuffer);
        doubleBuffer->backBuffer = NULL; // Avoid dangling pointer for `backBuffer`
    }
}


void allocateFrontBuffer(DoubleBuffer* doubleBuffer)
{
    doubleBuffer->frontBuffer = calloc(doubleBuffer->frontBufferSize * sizeof(char), sizeof(char));
    ensurePointerNotNull(doubleBuffer->frontBuffer);
}

void freeFrontBuffer(DoubleBuffer* doubleBuffer)
{
    free(doubleBuffer->frontBuffer);
    doubleBuffer->frontBuffer = NULL;
}

void freeDoubleBuffer(DoubleBuffer* doubleBuffer)
{
    freeFrontBuffer(doubleBuffer);
    freeBackBuffer(doubleBuffer);
}

void resetBackBuffer(DoubleBuffer* doubleBuffer)
{
    for (int i = 0 ; i < doubleBuffer->height ; i++)
    {
        for (int j = 0 ; j < doubleBuffer->width ; j++)
        {
            doubleBuffer->backBuffer[i][j] = '.';
        }
    }
}

void sendBackBufferToFront(DoubleBuffer* doubleBuffer)
{
    int index = 0;

    for (int i = 0; i < doubleBuffer->height; i++) {
        // Write the content of the backBuffer to frontBuffer directly
        for (int j = 0; j < doubleBuffer->width; j++) {
            doubleBuffer->frontBuffer[index] = doubleBuffer->backBuffer[i][j];
            index++;
        }
    }

    // Null-terminate the frontBuffer string
    doubleBuffer->frontBuffer[index] = '\0';
}