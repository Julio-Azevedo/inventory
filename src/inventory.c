#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include "../modules/util.h"
#include "../modules/sobre.h"
#include "../modules/estoque.h"
#include "../modules/clientes.h"
#include "../modules/fornecedores.h"

// declaração das funções
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
    op = controle_menu();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}
