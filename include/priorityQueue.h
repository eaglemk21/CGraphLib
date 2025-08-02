#pragma once
#include <stdio.h>
typedef struct priorityQueue {
    void* data;        
    size_t dataSize;   
    int capacity;      
    int size;          
    int (*compare)(const void*, const void*); 
} priorityQueue;

priorityQueue* createPriorityQueue(size_t dataSize, int (*compare)(const void*, const void*));
void pushPriorityQueue(priorityQueue* pq, void* value);
void* topPriorityQueue(priorityQueue* pq);
void popPriorityQueue(priorityQueue* pq);
void freePriorityQueue(priorityQueue* pq);