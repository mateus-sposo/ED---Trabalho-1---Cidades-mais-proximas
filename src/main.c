#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

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

typedef struct _hash{
    tcidade *cidades;
    int tamanho; // 16811 por ser primo
}thash;

thash* criarHash(int tamanho){
    thash *hash = (thash*)malloc(sizeof(thash));
    hash->tamanho = tamanho;
    hash->cidades = (tcidade*)malloc(tamanho*sizeof(tcidade)+1);
    for(int i=0; i <= tamanho; i++){
        hash->cidades[i].codigo_ibge = 0;
    }
    return hash;
}

int h(int codigo_ibge, int tamanho){
    return (codigo_ibge) % tamanho;
}

void insereCidade(thash *hash, tcidade cidade){
    int i = 0;
    int pos; 
    while(true){
        pos = (h(cidade.codigo_ibge, hash->tamanho) + i * h(cidade.codigo_ibge, hash->tamanho))% hash->tamanho;
        if(hash->cidades[pos].codigo_ibge == 0){
            hash->cidades[pos] = cidade;
            break;
        }
        i++; //testar depois
    }
}

void imprimeInforamacoes(tcidade cidade){
    printf("Codigo IBGE: %d\n", cidade.codigo_ibge);
    printf("Nome: %s\n", cidade.nome);
    printf("Latitude: %lf\n", cidade.latitude);
    printf("Longitude: %lf\n", cidade.longitude);
    printf("Capital: %d\n", cidade.capital);
    printf("Codigo UF: %d\n", cidade.codigo_uf);
    printf("Siafi ID: %d\n", cidade.siafi_id);
    printf("DDD: %d\n", cidade.ddd);
    printf("Fuso Horario: %s\n", cidade.fuso_horario);
}

void buscaCidade(thash* hash, int codigo_ibge){
    int i = 0;
    int pos = h(codigo_ibge, hash->tamanho);
    int inicio = pos;
    while(true){
        if(hash->cidades[pos].codigo_ibge == codigo_ibge){
            printf("Cidade encontrada! %d\n", pos);
            imprimeInforamacoes(hash->cidades[pos]);
            break;
        }
        if(pos == inicio){
            printf("Cidade nao encontrada!\n");
            break;
        }
        i++;
        pos = (h(codigo_ibge, hash->tamanho) + i * h(codigo_ibge, hash->tamanho))% hash->tamanho;
    }
}

int main(){
    thash *hash = criarHash(16811);

    return EXIT_SUCCESS;
}
