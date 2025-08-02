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

    int d01[2]={1,5}; int d10[2]={0,5};
    int d02[2]={2,1}; int d20[2]={0,1};
    int d21[2]={1,2}; int d12[2]={2,2};
    int d23[2]={3,4}; int d32[2]={2,4};
    int d24[2]={4,8}; int d42[2]={2,8};
    int d43[2]={3,2}; int d34[2]={4,2};

    Graph* graph = createGraph(5, sizeof(d01),edgeFinder,weightFinder);

    addEdge(graph, 0, &d01);  addEdge(graph, 1, &d10);  
    addEdge(graph, 0, &d02);  addEdge(graph, 2, &d20);  
    addEdge(graph, 2, &d21);  addEdge(graph, 1, &d12);  
    addEdge(graph, 2, &d23);  addEdge(graph, 3, &d32);  
    addEdge(graph, 2, &d24);  addEdge(graph, 4, &d42);  
    addEdge(graph, 4, &d43);  addEdge(graph, 3, &d34);  

    int* dis=dijkstra(graph,0,compare);
    for(int i=0;i<graph->numNodes;i++) printf("%d ",dis[i]);

    free(dis);
    freeGraph(graph);
    
    return 0;
}
