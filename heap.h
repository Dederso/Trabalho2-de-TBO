#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "estrutura.h"

typedef struct {
    int vertex;
    double distance;
} Node;

typedef struct {
    Node* node;
    int capacity; 
    int size;
} Heap;

Node* createNode(int vertex, double distance);

// Cria um heap com capacidade dada
Heap* createHeap(int capacity);

// Insere um nó no heap
void insert(Heap* heap, Node* node);

// Extrai o nó com a menor distância
Node extractMin(Heap* heap) ;

void fix_value(Heap* heap, int i, double value);

// Verifica se o heap está vazio
bool isEmpty(Heap* heap);

void freeHeap(Heap* heap);

void freeNode(Node* node);


#endif