#include "dijkstra.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>


int minDistance(Estrutura* estrutura,double dist[], bool sptSet[]) {
    double min = __LDBL_MAX__;  // Inicializa a variável "min" com um valor infinito.
    int min_index;      // Esta variável armazenará o índice do vértice com a menor distância.

    for (int v = 0; v < estrutura->V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            // Verifica se o vértice ainda não foi processado e se a distância é menor que "min".
            min = dist[v];      // Atualiza "min" com a nova menor distância encontrada.
            min_index = v;      // Armazena o índice do vértice com a menor distância.
        }
    }

    return min_index;  // Retorna o índice do vértice com a menor distância.
}


void printSolution(Estrutura*estrutura,double dist[]) {
    printf("Vértice \t Distância a partir da origem\n");
    for (int i = 0; i < estrutura->V; i++) {
        printf("%d \t\t %lf\n", i, dist[i]);
    }
}


void liberaDijkstra(double* dist){
    free(dist);
}


double* dijkstra(Estrutura* estrutura,double* dist, int src) {
    int V = getEV(estrutura);
    bool sptSet[V];
    Heap* heap = createHeap(V);
    
    for (int i = 0; i < V; i++) {
        dist[i] = __DBL_MAX__;
        sptSet[i] = false;
    }

    dist[src] = 0;
    Node* source = createNode(src, dist[src]);
    insert(heap,source);
    free(source);
    //printf("src=%d\n",src);

    while (!isEmpty(heap)) {
        Node u = extractMin(heap);
        sptSet[u.vertex] = true;

        Nos* adjList = getNo(estrutura, u.vertex);
        Node* aux;
        while (adjList != NULL) {
            int v = adjList->vertex;
            if (!sptSet[v] && dist[u.vertex] != __DBL_MAX__ && dist[u.vertex] + adjList->weight < dist[v]) {
                dist[v] = dist[u.vertex] + adjList->weight;
                aux= createNode(v, dist[v]);
                insert(heap,aux);
                free(aux);
            }
            adjList = adjList->next;
        }
    }
    // for(int i=0;i<V;i++){
    //     printf("dist[%d]=%lf\n",i,dist[i]);
    // }
    freeHeap(heap);
    return dist;
}