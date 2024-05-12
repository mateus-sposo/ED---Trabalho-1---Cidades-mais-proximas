#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define TAM 16811
#include "../../include/libtrab.h"

void lerArquivo(FILE* arquivo, thash* hash_cod, thash* hash_nome, tarvore *arvore){
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
            sscanf(linha, "    \"capital\": %hhd,", &cidade.capital);
        }
        if(strstr(linha, "codigo_uf")){
            sscanf(linha, "    \"codigo_uf\": %hd,", &cidade.codigo_uf);
        }
        if(strstr(linha, "siafi_id")){
            sscanf(linha, "    \"siafi_id\": %hd,", &cidade.siafi_id);
        }
        if(strstr(linha, "ddd")){
            sscanf(linha, "    \"ddd\": %hd,", &cidade.ddd);
        }
        if(strstr(linha, "fuso_horario")){
            sscanf(linha, "    \"fuso_horario\": \"%[^\"]\",", cidade.fuso_horario);
            insereCidadeCod(hash_cod, cidade);
            insereCidadeNome(hash_nome, cidade);
            insereArvore(&arvore->raiz, cidade, 0);
        }
    }
}

void interface(thash *hash_cod, thash *hash_nome, tarvore *arvore){
    int opcao = 0;
    while(opcao != 4){
        printf("--------------------------------------\n");
        printf("1 - Busca por Codigo IBGE\n");
        printf("2 - Busca os n Vizinhos\n");
        printf("3 - Busca por os n Vizinhos pelo Nome da Cidade\n");
        printf("4 - Sair\n");
        printf("--------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("--------------------------------------\n");
        int codigo_ibge = 0;
        int n;
        
        switch(opcao){
            case 1:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                if(codigo_ibge > 0){
                    tcidade imprime = buscaIBGE(hash_cod, codigo_ibge);
                    if(imprime.codigo_ibge != 0){
                        imprimeInformacoes(imprime);
                    }
                    else{
                        printf("Cidade nao encontrada!\n");
                    }
                    break;
                }
                else{
                    printf("Cidade nao encontrada!\n");
                    break;
                }
            case 2:
                printf("Digite o codigo IBGE: ");
                scanf("%d", &codigo_ibge);
                printf("Digite a quantidade de vizinhos: ");
                scanf("%d", &n);
                tcidade resultado1 = buscaIBGE(hash_cod, codigo_ibge);
                if(n > 0 && resultado1.codigo_ibge != 0){
                    buscaVizinhos(arvore, resultado1, n);
                }
                else{
                    printf("Favor informar um valor vádido!\n");
                }
                break;
            case 3:
                printf("Digite o nome da cidade: ");
                char nome[MAX];
                scanf(" %[^\n]", nome);
                tcidade resultado2 = buscaNome(hash_nome, nome);
                if(resultado2.codigo_ibge != 0){
                    printf("Digite a quantidade de vizinhos: ");
                    scanf("%d", &n);
                    buscaVizinhos(arvore, resultado2, n);
                }
                else{
                    printf("Cidade nao encontrada!\n");
                }
                break;
            case 4:
                liberaArvore(arvore->raiz);
                free(arvore);
                liberaHash(hash_cod);
                liberaHash(hash_nome);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

int main(){
    thash *hash_cod = criarHash(TAM);
    thash *hash_nome = criarHash(TAM);
    tarvore *arvore = (tarvore*)malloc(sizeof(tarvore));
    criaArvore(arvore);
    
    FILE* arquivo = fopen("../dados/municipios.json", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }

    lerArquivo(arquivo, hash_cod, hash_nome, arvore);

    interface(hash_cod, hash_nome, arvore);

    fclose(arquivo);
    return EXIT_SUCCESS;
}