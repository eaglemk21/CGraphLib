#include<stdio.h>
#include<stdlib.h>
#include"disjointSetUnion.h"

DSU* createDSU(int n,int (*edgeFinder)(const void*)){
    DSU* ds = malloc(sizeof(DSU));
    ds->nodes=n;
    ds->rank=malloc((n+1)*sizeof(int));
    ds->par=malloc((n+1)*sizeof(int));
    ds->edgeFinder=edgeFinder;
    for(int i=0;i<n+1;i++) {
        ds->rank[i]=0;
        ds->par[i]=i;
    }
    return ds;
}

int parent(DSU* ds,int node){
    if(node==(ds->par[node])) return node;
    return ds->par[node]=parent(ds,ds->par[node]);
}

void unionDSU(DSU* ds,void* u,void* v){
    int pu=parent(ds,ds->edgeFinder(u));
    int pv=parent(ds,ds->edgeFinder(v));
    if(ds->rank[pu]>ds->rank[pv]){
        ds->par[pv]=pu;
    }
    else if(ds->rank[pu]<ds->rank[pv]){
        ds->par[pu]=pv;
    }
    else{
        ds->par[pu]=pv;
        ds->rank[pv]++;
    }
}

int sameComponent(DSU*ds,void* u,void* v){
    return ds->par[ds->edgeFinder(u)]==ds->par[ds->edgeFinder(v)];
}

int totalComponent(DSU* ds){
    int ans=0;
    int n=ds->nodes;
    int* visit = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) visit[i]=0;
    for(int i=0;i<n;i++){
        int par=parent(ds,i);
        if(visit[par]==0) ans++;
        visit[par]=1;
    }
    return ans;
}

void freeDSU(DSU* ds){
    free(ds->rank);
    free(ds->par);
    free(ds);
}