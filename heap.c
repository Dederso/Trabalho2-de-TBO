#include "heap.h"

// Cria um novo nó do heap
Node* createNode(int vertex, double distance) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->distance = distance;
    return newNode;
}

// Cria um heap com capacidade dada
Heap* createHeap(int capacity) {
    Heap* newHeap = (Heap*)malloc(sizeof(Heap));
    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->node = (Node*)malloc(capacity * sizeof(Node));
    return newHeap;
}

// Fix up function
void fix_up(Heap* heap, int i) {
    while (i != 0 && heap->node[(i - 1) / 2].distance > heap->node[i].distance) {
        Node temp = heap->node[i];
        heap->node[i] = heap->node[(i - 1) / 2];
        heap->node[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Fix down function
void fix_down(Heap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->node[left].distance < heap->node[smallest].distance)
        smallest = left;

    if (right < heap->size && heap->node[right].distance < heap->node[smallest].distance)
        smallest = right;

    if (smallest != i) {
        Node temp = heap->node[i];
        heap->node[i] = heap->node[smallest];
        heap->node[smallest] = temp;
        fix_down(heap, smallest);
    }
}

// Insert function
void insert(Heap* heap, Node* node) {
    if (heap->size == heap->capacity) {
        return;
    }
    heap->node[heap->size] = *node;
    heap->size++;

    // Call fix_up function
    fix_up(heap, heap->size - 1);
}

// Extrai o nó com a menor distância
Node extractMin(Heap* heap) {
    Node root = heap->node[0];
    heap->node[0] = heap->node[heap->size - 1];
    heap->size--;

    // Heapify
    int i = 0;
    fix_down(heap, i);

    return root;
}


void fix_value(Heap* heap, int i, double value) {
    heap->node[i].distance = value;
    fix_up(heap, i);
}

// Verifica se o heap está vazio
bool isEmpty(Heap* heap) {
    return heap->size == 0;
}

void freeNode(Node* node){
    free(node);
}

void freeHeap(Heap* heap) {
    if (heap == NULL) {
        return;
    }

    // Libera a memória alocada para os nós
    for (int i = 0; i < heap->size; i++) {
        freeNode(&heap->node[i]);
    }

    // Libera a memória alocada para o array de nós
    free(heap->node);

    // Libera a memória alocada para a heap
    free(heap);
}