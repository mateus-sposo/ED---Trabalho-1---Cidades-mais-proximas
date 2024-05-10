#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

int stringToInt(char* string){
    int valor = 0;
    for(int i = 0; i < strlen(string); i++){
        valor += string[i];
    }
    return abs(valor);
}

int h1(int codigo_ibge, int tamanho){
    return (codigo_ibge) % tamanho;
}

int h2(int codigo_ibge, int tamanho){
    return 1 + (codigo_ibge) % (tamanho - 1);
}

tcidade buscaIBGE(thash* hash, int codigo_ibge){
    int i = 0;
    int pos = h1(codigo_ibge, hash->tamanho);
    while(true){
        if(hash->cidades[pos].codigo_ibge == codigo_ibge){
            return hash->cidades[pos];
        }
        if(i > hash->tamanho){
            printf("Cidade nao encontrada!\n");
            tcidade falsa;
            falsa.codigo_ibge = 0;
            return falsa;
        }
        i++;
        pos = (h1(codigo_ibge, hash->tamanho) + i * h2(codigo_ibge, hash->tamanho)) % hash->tamanho;
    }
    return hash->cidades[pos];
}

tcidade buscaNome(thash* hash, char* nome){
    int i = 0;
    int pos;
    int valorNome = stringToInt(nome);
    tcidade possibilidades[10];
    int j = 0;
    while(true){
        pos = (h1(valorNome, hash->tamanho) + i * h2(valorNome, hash->tamanho)) % hash->tamanho;
        if(strcmp(hash->cidades[pos].nome, nome) == 0){
            bool flag = 0;
            for(int k = 0; k < j; k++){
                if(possibilidades[k].codigo_ibge == hash->cidades[pos].codigo_ibge){
                    flag = 1;
                }
            }
            if(flag == 0){
                possibilidades[j] = hash->cidades[pos];
                j++;
            }
        }
        if(i > hash->tamanho && j == 0){
            tcidade falsa;
            falsa.codigo_ibge = 0;
            return falsa;
        }
        
        if(i > hash->tamanho && j > 0){
            if(j == 1){
                return possibilidades[0];
            }
            int num;
            printf("--------------------------------------\n");
            printf("Cidades encontradas:\n\n");
            for(int k = 0; k < j; k++){
                printf("%d - %s, %d\n", k+1, possibilidades[k].nome, possibilidades[k].codigo_ibge);
            }
            printf("--------------------------------------\n");
            printf("Digite o numero da cidade desejada: ");
            scanf("%d", &num);
            return possibilidades[num-1];
        }
        i++;
    }
    return hash->cidades[pos];
}