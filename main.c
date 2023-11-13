#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "io.h"
#include "estrutura.h"
#include "dijkstra.h"
#include "RTT.h"
#include "heapInf.h"

int main(int argc, char const *argv[]){


     //clock_t inicio = clock();
    
    Estrutura* estrutura=lerCoordenadas(argv[1]);
   

    Distancias*distancias=criaDistancias(estrutura);

    Inflacao*inflacao=RTTS(estrutura,distancias);

    heapSortInf(inflacao,estrutura->s*estrutura->c);

    imprimeSaida(argv[2],inflacao,estrutura->s*estrutura->c);


     // clock_t fim = clock();
      //double tempo=(fim - inicio) / CLOCKS_PER_SEC;
      //printf("Tempo de execucao: %lf segundos\n",tempo);
    // imprimeInflacao(inflacao,estrutura);
    //printf("\n\ndistancias\n\n");
    //imprimeDistancias(distancias,estrutura);
    // printEstrutura(estrutura);
    

    free(inflacao);
    liberaDistancias(distancias,estrutura);
    destroiEstrutura(estrutura);
    return 0;
}
