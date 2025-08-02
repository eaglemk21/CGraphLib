#include <stdio.h>
#include <stdlib.h>
#include "disjointSetUnion.h"

int edgeFinder(const void* node){
    return *(int*)node;  
}

int main() {
    int d0=0;
    int d1=1;
    int d2=2;
    int d3=3;
    
    DSU* ds = createDSU(4,edgeFinder);
    unionDSU(ds,&d1,&d0);
    unionDSU(ds,&d2,&d3);
    printf(" 1 and 0 belong to some component %d\n",sameComponent(ds,&d1,&d0));  // true
    printf(" 2 and 0 belong to some component %d\n",sameComponent(ds,&d2,&d0));  // false
    printf("Total Components %d\n",totalComponent(ds));  // 2 components
    freeDSU(ds);
    return 0;
}
