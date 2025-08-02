#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algorithms.h"

int edgeFinder(const void* node){
    return *(int*)((char*)node);  
}
int weightFinder(const void* node){
    return *(int*)((char*)node + sizeof(int));  
}
int compare(const void* node1,const void* node2){
    int w1=weightFinder(node1);
    int w2=weightFinder(node2);
    return w1>w2;
}

int main() {
    // example test case visual https://static.javatpoint.com/ds/images/prims-algorithm.png
    // Sample test Case's output -> ans=10
    
    int d13[2]={3,3}; int d31[2]={1,3};
    int d32[2]={2,10}; int d23[2]={3,10};
    int d34[2]={4,2}; int d43[2]={3,2};
    int d35[2]={5,6}; int d53[2]={3,6};
    int d24[2]={4,4}; int d42[2]={2,4};
    int d45[2]={5,1}; int d54[2]={4,1};
    Graph* graph = createGraph(6, sizeof(d13),edgeFinder,weightFinder);

    addEdge(graph, 1, &d13); addEdge(graph, 3, &d31); 
    addEdge(graph, 3, &d32); addEdge(graph, 2, &d23); 
    addEdge(graph, 3, &d34); addEdge(graph, 4, &d43); 
    addEdge(graph, 3, &d35); addEdge(graph, 5, &d53); 
    addEdge(graph, 2, &d24); addEdge(graph, 4, &d42); 
    addEdge(graph, 4, &d45); addEdge(graph, 5, &d54); 
    
    for(int i=0;i<graph->numNodes;i++){
        Node* temp=graph->adjacencyList[i];
        printf("%d ",i);
        while(temp){
            printf("-> %d ",edgeFinder(temp->data));
            temp=temp->next;
        }
        printf("\n");
    }

    printf("Prims Algorithm %d",prims(graph,compare));
    freeGraph(graph);
    
    return 0;
}
