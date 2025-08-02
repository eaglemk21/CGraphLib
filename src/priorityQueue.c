#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<priorityQueue.h>

priorityQueue* createPriorityQueue(size_t dataSize, int (*compare)(const void*, const void*)) {
    priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq->capacity = 2; 
    pq->dataSize = dataSize;
    pq->size = 0;
    pq->data = malloc(pq->capacity * dataSize);
    pq->compare = compare;
    return pq;
}

void swap(void* a, void* b, size_t dataSize) {
    void* temp = malloc(dataSize);
    memcpy(temp, a, dataSize);
    memcpy(a, b, dataSize);
    memcpy(b, temp, dataSize);
    free(temp);
}

int parent(int i) {
    return (i - 1) / 2;
}

void resizePriorityQueue(priorityQueue* pq) {
    pq->capacity *= 2;
    pq->data = realloc(pq->data, pq->capacity * pq->dataSize);
}

void pushPriorityQueue(priorityQueue* pq, void* value) {
    if (pq->size == pq->capacity) {
        resizePriorityQueue(pq);  
    }

    memcpy((char*)pq->data + pq->size * pq->dataSize, value, pq->dataSize);
    pq->size++;

    int i = pq->size - 1;
    while (i != 0 && pq->compare((char*)pq->data + parent(i) * pq->dataSize, (char*)pq->data + i * pq->dataSize)) {
        swap((char*)pq->data + i * pq->dataSize, (char*)pq->data + parent(i) * pq->dataSize, pq->dataSize);
        i = parent(i);
    }
}

void* topPriorityQueue(priorityQueue* pq){
    if(pq->size==0) {
        fprintf(stderr,"Empty Priority Queue");
        return NULL;
    }
    return pq->data; 
}

void heapifyRecursive(priorityQueue* pq,int ind){
    int maxiInd=ind;
    int leftChild=ind*2+1;
    int rightChild=ind*2+2;
    if(leftChild<pq->size&&pq->compare((char*)pq->data+maxiInd*pq->dataSize,(char*)pq->data+leftChild*pq->dataSize)) {
        maxiInd=leftChild;
    }
    if(rightChild<pq->size&&pq->compare((char*)pq->data+maxiInd*pq->dataSize,(char*)pq->data+rightChild*pq->dataSize)) {
        maxiInd=rightChild;
    }
    if(maxiInd==ind) return;
    swap((char*)pq->data+ind*pq->dataSize,(char*)pq->data+maxiInd*pq->dataSize,pq->dataSize); 
    heapifyRecursive(pq,maxiInd);   
}
void popPriorityQueue(priorityQueue* pq){
    if(pq->size==0) {
        fprintf(stderr,"Queue Underflow");
        return;
    }
    memcpy((char*)pq->data,(char*)pq->data+(pq->size-1) * pq->dataSize,pq->dataSize);
    pq->size--;
    heapifyRecursive(pq,0);
}

void freePriorityQueue(priorityQueue* pq){
    free(pq->data);
    free(pq);
}