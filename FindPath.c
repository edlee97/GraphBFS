//Edward Lee
//FindPath: Uses the Graph ADT and BFS to find the paths given between two vertices in a graph

//importation of pertinent files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
int main(int argc, char* argv[]){
    //Open files for reading and writing; if this cannot be done, exit
    FILE* in;
    FILE* out;
    int temp1;
    int temp2 = 1;
    if(argc != 3){
        printf("Usage error. %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    in = fopen(argv[1], "r");
    if(in==NULL){
        printf("unable to read from file %s\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if(out==NULL){
        printf("unable to write to file %s\n", argv[2]);
        exit(1);
    }
    fscanf(in, "%d", &temp1);
    //Creates a Graph from the contents in the input file
    Graph G = newGraph(temp1);
    while(temp1 != 0){
        fscanf(in, "%d %d", &temp1, &temp2);
        if((temp1 != 0) && (temp2 != 0)){
            addEdge(G, temp1, temp2);
        }
    }
    printGraph(out, G);
    fscanf(in, "%d %d", &temp1, &temp2);
    fprintf(out, "\n");
    //Reads additional lines from the input file to find paths
    while(temp1 != 0){
        if((temp1 != 0) && (temp2 != 0)){
            BFS(G, temp1);
            if(getDist(G, temp2) == INF){
                fprintf(out, "The distance from %d to %d is infinity\n", temp1, temp2);
                fprintf(out, "No %d-%d path exists", temp1, temp2);
            }else{
                fprintf(out, "The distance from %d to %d is %d\n", temp1, temp2, getDist(G, temp2));
                fprintf(out, "A shortest %d-%d path is: ", temp1, temp2);
                List L = newList();
                getPath(L, G, temp2);
                printList(out, L);
            }
            fprintf(out, "\n\n");
        }
        fscanf(in, "%d %d", &temp1, &temp2);
    }
    //Deallocate memory and close the files
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return 1;
}
