#include <stdio.h>
// cliente.c
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "cliente.h"
#include "../common/menus.h"

void moduloCliente()
{
    char opcao;
    Cliente *rel = NULL;

    do
    {
        mostrarMenuCliente();
        opcao = pegarMenuEscolha();
        switch (opcao)
        {
        case '1':
            cadastrarCliente();
            break;
        case '2':
            pesquisarCliente();
            break;
        case '3':
            editarCliente(rel);
            break;
        case '4':
            excluirClientePorCPF(rel);
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

// cadastrando cliente
void cadastrarCliente()
{
    // aloca memoria para a struct
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    // exibindo o menu de cadastro de fornecedores
    mostrarMenuCadastroFornecedor();

    // solicitando o cpf do cliente
    do
    {
        printf("Informe o CPF do cliente: ");
        scanf(" %[^\n]", novoCliente->cpf);
        limparBuffer();
    } while (!validarCpf(novoCliente->cpf) || ehCpfRegistrado(novoCliente->cpf));

    // solicitando o email do cliente
    do
    {
        printf("Informe o EMAIL do cliente: ");
        scanf(" %[^\n]", novoCliente->email);
        limparBuffer();
    } while (!validarEmail(novoCliente->email) || ehEmailClienteRegistrado(novoCliente->email));

    // solicitando o email do telefone
    do
    {
        printf("Informe o TELEFONE do cliente: ");
        scanf(" %[^\n]", novoCliente->telefone);
        limparBuffer();
    } while (!validarTelefone(novoCliente->telefone));

    // solicitando o email do nome
    do
    {
        printf("Informe o NOME do cliente: ");
        scanf(" %[^\n]", novoCliente->nome);
        limparBuffer();
    } while (!validarNome(novoCliente->nome));

    // adicionando um novo id ao cliente
    novoCliente->id = pegarProximoIdCliente();
    // informando que o status do cliente esta ativo
    novoCliente->status = '1';
    // inicializando o ponteiro prox como NULL
    novoCliente->prox = NULL;

    // abrindo o arquivo de cliente
    FILE *fp = fopen("data/clientes.dat", "ab");
    // fazendo o tratamento de erro
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

    // escrevendo novo produto no arquivo de clientes
    fwrite(novoCliente, sizeof(Cliente), 1, fp);
    // fechando o arquivo de clientes
    fclose(fp);

    printf("\n");
    printf(green "Cliente cadastrado com sucesso!\n" reset);
    printf("\t<ENTER> para continuar\n");
    getchar();
    free(novoCliente);
}

// pesquisando cliente
void pesquisarCliente()
{
    Cliente cliente;
    int encontrado = 0;
    char cpfPesquisa[50];
    mostrarMenuPesquisaCliente();

    do
    {
        printf("Informe o CPF do cliente (somente numeros): ");
        scanf(" %[^\n]", cpfPesquisa);
        limparBuffer();
    } while (!validarCpf(cpfPesquisa));

    FILE *fp = fopen("data/clientes.dat", "rb");

    if (fp == NULL)
    {
        fp = fopen("data/clientes.dat", "wb");
        tratamentoVerificaNulo(fp, "Erro na criação do arquivo de clientes\n");

        fclose(fp);
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, fp) == 1)
    {
        if (strcmp(cliente.cpf, cpfPesquisa) == 0 && cliente.status == '1')
        {
            mostrarCliente(&cliente);
            printf("\n");
            printf("\t<ENTER> para continuar\n");
            getchar();
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado)
    {
        printf("Cliente com CPF %s não existe ou esta inativo.\n", cpfPesquisa);
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
    }
}

// editar cliente
void editarCliente(Cliente *lista)
{
    mostrarMenuEditarCliente();
    char cpfBusca[50];
    printf("Informe o CPF do cliente que deseja editar: ");
    scanf(" %[^\n]", cpfBusca);
    limparBuffer();

    FILE *fp = fopen("data/clientes.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Cliente clienteAtual;

    while (fread(&clienteAtual, sizeof(Cliente), 1, fp) == 1)
    {
        if (strcmp(clienteAtual.cpf, cpfBusca) == 0)
        {
            mostrarCliente(&clienteAtual);
            printf("\nDeseja editar este fornecedor? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                limparTela();
                mostrarMenuEditarCliente();
                printf("* 1. Editar CPF                                                            *\n");
                printf("* 2. Editar Email                                                           *\n");
                printf("* 3. Editar Telefone                                                        *\n");
                printf("* 4. Editar Nome                                                            *\n");
                printf("* 0. Cancelar                                                               *\n");
                printf("*****************************************************************************\n");

                int opcao;
                printf("Informe a opcao que deseja editar: ");
                scanf("%d", &opcao);
                limparBuffer();

                switch (opcao)
                {
                case 1:
                    do
                    {
                        printf("Informe o novo CPF do cliente: ");
                        scanf(" %[^\n]", clienteAtual.cpf);
                        limparBuffer();
                    } while (!validarCpf(clienteAtual.cpf) || ehCpfRegistrado(clienteAtual.cpf));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 2:
                    do
                    {
                        printf("Informe o novo EMAIL do cliente: ");
                        scanf(" %[^\n]", clienteAtual.email);
                        limparBuffer();
                    } while (!validarEmail(clienteAtual.email) || ehEmailClienteRegistrado(clienteAtual.email));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 3:
                    do
                    {
                        printf("Informe o novo TELEFONE do cliente: ");
                        scanf(" %[^\n]", clienteAtual.telefone);
                        limparBuffer();
                    } while (!validarTelefone(clienteAtual.telefone));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 4:
                    do
                    {
                        printf("Informe o novo NOME do cliente: ");
                        scanf(" %[^\n]", clienteAtual.nome);
                        limparBuffer();
                    } while (!validarNome(clienteAtual.nome));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 0:
                    printf("Edição cancelada.\n");
                    printf(red "Edição cancelada.\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                default:
                    printf("Opção inválida. tente novamente!\n");
                    break;
                }

                // Volta para o início do registro no arquivo
                fseek(fp, -sizeof(Cliente), SEEK_CUR);
                // Escreve o registro modificado
                fwrite(&clienteAtual, sizeof(Cliente), 1, fp);
                printf("Fornecedor editado com sucesso!\n");
            }
            else
            {
                printf(red "Edição cancelada.\n" reset);
                printf("\t<ENTER> para continuar\n");
                getchar();
            }

            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Fornecedor não encontrado.\n");
}

// excluir cliente
void excluirCliente(Cliente *lista, const char *cpf)
{
    FILE *fp = fopen("data/clientes.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Cliente clienteAtual;

    while (fread(&clienteAtual, sizeof(Cliente), 1, fp) == 1)
    {
        if (strcmp(clienteAtual.cpf, cpf) == 0)
        {
            mostrarCliente(&clienteAtual);
            printf("\nDeseja excluir este fornecedor? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                // mudando o status para inativo
                clienteAtual.status = '0';

                // voltando para o início do arquivo
                fseek(fp, -sizeof(Cliente), SEEK_CUR);
                // escreve a modificacao no arquivo
                fwrite(&clienteAtual, sizeof(Cliente), 1, fp);
                printf(green "Cliente excluido com sucesso!\n" reset);
                printf("\t<ENTER> para continuar\n");
                getchar();
            }
            else
            {
                printf(red "Exclusao cancelada, voltando ao menu!\n" reset);
                printf("\t<ENTER> para continuar\n");
                getchar();
            }

            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Cliente não encontrado.\n");
    printf(green "Produto excluido com sucesso!\n" reset);
    printf("\t<ENTER> para continuar\n");
    getchar();
}

// verificando se o email ja esta registrado
int ehEmailClienteRegistrado(const char *email)
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    if (fp == NULL)
    {
        fp = fopen("data/clientes.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura ou criação do arquivo");
        fclose(fp);
        return 0;
    }

    Cliente clienteAtual;
    while (fread(&clienteAtual, sizeof(Cliente), 1, fp) == 1)
    {
        if (strcmp(clienteAtual.email, email) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// verificando se o cpf ja esta registrado
int ehCpfRegistrado(const char *cpf)
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    if (fp == NULL)
    {
        fp = fopen("data/clientes.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura ou criação do arquivo");
        fclose(fp);
        return 0;
    }

    Cliente clienteAtual;
    while (fread(&clienteAtual, sizeof(Cliente), 1, fp) == 1)
    {
        if (strcmp(clienteAtual.cpf, cpf) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// obtendo o proximo valor de id
int pegarProximoIdCliente()
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    if (fp == NULL)
    {
        return 1;
    }

    Cliente ultimoClienteLista;
    fseek(fp, -sizeof(Cliente), SEEK_END);

    // Verificando se a leitura foi bem-sucedida
    if (fread(&ultimoClienteLista, sizeof(Cliente), 1, fp) != 1)
    {
        fclose(fp);
        printf("Erro na leitura dos dados do cliente.\n");
        return 1;
    }

    // Verificar se o campo id é válido
    if (ultimoClienteLista.id < 0)
    {
        fclose(fp);
        printf("ID inválido encontrado nos dados do cliente.\n");
        return 1;
    }

    fclose(fp);

    return ultimoClienteLista.id + 1;
}

// exibindo o cliente
void mostrarCliente(const Cliente *cliente)
{
    printf("\n");
    printf("********* Dados do Fornecedor *********\n");
    printf("ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);
    printf("CPF: %s\n", cliente->cpf);
    printf("Email: %s\n", cliente->email);
    printf("Telefone: %s\n", cliente->telefone);
    printf("Status: %s\n", (cliente->status == '1') ? green "Ativo" reset : red "Inativo" reset);
    printf("***************************************\n");
}

// exclusao logica do cliente por cpf
void excluirClientePorCPF(Cliente *lista)
{
    mostrarMenuExcluirCliente();
    char cfpBusca[50];
    printf("Informe o CPF do cliente que deseja excluir: ");
    scanf(" %[^\n]", cfpBusca);
    limparBuffer();

    if (!ehCpfRegistrado(cfpBusca))
    {
        printf("CNPJ não encontrado.\n");
        return;
    }

    excluirCliente(lista, cfpBusca);
}