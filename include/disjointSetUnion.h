typedef struct disjointSetUnion{
    int nodes;
    int* par;
    int* rank;
    int (*edgeFinder)(const void*);
} DSU;

DSU* createDSU(int n,int (*edgeFinder)(const void*));
void unionDSU(DSU*ds,void* u,void* v);
int sameComponent(DSU*ds,void* u,void* v);
int totalComponent(DSU* ds);
void freeDSU(DSU* ds);