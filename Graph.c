//Edward Lee
//Graph.c: Implements the Graph.h header file

//Include basic input and output, as well as the List code
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

//Define the Graph Object
typedef struct GraphObj{
    List *adj;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int BFSrecent;
} GraphObj;

typedef GraphObj* Graph;

//newGraph(): Makes a new Graph. Color: 0 = white, 1 = grey, 2 = black
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    int i = 0;
    for(i=1; i<=n; i++){
        G->adj[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->BFSrecent = NIL;
    return (G);
}

//freeGraph: Frees the memory attached to a graph
void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL){
        makeNull(*pG);
        free(*pG);
        *pG = NULL;
    }
}

//getOrder: Returns the order of the current Graph
int getOrder(Graph G){
    if(G==NULL){
        printf("getOrder error: cannot getOrder on a null graph\n");
        exit(1);
    }else{
        return G->order;
    }
}

//getSize: Returns the size of the current Graph
int getSize(Graph G){
    if(G==NULL){
        printf("getSize error: cannot getSize on a null graph\n");
        exit(1);
    }else{
        return G->size;
    }
}

//getSource: Returns the vertex most recently used as a BFS source
int getSource(Graph G){
    if(G==NULL){
        printf("getSource error: cannot getSource on a null graph\n");
        exit(1);
    }else{
        return G->BFSrecent;
    }
}

//getParent: Returns the parent Vertex of the specified vertex in the most recent BFS tree
int getParent(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getParent error; u is either < 1 or > getOrder(G)");
        exit(1);
        return 0;
    }else{
        return G->parent[u];
    }
}

//getDist: Returns the distance of the specified vertex from the most recent BFS source
int getDist(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getDist error; u is either < 1 or > getOrder(G)");
        exit(1);
        return 0;
    }else{
        return G->distance[u];
    }
}

//getPath: Returns the path from the most recent BFS source to the specified vertex
void getPath(List L, Graph G, int u){
    if(getSource(G) == NIL){
        printf("cannot getPath on a graph that has not run BFS yet");
        exit(1);
    }else if((u>getOrder(G)) || (u < 1)){
        printf("getPath error: u is either <1 or >getOrder(G)");
        exit(1);
    }else{
        prepend(L, u);
        if(u != getSource(G)){
            getPath(L, G, G->parent[u]);
        }
    }
}

//makeNull: Empties the Graph
void makeNull(Graph G){
    if(G==NULL){
        printf("makeNull error: cannot makeNull on a null graph\n");
        exit(1);
    }else{
        int i = 1;
        while(i <= getOrder(G)){
            clear(G->adj[i]);
            i++;
        }
    }
}

//sortedadd: Helper function for inserting the edges in the Adjacency List in the proper order
void sortedadd(List L, int i){
    if(length(L) == 0){
        append(L, i);
        return;
    }else{
        if(length(L) == 1){
            if(front(L) >= i){
                prepend(L, i);
                return;
            }else{
                append(L, i);
                return;
            }
        }else{
            moveFront(L);
            while(index(L) > 0){
                if(get(L) >= i){
                    insertBefore(L, i);
                    return;
                }
                moveBack(L);
            }
            append(L, i);
        }
    }
}

//BFSprocedure: Recursively runs the BFS on a specified depth, queue, and graph
void BFSprocedure(Graph G, int depth, List queue, int gen){
    if(length(queue) > 0){
        int n = 0;
        int count = 0;
        while(n < gen){
            int i = front(queue);
            G->color[i] = 2;
            moveFront(G->adj[i]);
            while(index(G->adj[i]) >= 0){
                if(G->color[get(G->adj[i])] == 0){
                    G->distance[get(G->adj[i])] = depth;
                    append(queue, get(G->adj[i]));
                    count++;
                    G->color[get(G->adj[i])] = 1;
                    G->parent[get(G->adj[i])] = i;
                }
                moveNext(G->adj[i]);
            }
            deleteFront(queue);
            n++;
        }
        BFSprocedure(G, depth+1, queue, count);
    }
}

//addEdge: Adds an edge to the Graph between the specified vertices
void addEdge(Graph G, int u, int v){
    if((u>=1) && (u<=getOrder(G)) && (v>=1) && (v<=getOrder(G))){
        sortedadd(G->adj[u], v);
        sortedadd(G->adj[v], u);
        G->size++;
    }else{
        printf("addEdge error: cannot add edge that is beyond the limits of the graph G\n");
        exit(1);
    }
}

//addArc: Adds a directed edge from the specified vertex to the other
void addArc(Graph G, int u, int v){
    if((u>=1) && (u<=getOrder(G)) && (v>=1) && (v<=getOrder(G))){
        sortedadd(G->adj[u], v);
    }
}

//BFS: Does the preliminary and postliminary functions of BFS before running the recursive part
void BFS(Graph G, int s){
    int i = 0;
    for(i = 1; i<=getOrder(G); i++){
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->BFSrecent = s;
    List queue = newList();
    append(queue, s);
    G->distance[s] = 0;
    BFSprocedure(G, 1, queue, 1);
    for(i=1; i<=getOrder(G); i++){
        G->color[i] = 0;
    }
}

//printGraph: Prints the graph to the specified file
void printGraph(FILE* out, Graph G){
    int i = 1;
    while(i<=getOrder(G)){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
        i++;
    }
}
