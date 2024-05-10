#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

double calculaDistancia(tcidade cidade1, tcidade cidade2){
    return pow(cidade1.latitude - cidade2.latitude, 2) + pow(cidade1.longitude - cidade2.longitude, 2);
}

void constroiHeap(tmaxHeap *heap, int n){
    heap->vizinhos = (tvizinho*)malloc(n*sizeof(tvizinho));
    heap->tammax = n;
    heap->tam = 0;
}

void insereHeap(tmaxHeap *heap, tvizinho vizinho){
    heap->vizinhos[heap->tam] = vizinho;
    sobeHeap(heap, heap->tam);
    (heap->tam)++;
}

void liberaHeap(tmaxHeap * heap){
    free(heap->vizinhos);
    free(heap);
}

void sobeHeap(tmaxHeap *heap, int i){
    int pai = (i-1)/2;
    if(i > 0 && heap->vizinhos[i].distancia > heap->vizinhos[pai].distancia){
        tvizinho aux = heap->vizinhos[i];
        heap->vizinhos[i] = heap->vizinhos[pai];
        heap->vizinhos[pai] = aux;
        sobeHeap(heap, pai);
    }
}

void desceHeap(tmaxHeap *heap, int i, int n){
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    int maior = i;
    if(esq < n && heap->vizinhos[esq].distancia > heap->vizinhos[maior].distancia){
        maior = esq;
    }
    if(dir < n && heap->vizinhos[dir].distancia > heap->vizinhos[maior].distancia){
        maior = dir;
    }
    if(maior != i){
        tvizinho aux = heap->vizinhos[i];
        heap->vizinhos[i] = heap->vizinhos[maior];
        heap->vizinhos[maior] = aux;
        desceHeap(heap, maior, n);
    }
}

void heapSort(tmaxHeap *heap){
    for(int i = heap->tam-1; i > 0; i--){
        tvizinho aux = heap->vizinhos[0];
        heap->vizinhos[0] = heap->vizinhos[i];
        heap->vizinhos[i] = aux;
        desceHeap(heap, 0, i);
    }
}