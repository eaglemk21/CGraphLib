#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algorithms.h"
#include "disjointSetUnion.h"

int edgeFinder(const void* node){
    return *(int*)((char*)node);  
}

int weightFinder(const void* node){
    return *(int*)((char*)node + sizeof(int));  
}

int main() {
    // Example visual Representation
    // https://static.javatpoint.com/tutorial/daa/images/bellman-ford-algorithm3.png
    
    int d01[2]={1,6};
    int d02[2]={2,4};
    int d03[2]={3,5};
    int d14[2]={4,-1};
    int d21[2]={1,-2};
    int d32[2]={2,-2};
    int d24[2]={4,3};
    int d35[2]={5,-1};
    int d45[2]={5,3};
    Graph* graph = createGraph(6,sizeof(d01),edgeFinder,weightFinder);

    addEdge(graph,0,d01);
    addEdge(graph,0,d02);
    addEdge(graph,0,d03);
    addEdge(graph,1,d14);
    addEdge(graph,2,d21);
    addEdge(graph,3,d32);
    addEdge(graph,2,d24);
    addEdge(graph,3,d35);
    addEdge(graph,4,d45);

    int* distance = bellmanFord(graph,0);
    if(distance==NULL) printf("Graph contains Negative Cycle\n");
    else for(int i=0;i<graph->numNodes;i++) printf("%d ",distance[i]);
    free(distance);
    freeGraph(graph);
}
