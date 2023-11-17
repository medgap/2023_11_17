#include<stdio.h>
#include<stdlib.h>

#define MAX 32727

typedef struct Graph{
    char* vexs;
    int verNum;
    int** arcs;
    int arcNum;
}Graph;

typedef struct Edge{
    char vex;
    int weight;
}Edge;

Edge* initEdge(Graph* G, int index){
    Edge* edge = (Edge*)malloc(sizeof(Edge) * G->verNum);
    for(int i = 0; i < G->verNum; i++){
        edge[i].vex = G->vexs[index];
        edge[i].weight = G->arcs[index][i];
    }
    return edge;
}

int getMinIndex(Graph* G, Edge* edge){
    int min = MAX;
    int index;
    for(int i = 0; i < G->verNum; i++){
        if(edge[i].weight < min && edge[i].weight != 0){
            min = edge[i].weight;
            index = i;
        }
    }
    return index;
}

void Prim(Graph* G, int index){
    Edge* edge = initEdge(G,index);
    int min;
    for(int i = 0; i < G->verNum - 1; i++){
        min = getMinIndex(G,edge);
        printf("v%c-->v%c  weight = %d\n",edge[min].vex,G->vexs[min],edge[min].weight);
        edge[min].weight = 0;
        for(int j = 0 ; j < G->verNum; j++){
            if(G->arcs[min][j] < edge[j].weight){
                edge[j].weight = G->arcs[min][j];
                edge[j].vex = G->vexs[min];
            }
        }
    }
}

Graph* initGraph(int Vernum){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char) * Vernum);
    G->verNum = Vernum;
    G->arcs = (int**)malloc(sizeof(int*) * Vernum);
    for(int i = 0; i < Vernum; i++){
        G->arcs[i] = (int*)malloc(sizeof(int) * Vernum);
    }
    G->arcNum = 0;
    return G;
}

void createGraph(Graph* G, char* vexs, int* arcs){
    for(int i = 0; i < G->verNum; i++){
        G->vexs[i] = vexs[i];
        for(int j = 0; j < G->verNum; j++){
            G->arcs[i][j] = *(arcs + i * G->verNum + j);
            if(G->arcs[i][j] != 0 && G -> arcs[i][j] != MAX)
                G->arcNum++;
        }
    }
    G->arcNum /= 2;
}

void DFS(Graph* G, int* visited, int index){
    //depth first search
    printf("%c\t",G->vexs[index]);
    visited[index] = 1;
    for(int i = 0; i < G->verNum; i++){
        if(G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && !visited[i]){
            DFS(G,visited,i);
        }
    }
}

int main(){
    Graph* G = initGraph(6);
    int arcs[6][6] = {
            0, 6, 1, 5, MAX, MAX,
            6, 0, 5, MAX, 3, MAX,
            1, 5, 0, 5, 6, 4,
            5, MAX, 5, 0, MAX, 2,
            MAX, 3, 6, MAX, 0, 6,
            MAX, MAX, 4, 2, 6, 0
    };
    int* visited = (int*)malloc(sizeof(int) * G->verNum);
    for(int i = 0; i < 6; i++){
        visited[i] = 0;
    }
    createGraph(G,"123456",(int*)arcs);
    DFS(G,visited,0);
    printf("\n");
    Prim(G,0);
    printf("\n");
    return 0;
}