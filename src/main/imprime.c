#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

void imprimeInformacoes(tcidade cidade){
    printf("--------------------------------------\n");
    printf("Codigo IBGE: %d\n", cidade.codigo_ibge);
    printf("Nome: \"%s\"\n", cidade.nome);
    printf("Latitude: %lf\n", cidade.latitude);
    printf("Longitude: %lf\n", cidade.longitude);
    printf("Capital: %d\n", cidade.capital);
    printf("Codigo UF: %d\n", cidade.codigo_uf);
    printf("Siafi ID: %d\n", cidade.siafi_id);
    printf("DDD: %d\n", cidade.ddd);
    printf("Fuso Horario: \"%s\"\n", cidade.fuso_horario);
}

void imprimeHeap(tmaxHeap *heap){
    for(int i = 1; i <= heap->tam; i++){
        printf("--------------------------------------\n");
        printf("%d - Cidade: %s\n", i, heap->vizinhos[i-1].cidade.nome);
        printf("        Distancia: %lf\n", sqrt(heap->vizinhos[i-1].distancia));
    }
}