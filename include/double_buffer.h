//screen_buffer_utils.h
#ifndef DOUBLE_BUFFER_H
#define DOUBLE_BUFFER_H

typedef struct {
	char** backBuffer;
	char* frontBuffer;
	int width;
	int height;
	int frontBufferSize;
} DoubleBuffer;

void initDoubleBuffer(DoubleBuffer* doubleBuffer);

void setFrontBufferSize(DoubleBuffer* doubleBuffer);
void allocateBackBuffer(DoubleBuffer* doubleBuffer);
void freeBackBuffer(DoubleBuffer* doubleBuffer);
void allocateFrontBuffer(DoubleBuffer* doubleBuffer);
void freeFrontBuffer(DoubleBuffer* doubleBuffer);

void freeDoubleBuffer(DoubleBuffer* doubleBuffer);
void resetBackBuffer(DoubleBuffer* doubleBuffer);
void sendBackBufferToFront(DoubleBuffer* doubleBuffer);

#endif