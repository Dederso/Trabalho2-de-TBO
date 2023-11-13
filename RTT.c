#include "RTT.h"
#include "time.h"

double RTT(int a, int b,Distancias* distancias,Estrutura* estrutura){
    double RTT;
    //Servidores vao de 0 a S-1
    //Clientes vao de S a S+C-1
    //Monitores vao de S+C a S+C+M-1
    int x,y;
    x=estrutura->S[a];
    y=estrutura->C[b];
    RTT=distancias->distancia[a][y]+distancias->distancia[b+estrutura->s][x];

    //printf("RTT(%d,%d)=%.16lf = %.16lf+%.16lf \n",a,b,RTT,distancias->distancia[a][b],distancias->distancia[b][a]);

    return RTT;
};

Distancias* criaDistancias(Estrutura* estrutura){

    Distancias* distancias=(Distancias*)malloc(sizeof(Distancias));
    int total=estrutura->scm;
    distancias->distancia=(double**)malloc(sizeof(double*)* total );
    if(distancias->distancia==NULL){
        perror("Erro ao alocar memória");
        exit(1);
    }

    //clock_t inicio = clock();
    
    int i,j,k,l;
    i=j=k=l=0;

        for(i=0;i<estrutura->scm;i++){

            //Aloca os valores e preenche a matriz
            if(i<estrutura->s){   
                double * temp=malloc(sizeof(double)*estrutura->V);
                temp=dijkstra(estrutura,temp,estrutura->S[i]);//Servidores vao de 0 a S-1         
                distancias->distancia[i]=temp;
                
                //printf("Distancia %d servidor %d\n",i,estrutura->S[j]);
            }
            else if(i<estrutura->s+estrutura->c){
                double * temp=malloc(sizeof(double)*estrutura->V);
                temp=dijkstra(estrutura,temp,estrutura->C[i- (estrutura->s)]);//Clientes vao de S a S+C-1

                
                distancias->distancia[i]=temp;
                //printf("Distancia %d %lf\n",i,distancias->distancia[i][0]);
                //printf("Distancia %d cliente %d\n",i,estrutura->C[k]);
            }

            else{
                double * temp=malloc(sizeof(double)*estrutura->V);
                temp=dijkstra(estrutura,temp,estrutura->M[i- (estrutura->s+estrutura->c)]);//Monitores vao de S+C a S+C+M-1
                distancias->distancia[i]=temp;
            // printf("Distancia %d monitor %d\n",i,estrutura->M[l]);
            }
        }

    //clock_t fim = clock();
    //double tempo=(fim - inicio) / CLOCKS_PER_SEC;
    //printf("Tempo de execucao dijkstra: %lf segundos\n",tempo);
    

    return distancias;
};

void imprimeDistancias(Distancias* distancias,Estrutura* estrutura){
    int i,j;
    printf("Distancias\n");

    for(i=0;i<estrutura->scm;i++){
        if(i<estrutura->s){
            for(j=0;j<estrutura->V;j++){
                printf("%d  %d   %lf\n",estrutura->S[i],j,distancias->distancia[i][j]);
            }
        }
        else if(i<estrutura->s+estrutura->c){
            for(j=0;j<estrutura->V;j++){
                printf("%d  %d   %lf\n",estrutura->C[i- estrutura->s],j,distancias->distancia[i][j]);
            }      
        }
        else{
            for(j=0;j<estrutura->V;j++){
                printf("%d  %d   %lf\n",estrutura->M[i-(estrutura->s+estrutura->c)],j,distancias->distancia[i][j]);
            }
        }
    }
        
};

void imprimeInflacao(Inflacao* inflacao,Estrutura* estrutura){
    for(int i=0;i<estrutura->s*estrutura->c;i++){
        printf("%d %d %.16lf \n",inflacao[i].S,inflacao[i].C,inflacao[i].INF);
    }
};
void liberaDistancias(Distancias* distancias,Estrutura* estrutura){
    for(int i=0;i<estrutura->scm;i++){
        free(distancias->distancia[i]);
    }
    free(distancias->distancia);
    free(distancias);
};

double calculaInf(double a, double b){
    double c;
    c=b/a;
    //printf("a=%.15lf b=%.15lf c=%.15lf\n",a,b,c);
    return c;
};




static double RTTM(int a, int b,int c,Distancias* distancias,Estrutura* estrutura){
    double RTT,RTTM;
    //Servidores vao de 0 a S-1
    //Clientes vao de S a S+C-1
    //Monitores vao de S+C a S+C+M-1
    int x,y,z;
    x=estrutura->S[a];
    y=estrutura->C[b];
    z=estrutura->M[c];

    RTT=distancias->distancia[a][z]+distancias->distancia[c+estrutura->s+estrutura->c][x];

    RTTM=distancias->distancia[c+estrutura->s+estrutura->c][y]+distancias->distancia[b+estrutura->s][z];

    //printf("RTT(%d,%d)=%.16lf = %.16lf+%.16lf \n",a,b,RTT,distancias->distancia[a][b],distancias->distancia[b][a]);
    RTTM+=RTT;
    return RTTM;
};








Inflacao* RTTS (Estrutura*estrutura,Distancias*distancias){// a mudar
    int a,b,c,aux=0;
    double rtt,rtt2,rtt3;
    //printf("\ns=%d c=%d m=%d\n",estrutura->s,estrutura->c,estrutura->m);
    Inflacao* inflacao=(Inflacao*)malloc((estrutura->s*estrutura->c)*sizeof(Inflacao));//Aloca o vetor de inflacao
    
    if(inflacao==NULL){
        perror("Erro ao alocar memória");
        exit(1);
    }	

    for(int i=0;i<estrutura->s;i++){
        for(int j=0;j<estrutura->c;j++){
            a=estrutura->S[i];
            b=estrutura->C[j];
           
            inflacao[aux].C=b;
            inflacao[aux].S=a;
            
            rtt=RTT(i,j,distancias,estrutura);//Distancia de RTT(S,C)
            
            //printf("s=%d c=%d rtt=%lf\n",a,b,rtt);
           // printf("s=%d c=%d rtt=%lf\n\n",i,j+estrutura->s,rtt);


            rtt2=__DBL_MAX__;
            rtt3=__DBL_MAX__;
           for(int k=0;k<estrutura->m;k++){
                c=estrutura->M[k];
               
                rtt2=RTTM(i,j,k,distancias,estrutura);//Distancia de RTT*(S,M,C)
                
                if(rtt2<rtt3){
                    rtt3=rtt2;//Escolhe o menor monitor
                };
            }
            inflacao[aux].INF=calculaInf(rtt,rtt3);//calcula inflaçao
            aux++;
        }
    }
    return inflacao;
};