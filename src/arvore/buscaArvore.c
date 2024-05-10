#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

void buscaVizinhosRec(tno *no, tcidade cidade, tmaxHeap *heap){
    if(no != NULL){
        tvizinho vizinho;
        vizinho.cidade = no->cidade;
        vizinho.distancia = calculaDistancia(cidade, no->cidade);
        if(heap->tam < heap->tammax && vizinho.distancia > 0){
            insereHeap(heap, vizinho);
        }else{
            if(vizinho.distancia < heap->vizinhos[0].distancia && vizinho.distancia > 0){
                heap->vizinhos[0] = vizinho;
                desceHeap(heap, 0, heap->tam);
            }
        }
        buscaVizinhosRec(no->esq, cidade, heap);
        buscaVizinhosRec(no->dir, cidade, heap);
    }
}

void buscaVizinhos(thash *hash, tarvore *arvore, tcidade cidade, int n){
    int i = 0;
    int pos = h1(cidade.codigo_ibge, hash->tamanho);
    while(true){
        if(hash->cidades[pos].codigo_ibge == cidade.codigo_ibge){
            break;
        }
        if(i > hash->tamanho){
            printf("Cidade nao encontrada!\n");
            return;
        }
        i++;
        pos = (h1(cidade.codigo_ibge, hash->tamanho) + i * h2(cidade.codigo_ibge, hash->tamanho)) % hash->tamanho;
    }

    tmaxHeap *heap = (tmaxHeap*)malloc(sizeof(tmaxHeap));
    constroiHeap(heap, n);

    buscaVizinhosRec(arvore->raiz, hash->cidades[pos], heap);
    heapSort(heap);
    imprimeHeap(heap);
    liberaHeap(heap);
}