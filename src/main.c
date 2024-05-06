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
    int n;
}tmaxHeap;

int h1(int codigo_ibge, int tamanho){
    return (codigo_ibge) % tamanho;
}

int h2(int codigo_ibge, int tamanho){
    return 1 + (codigo_ibge) % (tamanho - 1);
}

double calculaDistancia(tcidade cidade1, tcidade cidade2){
    return sqrt(pow(cidade1.latitude - cidade2.latitude, 2) + pow(cidade1.longitude - cidade2.longitude, 2));
}

thash* criarHash(int tamanho){
    thash *hash = (thash*)malloc(sizeof(thash));
    hash->tamanho = tamanho;
    hash->cidades = (tcidade*)malloc(tamanho*sizeof(tcidade)+1);
    for(int i=0; i <= tamanho; i++){
        hash->cidades[i].codigo_ibge = 0;
    }
    return hash;
}

void imprimeInformacoes(tcidade cidade){
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

void insereCidade(thash *hash, tcidade cidade){
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

void buscaIBGE(thash* hash, int codigo_ibge){
    int i = 0;
    int pos = h1(codigo_ibge, hash->tamanho);
    while(true){
        if(hash->cidades[pos].codigo_ibge == codigo_ibge){
            printf("Cidade encontrada!\n");
            printf("--------------------------\n");
            imprimeInformacoes(hash->cidades[pos]);
            break;
        }
        if(i > hash->tamanho){
            printf("Cidade nao encontrada!\n");
            break;
        }
        i++;
        pos = (h1(codigo_ibge, hash->tamanho) + i * h2(codigo_ibge, hash->tamanho)) % hash->tamanho;
    }
}

void liberaHash(thash* hash){
    free(hash->cidades);
    free(hash);
}

void criaArvore(tarvore *arvore){
    arvore->raiz = NULL;
}

void insereArvore(tarvore *arvore, tcidade cidade){
    tno *novo = (tno*)malloc(sizeof(tno));
    novo->cidade = cidade;
    novo->esq = NULL;
    novo->dir = NULL;
    if(arvore->raiz == NULL){
        arvore->raiz = novo;
    }else{
        int i = 0;
        tno *atual = arvore->raiz;
        tno *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(i%2 == 0){
                if(cidade.latitude < atual->cidade.latitude){
                    atual = atual->esq;
                }else{
                    atual = atual->dir;
                }
            }
            else{
                if(cidade.longitude < atual->cidade.longitude){
                    atual = atual->esq;
                }else{
                    atual = atual->dir;
                }
            }
            i++;
        }
        if(cidade.latitude < anterior->cidade.latitude){
            anterior->esq = novo;
        }
        else{
            anterior->dir = novo;
        }
    }
}

void constroiHeap(tmaxHeap *heap, int n){
    heap->vizinhos = (tvizinho*)malloc(n*sizeof(tvizinho));
    heap->n = n;
}

void buscaVizinhos(thash *hash, tarvore *arvore, int codigo_ibge, int n){
    int i = 0;
    int pos = h1(codigo_ibge, hash->tamanho);
    while(true){
        if(hash->cidades[pos].codigo_ibge == codigo_ibge){
            break;
        }
        if(i > hash->tamanho){
            printf("Cidade nao encontrada!\n");
            return;
        }
        i++;
        pos = (h1(codigo_ibge, hash->tamanho) + i * h2(codigo_ibge, hash->tamanho)) % hash->tamanho;
    }

    tmaxHeap *heap = (tmaxHeap*)malloc(sizeof(tmaxHeap));
    constroiHeap(heap, n);


}

void lerArquivo(FILE* arquivo, thash* hash, tarvore *arvore){
    char linha[200];
    tcidade cidade;
    while(fgets(linha, 200, arquivo)){
        if(strstr(linha, "codigo_ibge")){
            sscanf(linha, "    \"codigo_ibge\": %d,", &cidade.codigo_ibge);
        }
        if(strstr(linha, "nome")){
            sscanf(linha, "    \"nome\": \"%[^\"]\",", cidade.nome);
        }
        if(strstr(linha, "latitude")){
            sscanf(linha, "    \"latitude\": %lf,", &cidade.latitude);
        }
        if(strstr(linha, "longitude")){
            sscanf(linha, "    \"longitude\": %lf,", &cidade.longitude);
        }
        if(strstr(linha, "capital")){
            sscanf(linha, "    \"capital\": %d,", &cidade.capital);
        }
        if(strstr(linha, "codigo_uf")){
            sscanf(linha, "    \"codigo_uf\": %d,", &cidade.codigo_uf);
        }
        if(strstr(linha, "siafi_id")){
            sscanf(linha, "    \"siafi_id\": %d,", &cidade.siafi_id);
        }
        if(strstr(linha, "ddd")){
            sscanf(linha, "    \"ddd\": %d,", &cidade.ddd);
        }
        if(strstr(linha, "fuso_horario")){
            sscanf(linha, "    \"fuso_horario\": \"%[^\"]\",", cidade.fuso_horario);
            insereCidade(hash, cidade);
            insereArvore(arvore, cidade);
        }
    }
}

void interface(thash *hash, tarvore *arvore){
    int opcao = 0;
    while(opcao != 4){
        printf("--------------------------\n");
        printf("1 - Busca por Codigo IBGE\n");
        printf("2 - Busca os n Vizinhos\n");
        printf("3 - Busca por os n Vizinhos pelo Nome da Cidade\n");
        printf("4 - Sair\n");
        printf("--------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("--------------------------\n");
        int codigo_ibge = 0;
        int n;
        
        switch(opcao){
            case 1:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                buscaIBGE(hash, codigo_ibge);
                break;
            case 2:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                printf("Digite a quantidade de vizinhos: ");
                scanf("%d", &n);
                buscaVizinhos(hash, arvore, codigo_ibge, n);
                break;
            case 3:
                printf("Digite o nome da cidade: ");
                char nome[MAX];
                scanf("%s", nome);
                //buscaNome(hash, nome);
                break;
            case 4:
                liberaHash(hash);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

int main(){
    thash *hash = criarHash(TAM);
    FILE* arquivo = fopen("../dados/municipios.json", "r");
    tarvore *arvore = (tarvore*)malloc(sizeof(tarvore));
    criaArvore(arvore);

    lerArquivo(arquivo, hash, arvore);

    interface(hash, arvore);

    fclose(arquivo);
    return EXIT_SUCCESS;
}