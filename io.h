#ifndef _io_h_
#define _io_h_

#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"
#include "RTT.h"
Estrutura*lerCoordenadas(const char* arquivo);

void imprimeSaida(const char* arquivo, Inflacao* inf,int max);
#endif