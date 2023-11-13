#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "estoque.h"

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
    op = controle_menu();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}