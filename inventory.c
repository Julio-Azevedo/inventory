// Arquivo principal do programa
#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep
#include "modules/sobre.h" // para as funções de informações do projeto
#include "modules/estoque.h"
#include "modules/clientes.h"
#include "modules/fornecedores.h"

// chamada das funções
char tela_iniciar(void);
void tela_sobre(void);
void modulo_estoque(void);
//

int main(void) {
    char opcao;

    do {
        opcao = tela_iniciar();
        switch (opcao)
        {
        case '1':
            modulo_estoque();    
            break;
        case '2':
            tela_sobre();
            break;
        default:
            break;
        }
    } while (opcao != '0');
        
    return 0;
}

void limpar_tela() {
    system("clear||cls");
}

char tela_iniciar(void) {
    char op;

    limpar_tela();
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Sistema de Estoque = = = = =                     *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Administrar estoques                                                    *\n");
    printf("* 2. Sobre o projeto                                                         *\n");
    printf("* 0. Sair                                                                    *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}
