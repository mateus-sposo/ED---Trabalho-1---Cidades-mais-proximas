#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct _hash{
    tcidade *cidades;
    int tamanho; // 16811 por ser primo
    int atual;
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

int h1(int codigo_ibge, int tamanho){
    return (codigo_ibge) % tamanho;
}

int h2(int codigo_ibge, int tamanho){
    return 1 + (codigo_ibge) % (tamanho - 1);
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

void lerArquivo(FILE* arquivo, thash* hash){
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
        }
    }
}

void liberaHash(thash* hash){
    free(hash->cidades);
    free(hash);
}

void interface(thash *hash){
    int opcao = 0;
    while(opcao != 4){
        printf("--------------------------\n");
        printf("1 - Busca por Codigo IBGE\n");
        printf("2 - Busca n Vizinhos\n");
        printf("3 - Busca por Nome\n");
        printf("4 - Sair\n");
        printf("--------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("--------------------------\n");
        int codigo_ibge;
        switch(opcao){
            case 1:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                buscaIBGE(hash, codigo_ibge);
                break;
            case 2:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                //buscaVizinhos(hash, codigo_ibge);
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
    lerArquivo(arquivo, hash);

    interface(hash);

    fclose(arquivo);
    return EXIT_SUCCESS;
}