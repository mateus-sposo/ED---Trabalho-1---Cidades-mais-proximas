#ifndef __LIBTRAB_H__
#define __LIBTRAB_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811

typedef unsigned char bool;
static const bool false = 0;
static const bool true = 1;

typedef struct _cidade{
    int codigo_ibge;
    char nome[MAX];
    double latitude;
    double longitude;
    bool capital;
    unsigned short codigo_uf;
    unsigned short siafi_id;
    unsigned short ddd;
    char fuso_horario[MAX];
}tcidade;

typedef struct _no{
    tcidade cidade;
    struct _no *esq;
    struct _no *dir;
}tno;

typedef struct _arvore{
    struct _no *raiz;
}tarvore;

typedef struct _hash{
    tcidade *cidades;
    int tamanho; // 16811 por ser primo
    int atual;
}thash;

typedef struct _vizinho{
    tcidade cidade;
    double distancia;
}tvizinho;

typedef struct _maxHeap{
    tvizinho *vizinhos;
    int tam;
    int tammax;
}tmaxHeap;

//pasta arvore
    //arquivo buscaArvore.c
void buscaVizinhosRec(tno *no, tcidade cidade, tmaxHeap *heap, int h);
void buscaVizinhos(tarvore *arvore, tcidade cidade, int n);
    //arquivo funcsArvore.c
void criaArvore(tarvore *arvore);
void insereArvore(tno ** no, tcidade cidade, int i);
void liberaArvore(tno *no);

//pasta hash
    //arquivo buscaHash.c
int stringToInt(char *str);
int h1(int codigo_ibge, int tamanho);
int h2(int codigo_ibge, int tamanho);
tcidade buscaIBGE(thash *hash, int codigo_ibge);
tcidade buscaNome(thash *hash, char *nome);
    //arquivo funcsHash.c
thash* criarHash(int tamanho);
void insereCidadeCod(thash *hash, tcidade cidade);
void insereCidadeNome(thash *hash, tcidade cidade);
void liberaHash(thash *hash);

//pasta heap
    //arquivo funcsHeap.c
double calculaDistancia(tcidade cidade1, tcidade cidade2);
void constroiHeap(tmaxHeap *heap, int n);
void insereHeap(tmaxHeap *heap, tvizinho vizinho);
void liberaHeap(tmaxHeap *heap);
void sobeHeap(tmaxHeap *heap, int i);
void desceHeap(tmaxHeap *heap, int i, int n);
void heapSort(tmaxHeap *heap);

//pasta main
    //arquivo imprime.c
void imprimeInformacoes(tcidade cidade);
void imprimeHeap(tmaxHeap *heap);
    //arquivo main.c
void lerArquivo(FILE* arquivo, thash* hash_cod, thash* hash_nome, tarvore *arvore);
void interface(thash *hash_cod, thash* hash_nome, tarvore *arvore);

#endif