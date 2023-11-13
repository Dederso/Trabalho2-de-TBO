#include "heapInf.h"



void heapifyInf(Inflacao *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].INF > arr[largest].INF)
        largest = l;

    if (r < n && arr[r].INF > arr[largest].INF)
        largest = r;

    if (largest != i) {
        Inflacao temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapifyInf(arr, n, largest);
    }
}

void heapSortInf(Inflacao *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyInf(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        Inflacao temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapifyInf(arr, i, 0);
    }
}
