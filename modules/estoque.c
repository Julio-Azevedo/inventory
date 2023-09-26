#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep
#include "estoque.h"
#include "clientes.h"

// chamadas de funções
char tela_estoque(void);
char tela_clientes(void);
void modulo_clientes(void);
void modulo_fornecedores(void);
void modulo_produtos(void);
//

void modulo_estoque(void) {
    char opcao;
    
    do {
        opcao = tela_estoque();
        switch (opcao)
        {
        case '1':
            modulo_clientes();
            break;
        case '2':
            modulo_fornecedores();
            break;
        case '3':
            modulo_produtos();
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

char tela_estoque(void) {
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Sistema de Estoque = = = = =                     *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Clientes                                                                *\n");
    printf("* 2. Fornecedores                                                            *\n");
    printf("* 3. Produtos                                                                *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}