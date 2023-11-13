#ifndef _dijkstra_h_
#define _dijkstra_h_

#include "estrutura.h"
#include "heap.h"

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int minDistance(Estrutura* estrutura,double dist[], bool sptSet[]);

void printSolution(Estrutura* estrutura,double dist[]);

double* dijkstra(Estrutura*estrutura,double* dist,int src);

void liberaDijkstra(double* dist);

#endif