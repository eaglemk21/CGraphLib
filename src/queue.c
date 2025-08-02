#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    queue->size = 0;
    queue->head = queue->tail = NULL;
    return queue;
}

void pushQueue(Queue* queue, void* data, size_t dataSize) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newQueueNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newQueueNode->data = malloc(dataSize);
    if (!newQueueNode->data) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newQueueNode);
        return;
    }
    memcpy(newQueueNode->data, data, dataSize);
    newQueueNode->next = NULL;

    if (queue->tail == NULL) {
        queue->head = queue->tail = newQueueNode;
    } else {
        queue->tail->next = newQueueNode;
        queue->tail = newQueueNode;
    }
    queue->size++;
}

void* topQueue(Queue* queue) {
    if (queue->head == NULL) {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    return queue->head->data;
}

void popQueue(Queue* queue) {
    if (queue->head == NULL) {
        fprintf(stderr, "Queue is empty\n");
        return;
    }

    QueueNode* temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(temp->data);  
    free(temp);        
    queue->size--;
}

int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

void freeQueue(Queue* queue) {
    while (!isQueueEmpty(queue)) {
        popQueue(queue);
    }
    free(queue);
}
