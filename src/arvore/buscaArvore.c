#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

void buscaVizinhosRec(tno *no, tcidade cidade, tmaxHeap *heap, int h){
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
        if(h%2 == 0){
            if(cidade.latitude < no->cidade.latitude){
                buscaVizinhosRec(no->esq, cidade, heap, h+1);
                if(pow(cidade.latitude - no->cidade.latitude,2) < heap->vizinhos[0].distancia){
                    buscaVizinhosRec(no->dir, cidade, heap, h+1);
                }
            }else{
                buscaVizinhosRec(no->dir, cidade, heap, h+1);
                if(pow(cidade.latitude - no->cidade.latitude,2) < heap->vizinhos[0].distancia){
                    buscaVizinhosRec(no->esq, cidade, heap, h+1);
                }
            }
        }else{
            if(cidade.longitude < no->cidade.longitude){
                buscaVizinhosRec(no->esq, cidade, heap, h+1);
                if(pow(cidade.longitude - no->cidade.longitude,2) < heap->vizinhos[0].distancia){
                    buscaVizinhosRec(no->dir, cidade, heap, h+1);
                }
            }else{
                buscaVizinhosRec(no->dir, cidade, heap, h+1);
                if(pow(cidade.longitude - no->cidade.longitude,2) < heap->vizinhos[0].distancia){
                    buscaVizinhosRec(no->esq, cidade, heap, h+1);
                }
            }
        }
    }
}

void buscaVizinhos(tarvore *arvore, tcidade cidade, int n){
    tmaxHeap *heap = (tmaxHeap*)malloc(sizeof(tmaxHeap));
    constroiHeap(heap, n);

    buscaVizinhosRec(arvore->raiz, cidade, heap, 0);
    heapSort(heap);
    imprimeHeap(heap);
    liberaHeap(heap);
}