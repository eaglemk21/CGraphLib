#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "queue.h"
#include "graph.h"
#include "priorityQueue.h"

void DFS_recursive(Graph* graph,int startNode,int *visit){
    printf("%d ",startNode);
    visit[startNode]=1;

    Node* temp=graph->adjacencyList[startNode];
    while(temp){
        int edge=graph->edgeFinder(temp->data);
        if(visit[edge]==0){
            DFS_recursive(graph,edge,visit);
        }
        temp=temp->next;
    }
}
void DFS(Graph* graph,int startNode){
    int n=graph->numNodes;
    int* visit = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=0;
    DFS_recursive(graph,startNode,visit);
    printf("\n");
    free(visit);
}

void BFS(Graph* graph,int startNode){
    int n=graph->numNodes;
    int* visit = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=0;
    Queue* q = createQueue();
    pushQueue(q,&startNode,sizeof(startNode));
    while(isQueueEmpty(q)==0){
        int node=*(int*)topQueue(q);
        popQueue(q);
        printf("%d ",node);
        Node* tmp = graph->adjacencyList[node];
        visit[startNode]=1;
        while (tmp){
            int edge = graph->edgeFinder(tmp->data);
            if(visit[edge]==0){
                visit[edge]=1;
                pushQueue(q,&edge,sizeof(edge));
            }
            tmp=tmp->next;
        }
    }
    printf("\n");
    free(visit);
}

int undirectedCyclicityRecursive(Graph* graph,int* visit,int node,int par){
    visit[node] = 1;
    Node* tmp = graph->adjacencyList[node];
    while(tmp){
        int edge = graph->edgeFinder(tmp->data);
        if(visit[edge]==0) {
            if(undirectedCyclicityRecursive(graph,visit,edge,node)) return 1;   
        }
        else if(par!=edge) return 1;
        tmp = tmp->next;
    }
    return 0;
}
int undirectedCyclicity(Graph* graph){
    int n=graph->numNodes;
    int* visit = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=0;
    for(int i=0;i<n;i++){
        if(visit[i]==1) continue;
        if(undirectedCyclicityRecursive(graph,visit,i,-1)) return 1;
    }
    free(visit);
    return 0;
}

int directedCyclicityRecursive(Graph* graph,int* visit,int *path,int node){
    visit[node]=1;
    path[node]=1;
    Node* tmp = graph->adjacencyList[node];
    while(tmp){
        int edge = graph->edgeFinder(tmp->data);
        if(visit[edge]==0){
            if(directedCyclicityRecursive(graph,visit,path,edge)) return 1;
        }
        else if(path[edge]==1) return 1;
        tmp = tmp->next;
    }
    path[node]=0;
    return 0;
}
int directedCyclicity(Graph* graph){
    int n=graph->numNodes;
    int* visit = malloc(n*sizeof(int));
    int* path = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=path[i]=0;
    for(int i=0;i<n;i++){
        if(visit[i]==1) continue;
        path[i]=1;
        if(directedCyclicityRecursive(graph,visit,path,i)) return 1;
        path[i]=0;
    }
    free(path);
    free(visit);
    return 0;
} 

int* topologicalSort(Graph* graph){
    int n = graph->numNodes;
    int* indegree = malloc(n * sizeof(int));
    int* array = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) indegree[i] = array[i] = 0;
    for(int i=0;i<n;i++){
        Node* tmp = graph->adjacencyList[i];
        while(tmp){
            int edge = graph->edgeFinder(tmp->data);
            indegree[edge]++;
            tmp = tmp->next;
        }
    }
    Queue* q = createQueue();
    for(int i=0;i<n;i++){
        if(indegree[i]==0) pushQueue(q,&i,sizeof(i));
    }
    int k=0;
    while(isQueueEmpty(q)==0){
        int node = graph->edgeFinder(topQueue(q));
        popQueue(q);
        array[k++]=node;
        Node* tmp = graph->adjacencyList[node];
        while(tmp){
            int edge = graph->edgeFinder(tmp->data);
            indegree[edge]--;
            if(indegree[edge]==0) pushQueue(q,&edge,sizeof(edge));
            tmp = tmp->next;
        }
    }
    free(indegree);
    if(k!=n) {
        free(array);
        return NULL;   // Graph contains a cycle
    }
    return array;
}


int* dijkstra(Graph* graph, int startNode,int (*cmp) (const void*, const void*)){
    int n=graph->numNodes;
    int* dis = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) dis[i]=INT_MAX;
    dis[startNode]=0;
    size_t sz=graph->dataSize;
    priorityQueue* pq = createPriorityQueue(sz,cmp);
    do{
        int node=startNode;
        if(pq->size){
            node=graph->edgeFinder(topPriorityQueue(pq));
            popPriorityQueue(pq);
        }
        Node* tmp = graph->adjacencyList[node];
        while(tmp){
            int edge=graph->edgeFinder(tmp->data);
            int wt=graph->weightFinder(tmp->data);
            if(wt+dis[node]<dis[edge]){
                dis[edge]=wt+dis[node];
                pushPriorityQueue(pq,tmp->data);
            }   
            tmp=tmp->next;
        }
    }while(pq->size!=0);
    freePriorityQueue(pq);
    return dis;
}

int** floydWarshal(Graph* graph){
    int n=graph->numNodes;
    int** matrix=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        matrix[i]=malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) matrix[i][j]=1e9;
    }
    for(int i=0;i<n;i++){
        matrix[i][i]=0;
        Node* tmp = graph->adjacencyList[i];
        while(tmp){
            int edge = graph->edgeFinder(tmp->data);
            int wt = graph->weightFinder(tmp->data);
            matrix[i][edge]=wt;
            matrix[edge][i]=wt;
            tmp=tmp->next;
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]>matrix[i][k]+matrix[k][j]) matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
    return matrix;
}

int prims(Graph* graph,int (*cmp)(const void *, const void *)){
    int n=graph->numNodes;
    int* visit = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=0;
    int ans=0;
    size_t sz=graph->dataSize;
    priorityQueue* pq = createPriorityQueue(sz,cmp);
    do{
        int node=n-1;
        int wt=0;
        if(pq->size){
            node=graph->edgeFinder(topPriorityQueue(pq));
            wt=graph->weightFinder(topPriorityQueue(pq));
            popPriorityQueue(pq);
        }
        if(visit[node]==1) continue;
        visit[node]=1;
        ans += wt;
        Node* tmp = graph->adjacencyList[node];
        while(tmp){
            int edge=graph->edgeFinder(tmp->data);
            int wt=graph->weightFinder(tmp->data);
            if(visit[edge]==0) pushPriorityQueue(pq,tmp->data);
            tmp=tmp->next;
        }
    }while(pq->size!=0);
    freePriorityQueue(pq);
    free(visit);
    return ans;
}

int* bellmanFord(Graph* graph,int startNode){
    int n = graph->numNodes;
    int* dis = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) dis[i]=INT_MAX;
    dis[startNode]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Node* tmp =  graph->adjacencyList[j];
            while(tmp){
                int u = j;
                int v = graph->edgeFinder(tmp->data);
                int wt = graph->weightFinder(tmp->data);
                if(dis[u]!=INT_MAX&&dis[v]>wt+dis[u]){
                    dis[v]=wt+dis[u];
                    if(i==n-1) {     // If NULL is returned, graph has Negative cycle
                        free(dis);
                        return NULL; 
                    }
                }
                tmp = tmp->next;
            }
        }
    }
    return dis;
}