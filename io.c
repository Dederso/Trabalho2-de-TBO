#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include <time.h>
#include "estrutura.h"
#include "RTT.h"

Estrutura* lerCoordenadas(const char* arquivo) {
    FILE* file = fopen(arquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    
    int V, E, S, C, M; 
    int aux = 0;
    int a, b;
    double peso;

    fscanf(file, "%d %d", &V, &E);
    fscanf(file, "%d %d %d", &S, &C, &M);

    Estrutura* estrutura = malloc(sizeof(Estrutura));
    estrutura->adjLists = malloc(V * sizeof(Nos*));

    for (int i = 0; i < V; i++) {
        estrutura->adjLists[i] = NULL;
    }

    //atribui os valores lidos para a estrutura
    estrutura->S=malloc(S*sizeof(int));
    estrutura->s=S;
    estrutura->C=malloc(C*sizeof(int));
    estrutura->c=C; 
    estrutura->M=malloc(M*sizeof(int));
    estrutura->m=M;
    estrutura->V=V; 
    estrutura->scm=S+C+M;
    
    int i;
    while (aux<S)
    {
        fscanf(file, "%d", &i);
        estrutura->S[aux]=i;
        aux++;
    }
    aux = 0;

    while (aux<C)
    {
        fscanf(file, "%d", &i);
        estrutura->C[aux]=i;
        aux++;
    }
    aux=0;

    while (aux<M)
    {
        fscanf(file, "%d", &i);
        estrutura->M[aux]=i;
        aux++;
    }
    aux=0;
    
    // Lê as coordenadas
    while (aux < E) {
        fscanf(file, "%d %d %lf", &a, &b, &peso);
        Nos* newNode = malloc(sizeof(Nos));
        newNode->vertex = b;
        newNode->weight = peso;
        newNode->next = estrutura->adjLists[a];
        estrutura->adjLists[a] = newNode;
        aux++;
    }

    fclose(file);
    return estrutura;
}


void imprimeSaida(const char* arquivo, Inflacao* inf,int max) {
    FILE* file = fopen(arquivo, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    for(int i=0;i<max;i++){
        fprintf(file, "%d %d %.16lf\n", inf[i].S, inf[i].C, inf[i].INF);
    }

    fclose(file);
}
