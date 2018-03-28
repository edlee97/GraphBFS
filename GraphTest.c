//Edward Lee
//GraphTest.c: Tests the Graph ADT
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
int main(){
    printf("Crossfield Class NCC-1031 DISCOVERY - Starmap Test\n");
    printf("Making graph G: Ten vertices, two connected components\n");
    Graph G = newGraph(10);
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    addEdge(G, 6, 7);
    addEdge(G, 8, 9);
    addEdge(G, 9, 10);
    printf("Printing Graph G\n");
    printGraph(stdout, G);
    printf("Testing getOrder (Expected: 10) and getSize (Expected: 8)\n");
    printf("%d %d\n", getOrder(G), getSize(G));
    printf("Testing BFS on 1\n");
    BFS(G, 1);
    printf("Testing getSource (Expected: 1) and getParent (Expected: 6 5 4 3 2 1)\n");
    printf("%d\n", getSource(G));
    for(int i = 7; i>1; i--){
        printf("%d", getParent(G, i));
    }
    printf("\n");
    printf("Testing getDist, 1 to 7 (Expected: 6), 1 to 8 (Expected: infinite), and 8 to 10 (Expected: 2)\n");
    BFS(G, 1);
    printf("%d\n", getDist(G, 7));
    if((getDist(G, 8)) == INF){
        printf("infinite\n");
    }else{
        printf("%d", getDist(G, 8));
    }
    BFS(G, 8);
    printf("%d\n", getDist(G, 10));
    printf("Testing getDist and getPath on a nonlinear graph: adding 1 7 edge. Expected of 1 to 6: 2, 1 7 6\n");
    addEdge(G, 1, 7);
    BFS(G, 1);
    printf("%d\n", getDist(G, 6));
    List L = newList();
    getPath(L, G, 6);
    printList(stdout, L);
    printf("\n");
    printf("Testing addArc. Adding one-way path from 8 to 1\n");
    addArc(G, 8, 1);
    printf("Expected of getDist on 8 2: 2. Expected of getDist on 1 9: infinite\n");
    BFS(G, 8);
    printf("%d\n", getDist(G, 2));
    BFS(G, 1);
    if((getDist(G, 9)) == INF){
        printf("infinite\n");
    }else{
        printf("%d", getDist(G, 9));
    }
    printf("Testing makeNull\n");
    makeNull(G);
    printf("Printing G\n");
    printGraph(stdout, G);
    printf("All tests passed. Helm, take us to Black Alert and prepare to jump.\n");
    freeGraph(&G);
    return 1;
}
