#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep
#include "fornecedores.h"

// chamada das funções
char tela_fornecedores(void);
void tela_cadastra_fornecedor(void);
//

void modulo_fornecedores(void) {
    char opcao;

    do {
        opcao = tela_fornecedores();
        switch (opcao)
        {
        case '1':
            tela_cadastra_fornecedor();
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

void tela_cadastra_fornecedor(void) {
    Fornecedores fornecedor;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Cadastrar Fornecedor = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("Nome do fornecedor: ");
    scanf(" %[^\n]", fornecedor.nome);
    printf("CNPJ do fornecedor: ");
    scanf("%d", fornecedor.CNPJ);
    printf("Telefone do fornecedor: ");
    scanf("%d", fornecedor.telefone);
    printf("Unidade Federativa do fornecedor(Ex: RN, SP, RJ): ");
    scanf("%s", fornecedor.estado);
    printf("Municipio do fornecedor: ");
    scanf(" %[^\n]", fornecedor.cidade);
    printf("Endereço do fornecedor: ");
    scanf(" %[^\n]", fornecedor.endereco);
    printf("Email para contato do fornecedor: ");
    scanf(" %[^\n]", fornecedor.email);
}

void tela_listar_fornecedor(void) {
    Fornecedores fornecedor;

    
}
