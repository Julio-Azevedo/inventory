#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep

// chamada das funções
char tela_fornecedores(void);
//

void modulo_fornecedores(void) {
    char opcao;

    do {
        opcao = tela_fornecedores();
        switch (opcao)
        {
        case '1':
            /* code */
            break;
        
        default:
            break;
        }
    } while (opcao != 0);
}

char tela_fornecedores(void) {
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                    = = = = = Fornecedores = = = = =                        *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Cadastrar um novo fornecedor                                            *\n");
    printf("* 2. Listar fornecedores                                                     *\n");
    printf("* 3. Editar fornecedores                                                     *\n");
    printf("* 4. Excluir fornecedores                                                    *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

typedef struct {
    char nome[50];
    int CNPJ[20];
    int telefone[12];
    char estado[2];
    char cidade[40];
    char endereco[120];
    char email[50];
} Fornecedores;


void tela_cadastra_fornecedor(void) {
    Fornecedores fornecedor;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Cadastrar Fornecedor = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("Nome do fornecedor: ");
    scanf("%s", fornecedor.nome);
}
