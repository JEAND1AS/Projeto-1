#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_PALAVRA 50
#define MAXIMO_ENTRADAS 100

typedef struct {
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    int contador;
} EntradaPalavra;

int buscarPalavra(EntradaPalavra entradas[], int num_entradas, char palavra[]) {
    for (int i = 0; i < num_entradas; i++) {
        if (strcmp(entradas[i].palavra, palavra) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE *arquivo;
    EntradaPalavra entradas[MAXIMO_ENTRADAS];
    int num_entradas = 0;
    int opcao;

    while(1) {
        printf("\nESCOLHA UMA DAS 3 OPCOES\n");
        printf("DIGITE 1 - Criar dicionário\n");
        printf("DIGITE 2 - Listar dicionários\n");
        printf("DIGITE 3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome_arquivo[50];
                printf("Digite o nome do DICIONARIO: ");
                scanf("%s", nome_arquivo);
                arquivo = fopen(nome_arquivo, "w");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o DICIONARIO!\n");
                    break;
                }

                num_entradas = 0;
                char palavra[TAMANHO_MAXIMO_PALAVRA];
                while (1) {
                    printf("Digite uma palavra (ou 'sair' para encerrar): ");
                    scanf("%s", palavra);
                    if (strcmp(palavra, "sair") == 0) {
                        break;
                    }

                    int indice = buscarPalavra(entradas, num_entradas, palavra);
                    if (indice != -1) {
                        entradas[indice].contador++;
                    } else {
                        strcpy(entradas[num_entradas].palavra, palavra);
                        entradas[num_entradas].contador = 1;
                        num_entradas++;
                    }
                }

                for (int i = 0; i < num_entradas; i++) {
                    fprintf(arquivo, "%s: %d\n", entradas[i].palavra, entradas[i].contador);
                }
                fclose(arquivo);
                printf("Dicionario criado com sucesso e salvo em '%s'\n", nome_arquivo);
                break;
            }
            case 2: {
                char nome_arquivo_listagem[50];
                printf("Digite o nome do dicionario para consulta: ");
                scanf("%s", nome_arquivo_listagem);
                arquivo = fopen(nome_arquivo_listagem, "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o dicionario!\n");
                    break;
                }

                char linha[100];
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    printf("%s", linha);
                }
                fclose(arquivo);

                break;
            }
            case 3:
                printf("Encerrando o programa.\n");
                return 0;

            default:
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
    }
    return 0;
}
