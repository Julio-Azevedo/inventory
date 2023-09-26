#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep
#include "produtos.h"

// chamada das funções
char tela_produtos(void);
void tela_cadastrar_produtos(void);
//

void modulo_produtos(void) {
    char opcao;

    do {
        opcao = tela_produtos();
        switch (opcao)
        {
        case '1':
            tela_cadastrar_produtos();
            break;
        
        default:
            break;
        }
    } while (opcao != '0'); 
}

char tela_produtos(void) {
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                    = = = = = Produtos = = = = =                            *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Cadastrar um novo produto                                               *\n");
    printf("* 2. Listar produtos                                                         *\n");
    printf("* 3. Editar produtos                                                         *\n");
    printf("* 4. Excluir produtos                                                        *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

void tela_cadastrar_produtos(void) {
    Produtos produto;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Cadastrar Produto = = = = =                      *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("Nome do produto: ");
    scanf(" %[^\n]", produto.nome);
    printf("Código do produto: ");
    scanf("%s", produto.codigo);
    printf("Fornecedor do produto: ");
    scanf(" %[^\n]", produto.fornecedor);
    printf("Custo do produto(valor de compra): ");
    scanf("%d", produto.valor_custo);
    printf("Venda do produto(valor de venda): ");
    scanf("%d", produto.valor_venda);
    printf("Quantidade de estoque: ");
    scanf("%d", produto.qtd_estoque);
}
