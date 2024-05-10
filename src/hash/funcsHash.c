#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

thash* criarHash(int tamanho){
    thash *hash = (thash*)malloc(sizeof(thash));
    hash->tamanho = tamanho;
    hash->cidades = (tcidade*)malloc(tamanho*sizeof(tcidade)+1);
    for(int i=0; i <= tamanho; i++){
        hash->cidades[i].codigo_ibge = 0;
    }
    return hash;
}

void insereCidadeCod(thash *hash, tcidade cidade){
    int i = 0;
    int pos; 
    while(true){
        pos = (h1(cidade.codigo_ibge, hash->tamanho) + i * h2(cidade.codigo_ibge, hash->tamanho)) % hash->tamanho;
        if(hash->cidades[pos].codigo_ibge == 0){
            hash->cidades[pos] = cidade;
            hash->atual += 1;
            break;
        }
        i++;
    }
}

void insereCidadeNome(thash *hash, tcidade cidade){
    int i = 0;
    int pos; 
    int valorNome = stringToInt(cidade.nome);
    while(true){
        pos = (h1(valorNome, hash->tamanho) + i * h2(valorNome, hash->tamanho)) % hash->tamanho;
        if(hash->cidades[pos].codigo_ibge == 0){
            hash->cidades[pos] = cidade;
            hash->atual += 1;
            break;
        }
        i++;
    }
}

void liberaHash(thash* hash){
    free(hash->cidades);
    free(hash);
}