#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <unistd.h> // para a função sleep
#include "clientes.h"

// chamada de funções
char tela_clientes(void);
void tela_cadastra_cliente(void);
void tela_lista_cliente(void);
//

void modulo_clientes(void) {
    char opcao;

    do {
        opcao = tela_clientes();
        switch (opcao)
        {
        case '1':
            tela_cadastra_cliente();
            break;
        case '2':
            tela_lista_cliente();
            break;
        default:
            break;
        }
    } while (opcao != '0');  
}

char tela_clientes(void) {
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                      = = = = = Clientes = = = = =                          *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Cadastrar um novo cliente                                               *\n");
    printf("* 2. Listar clientes                                                         *\n");
    printf("* 3. Editar clientes                                                         *\n");
    printf("* 4. Excluir clientes                                                        *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

void tela_cadastra_cliente(void) {
    Clientes cliente;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Cadastrar Cliente = = = = =                    *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("Nome do cliente: ");
    scanf(" %[^\n]", cliente.nome);
    printf("CPF do cliente: ");
    scanf(" %[^\n]", cliente.cpf);
    printf("Cidade: ");
    scanf(" %[^\n]", cliente.cidade);
    printf("Unidade Federativa(Ex: RN, SP, RJ): ");
    scanf(" %[^\n]", cliente.estado);
    printf("Endereço: ");
    scanf(" %[^\n]", cliente.endereco);
    printf("Telefone: ");
    scanf("%d" , cliente.telefone);
}

void tela_lista_cliente(void) {
    Clientes cliente;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Lista de Clientes = = = = =                    *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    
}
