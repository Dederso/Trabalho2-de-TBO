#ifndef _estrutura_h_
#define _estrutura_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct nos {
    int vertex;
    double weight;
    struct nos* next;
} Nos;

typedef struct {
    Nos** adjLists;
    int s;
    int c;
    int m;
    int V;
    int scm;
    int* S;
    int* C;
    int* M;
} Estrutura;


Nos* getNo(Estrutura* estrutura, int index);

int* getES(Estrutura* estrutura);
int* getEC(Estrutura* estrutura);
int* getEM(Estrutura* estrutura);

int getEV(Estrutura* estrutura);
int getEs(Estrutura* estrutura);
int getEc(Estrutura* estrutura);
int getEm(Estrutura* estrutura);

void printEstrutura(Estrutura* estrutura);
void destroiEstrutura(Estrutura* estrutura);


#endif