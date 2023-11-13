#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"
#include "clientes.h"

void modulo_clientes(void)
{
    char opcao;
    Clientes *rel;

    do
    {
        opcao = tela_clientes();
        switch (opcao)
        {
        case '1':
            rel = tela_cadastra_cliente(0);
            grava_cliente(rel);
            break;
        case '2':
            tela_pesquisa_cliente();
            break;
        case '3':
            tela_edita_cliente();
            break;
        case '4':
            tela_excluir_cliente();
            break;
        case '5':
            tela_lista_cliente();
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

// funções de tela_
char tela_clientes(void)
{
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                      = = = = = Clientes = = = = =                          *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Cadastrar um novo cliente                                               *\n");
    printf("* 2. Pesquisar clientes                                                      *\n");
    printf("* 3. Editar clientes                                                         *\n");
    printf("* 4. Excluir clientes                                                        *\n");
    printf("* 5. Listar clientes                                                         *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

// função para cadastrar um novo cliente - code 1
Clientes *tela_cadastra_cliente(int editando)
{
    int cpf_exite = 0;
    int cpf_valido = 0;
    Clientes *cliente = (Clientes *)malloc(sizeof(Clientes));
    if (cliente == NULL)
    {
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
        scanf(" %[^\n]", cliente->nome);
        limpa_buffer();
    } while (!valida_nome(cliente->nome));

    do
    {
        printf("Digite o CPF do cliente: ");
        scanf(" %[^\n]", cliente->cpf);
        limpa_buffer();

        cpf_exite = verifica_cpf_cliente(cliente->cpf);

        if (!editando)
        {
            cpf_exite = verifica_cpf_cliente(cliente->cpf);
            if (cpf_exite)
            {
                printf("\n");
                printf("<<< CPF de cliente já cadastrado >>>\n");
                printf("\n");
                continue;
            }
        }

        if (valida_cpf(cliente->cpf))
        {
            cpf_valido = 1;
        }
        else
        {
            printf("\n");
            printf("<<< CPF inválido, tente novamente >>>\n");
            printf("\n");
        }

    } while (!cpf_valido || (cpf_exite && !editando));

    do
    {
        printf("Digite a cidade do cliente: ");
        scanf(" %[^\n]", cliente->cidade);
        limpa_buffer();
    } while (!valida_nome(cliente->nome));

    do
    {
        printf("Digite a Unidade Federativa do cliente(Ex: RN, SP, RJ): ");
        scanf(" %[^\n]", cliente->estado);
        limpa_buffer();
    } while (!valida_nome(cliente->nome));

    do
    {
        printf("Digite o endereco do cliente: ");
        scanf(" %[^\n]", cliente->endereco);
        limpa_buffer();
    } while (!valida_nome(cliente->nome));

    do
    {
        printf("Digite o telefone do cliente: ");
        scanf(" %[^\n]", cliente->telefone);
        limpa_buffer();
    } while (!valida_telefone(cliente->telefone));

    cliente->status = 1;

    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
    return cliente;
}

// função que permite pesquisar o cliente pelo CPF - code 2
Clientes *tela_pesquisa_cliente(void)
{
    char cpf_pesquisa[15];
    Clientes *cliente = (Clientes *)malloc(sizeof(Clientes));
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Pesquisar Clientes = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    do
    {
        printf("Informe o CPF do cliente: ");
        scanf(" %[^\n]", cpf_pesquisa);
        limpa_buffer();
    } while (!valida_cpf(cpf_pesquisa));

    FILE *fp = fopen("clientes.dat", "rb");
    if (fp == NULL)
    {
        printf("O programa ainda nao possui clientes cadastrados\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        free(cliente);
        return NULL;
    }

    int possui_cliente = 0;
    while (fread(cliente, sizeof(Clientes), 1, fp))
    {
        if ((cliente->status == 1) && (strcmp(cliente->cpf, cpf_pesquisa)) == 0)
        {
            exibe_cliente(cliente);
            limpa_buffer();
            possui_cliente = 1;
        }
    }

    if (!possui_cliente)
    {
        printf("\n");
        printf("<<< Nenhum cliente encontrado >>>\n");
        printf("\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        return NULL;
    }

    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
    return NULL;
}

// função que permite alterar os dados de um cliente - code 3
void tela_edita_cliente(void)
{
    Clientes *cliente;
    char *cpf = (char *)malloc(15 * sizeof(char));

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Editar Clientes = = = = =                      *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    do
    {
        printf("Informe o CPF do cliente que deseja editar: ");
        scanf(" %[^\n]", cpf);
        limpa_buffer();
    } while (!valida_cpf(cpf));

    cliente = busca_cpf_cliente(cpf);

    if (cliente == NULL)
    {
        printf("\n");
        printf("<<< Nenhum cliente encontrado >>>\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }
    else
    {
        char opt;
        int valida_opt = 0;

        exibe_cliente(cliente);

        while (!valida_opt)
        {
            printf("Deseja realmente editar este cliente? (S/N): ");
            scanf(" %c", &opt);
            limpa_buffer();

            if (opt == 'S' || opt == 's')
            {
                valida_opt = 1;
                cliente = tela_cadastra_cliente(1);
                regrava_cliente(cliente);
                free(cliente);
            }
            else if (opt == 'N' || opt == 'n')
            {
                valida_opt = 1;
                printf("<<< Edicao Cancelada >>>\n");
                printf("<<< Tecle <ENTER> para continuar >>>\n");
                getchar();  
                free(cliente);
                return;
            }
            else
            {
                printf("Resposta invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n");
            }
        }
    }

    free(cpf);
}

// função para excluir o cliente cadastrado no sistema - code 4
void tela_excluir_cliente(void)
{
    int possui_cliente = 0;
    long posicao;
    Clientes *cliente = (Clientes *)malloc(sizeof(Clientes));
    char cpf_pesquisa[15];

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Excluir Clientes = = = = =                     *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    do
    {
        printf("Informe o CPF do cliente que deseja excluir: ");
        scanf(" %[^\n]", cpf_pesquisa);
        limpa_buffer();
    } while (!valida_cpf(cpf_pesquisa));

    FILE *fp = fopen("clientes.dat", "r+b");
    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    while (fread(cliente, sizeof(Clientes), 1, fp))
    {
        if (strcmp(cliente->cpf, cpf_pesquisa) == 0 && cliente->status == 1)
        {
            possui_cliente = 1;
            posicao = ftell(fp) - sizeof(Clientes);
            break;
        }
    }

    if (!possui_cliente)
    {
        printf("\nNenhum cliente ativo encontrado com esse CPF.\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }
    else
    {
        char opt;
        int valida_opt = 0;

        exibe_cliente(cliente);

        while (!valida_opt)
        {
            printf("Deseja realmente excluir este cliente? (S/N): ");
            scanf(" %c", &opt);
            limpa_buffer();

            if (opt == 'S' || opt == 's')
            {
                valida_opt = 1;
                fseek(fp, posicao, SEEK_SET);
                cliente->status = 0;
                fwrite(&cliente, sizeof(Clientes), 1, fp);
                printf("\nCliente excluido com sucesso.\n");
            }
            else if (opt == 'N' || opt == 'n')
            {
                valida_opt = 1;
                printf("<<< Exclusao Cancelada >>>\n");
                printf("<<< Tecle <ENTER> para continuar >>>\n");
                getchar();  
                free(cliente);
                return;
            }
            else
            {
                printf("Resposta invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n");
            }
        }
    }

    fclose(fp);
    free(cliente);
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
}

// função para mostrar todos os clientes cadastrados no sistema - code 5
void tela_lista_cliente(void)
{
    int possui_cliente = 0;
    Clientes *cliente = (Clientes *)malloc(sizeof(Clientes));
    if (cliente == NULL)
    {
        perror("Erro na alocação de memória");
        return;
    }
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Lista de Clientes = = = = =                    *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    FILE *fp = fopen("clientes.dat", "rb");
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        free(cliente);
        return;
    }

    // função que irá ler os clientes que estão no arquivo
    while (fread(cliente, sizeof(Clientes), 1, fp))
    {
        if (cliente->status == 1)
        {
            exibe_cliente(cliente);
            possui_cliente = 1;
        }
    }

    // se não possuir nenhum cliente no arquivo
    if (!possui_cliente)
    {
        printf("\n");
        printf("<<< Nenhum cliente encontrado >>>\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }

    // liberando a memória alocada
    free(cliente);
    // fechando o arquivo
    fclose(fp);
    limpa_buffer();
    // esperando confirmação do usuário
    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
}

/////////////////////////////////////////////////////////////////////////////
// funções auxiliares
void grava_cliente(Clientes *cliente)
{
    FILE *fp = fopen("clientes.dat", "ab");
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        return;
    }
    fwrite(cliente, sizeof(Clientes), 1, fp);
    fclose(fp);
}

// estrutura que será exibida quando for verificado os clientes em lista
void exibe_cliente(Clientes *cliente)
{
    printf("********* Dados do Cliente *********\n");
    printf("Nome: %s\n", cliente->nome);
    printf("Cpf: %s\n", cliente->cpf);
    printf("Cidade: %s\n", cliente->cidade);
    printf("Estado: %s\n", cliente->estado);
    printf("Endereco: %s\n", cliente->endereco);
    printf("Telefone: %s\n", cliente->telefone);
    printf("Status: %s\n", cliente->status == 1 ? "\033[0;32mATIVO\033[0m\n" : "\033[0;31mINATIVO\033[0m\n");
    printf("************************************\n");
}

// estrutura que busca um cliente pelo cpf
Clientes *busca_cpf_cliente(char *cpf)
{
    // alocando a memória
    Clientes *cliente = (Clientes *)malloc(sizeof(Clientes));
    // abrindo o arquivo
    FILE *fp = fopen("clientes.dat", "rb");
    // caso tenho erro ao abrir o arquivo
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        return NULL;
    }
    // lendo os clintes que estão no arquivo
    while (fread(cliente, sizeof(Clientes), 1, fp))
    {
        if (strcmp(cliente->cpf, cpf) == 0 && cliente->status == 1)
        {
            // fechando o arquivo
            fclose(fp);
            // retorna o cliente que encontrou
            return cliente;
        }
    }

    // fechando o arquivo
    fclose(fp);
    // liberando a memória alocada
    free(cliente);
    return NULL;
}

// estrutura que substitui o cliente original pelo editado
void regrava_cliente(Clientes *cliente)
{
    Clientes cliente_lido;
    FILE *fp = fopen("clientes.dat", "r+b");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return;
    }

    int possui_cliente = 0;
    // Busca o cliente pelo CPF no arquivo
    while (fread(&cliente_lido, sizeof(Clientes), 1, fp) == 1)
    { // Verifica se um registro foi lido
        if (strcmp(cliente_lido.cpf, cliente->cpf) == 0)
        {
            possui_cliente = 1;
            // Move o ponteiro para trás do tamanho de um Cliente
            if (fseek(fp, -(off_t)sizeof(Clientes), SEEK_CUR) != 0)
            {
                perror("Erro ao posicionar o ponteiro do arquivo");
                break; // Se fseek falhar, saia do loop
            }
            fwrite(cliente, sizeof(Clientes), 1, fp);
            break;
        }
    }

    if (!possui_cliente)
    {
        printf("\nCliente não encontrado!\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }

    fclose(fp); // Fecha o arquivo após o uso
}