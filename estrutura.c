#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "estrutura.h"



#include <stdio.h>
#include <stdlib.h>

Nos* getNo(Estrutura* estrutura, int index) {
    if (index < 0 || index >= estrutura->V) {
        return NULL;
    }
    return estrutura->adjLists[index];
}



int* getES(Estrutura* estrutura) {
    return estrutura->S;
}
int* getEC(Estrutura* estrutura) {
    return estrutura->C;
}
int* getEM(Estrutura* estrutura) {
    return estrutura->M;
}



int getEs(Estrutura* estrutura){
    return estrutura->s;
}
int getEc(Estrutura* estrutura){
    return estrutura->c;
}
int getEm(Estrutura* estrutura){
    return estrutura->m;
}
int getEV(Estrutura* estrutura) {
    return estrutura->V;
}

void printEstrutura(Estrutura* estrutura) {
    for (int v = 0; v < estrutura->V; ++v) {
        Nos* no = estrutura->adjLists[v];
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (no) {
            printf("-> %d(%lf)", no->vertex, no->weight);
            no = no->next;
        }
        printf("\n");
    }
}

void destroiEstrutura(Estrutura* estrutura) {
    for (int v = 0; v < estrutura->V; ++v) {
        Nos* no = estrutura->adjLists[v];
        while (no) {
            Nos* temp = no;
            no = no->next;
            free(temp);
        }
    }
    free(estrutura->S);
    free(estrutura->C);
    free(estrutura->M);
    free(estrutura->adjLists);
    free(estrutura);
}

