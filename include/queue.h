#pragma once
#include <stddef.h>
typedef struct QueueNode {
    void* data;          
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    int size;
    QueueNode* head;
    QueueNode* tail;
} Queue;

// Function declarations
Queue* createQueue();
void pushQueue(Queue* queue, void* data, size_t dataSize);
void* topQueue(Queue* queue);
void popQueue(Queue* queue);
int isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);