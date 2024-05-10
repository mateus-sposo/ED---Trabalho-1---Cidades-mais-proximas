#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

void criaArvore(tarvore *arvore){
    arvore->raiz = NULL;
}

void insereArvore(tno ** no, tcidade cidade, int i){
    if(*no == NULL){
        *no = (tno*)malloc(sizeof(tno));
        (*no)->cidade = cidade;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
    }else{
        if(i%2 == 0){
            if(cidade.latitude < (*no)->cidade.latitude){
                insereArvore(&(*no)->esq, cidade, ++i);
            }else{
                insereArvore(&(*no)->dir, cidade, ++i);
            }
        }
        else{
            if(cidade.longitude < (*no)->cidade.longitude){
                insereArvore(&(*no)->esq, cidade, ++i);
            }else{
                insereArvore(&(*no)->dir, cidade, ++i);
            }
        }
    }
}

void liberaArvore(tno * no){
    if(no->esq != NULL){
        liberaArvore(no->esq);
    }
    if(no->dir != NULL){
        liberaArvore(no->dir);
    }
    free(no);
}