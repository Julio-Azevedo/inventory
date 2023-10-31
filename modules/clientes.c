#include <stdio.h>
#include <stdlib.h> // para a função system 
#include <string.h>
#include <unistd.h> // para a função sleep
#include "clientes.h"
#include "util.h"

// chamada de funções
char tela_clientes(void);
Clientes* tela_cadastra_cliente(void);
void tela_lista_cliente(void);
void limpa_buffer(void);
int valida_nome(const char *nome);
int valida_cpf(char *cpf);
int valida_telefone(char* telefone);
//

void modulo_clientes(void) {
    char opcao;
    Clientes* rel;

    do {
        opcao = tela_clientes();
        switch (opcao)
        {
        case '1':
            rel = tela_cadastra_cliente();
            grava_cliente(rel);
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

Clientes* tela_cadastra_cliente(void) {
    Clientes *cliente = (Clientes*)malloc(sizeof(Clientes));
    if (cliente == NULL) {
        perror("Erro na alocação de memória");
        return NULL;
    }
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Cadastrar Cliente = = = = =                    *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    do
    {
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", cliente -> nome);
        limpa_buffer();
    } while (!valida_nome(cliente -> nome));

    do
    {
        printf("Digite o CPF do cliente: ");
        scanf(" %[^\n]", cliente -> cpf);
        limpa_buffer();
    } while (!valida_cpf(cliente -> cpf));    

    do
    {
        printf("Digite a cidade do cliente: ");
        scanf(" %[^\n]", cliente -> cidade);
        limpa_buffer();
    } while (!valida_nome(cliente -> nome));

    do
    {
        printf("Digite a Unidade Federativa do cliente(Ex: RN, SP, RJ): ");
        scanf(" %[^\n]", cliente -> estado);
        limpa_buffer();
    } while (!valida_nome(cliente -> nome));

    do
    {
        printf("Digite o endereco do cliente: ");
        scanf(" %[^\n]", cliente -> endereco);
        limpa_buffer();
    } while (!valida_nome(cliente -> nome));

    do
    {
        printf("Digite o telefone do cliente: ");
        scanf(" %[^\n]", cliente -> telefone);
        limpa_buffer();
    } while (!valida_telefone(cliente -> telefone));

    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
    return cliente;
}

void grava_cliente(Clientes* cliente) {
    FILE *fp = fopen("clientes.dat", "ab");
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        return;
    }
    fwrite(cliente, sizeof(Clientes), 1, fp);
    fclose(fp);
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

