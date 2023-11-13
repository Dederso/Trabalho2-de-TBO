#ifndef _RTT_h_
#define _RTT_h_

#include "dijkstra.h"
#include "estrutura.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>



typedef struct 
{
    double** distancia;

}Distancias;

typedef struct 
{   
    int S;
    int C;
    double INF;

}Inflacao;

double RTT(int a, int b,Distancias* distancias,Estrutura* estrutura);

Distancias* criaDistancias(Estrutura* estrutura);

void imprimeDistancias(Distancias* distancias, Estrutura* estrutura);

void imprimeInflacao(Inflacao* inflacao, Estrutura* estrutura);

void liberaDistancias(Distancias* distancias, Estrutura* estrutura);

Inflacao* RTTS(Estrutura* estrutura,Distancias* distancias);

double calculaInf(double a, double b);

#endif
