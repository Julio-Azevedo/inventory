#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "fornecedor.h"
#include "../common/menus.h"

void moduloFornecedor()
{
    char opcao;
    Fornecedor *rel = NULL;

    do
    {
        mostrarMenuFornecedor();
        opcao = pegarMenuEscolha();
        switch (opcao)
        {
        case '1':
            rel = cadastrarFornecedor(rel);
            break;
        case '2':
            pesquisarFornecedor();
            break;
        case '3':
            editarFornecedor(rel);
            break;
        case '4':
            excluirFornecedorPorCNPJ(rel);
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

// cadastro de fornecedor
Fornecedor *cadastrarFornecedor(Fornecedor *lista)
{
    Fornecedor *novoFornecedor = (Fornecedor *)malloc(sizeof(Fornecedor));

    mostrarMenuCadastroFornecedor();

    do
    {
        printf("Informe o CNPJ do fornecedor: ");
        scanf(" %[^\n]", novoFornecedor->cnpj);
        limparBuffer();
    } while (!validarCnpj(novoFornecedor->cnpj) || ehCnpjRegistrado(novoFornecedor->cnpj));
    do
    {
        printf("Informe o EMAIL do fornecedor: ");
        scanf(" %[^\n]", novoFornecedor->email);
        limparBuffer();
    } while (!validarEmail(novoFornecedor->email) || ehEmailRegistrado(novoFornecedor->email));

    do
    {
        printf("Informe o TELEFONE do fornecedor: ");
        scanf(" %[^\n]", novoFornecedor->telefone);
        limparBuffer();
    } while (!validarTelefone(novoFornecedor->telefone));

    do
    {
        printf("Informe o NOME do fornecedor: ");
        scanf(" %[^\n]", novoFornecedor->nome);
        limparBuffer();
    } while (!validarNome(novoFornecedor->nome));

    novoFornecedor->id = pegarProximoId();
    novoFornecedor->status = '1';
    novoFornecedor->prox = NULL;

    if (lista == NULL)
    {
        FILE *fp = fopen("data/fornecedores.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

        fwrite(novoFornecedor, sizeof(Fornecedor), 1, fp);
        fclose(fp);

        printf("\n");
        printf(green "Fornecedor cadastrado com sucesso!\n" reset);
        printf("\t<ENTER> para continuar\n");
        getchar();
        return novoFornecedor;
    }

    Fornecedor *atual = lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }

    atual->prox = novoFornecedor;

    FILE *fp = fopen("data/fornecedores.dat", "ab");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

    fwrite(novoFornecedor, sizeof(Fornecedor), 1, fp);
    fclose(fp);

    printf("\n");
    printf(green "Fornecedor cadastrado com sucesso!\n" reset);
    printf("\t<ENTER> para continuar\n");
    getchar();
    return lista;
}

// pesquisa de fornecedor
void pesquisarFornecedor()
{
    Fornecedor fornecedor;
    int encontrado = 0;
    char cnpjPesquisa[50];
    mostrarMenuPesquisaFornecedor();

    do
    {
        printf("Informe o CNPJ do fornecedor (somente numeros): ");
        scanf(" %[^\n]", cnpjPesquisa);
        limparBuffer();
    } while (!validarCnpj(cnpjPesquisa));

    FILE *fp = fopen("data/fornecedores.dat", "rb");

    if (fp == NULL)
    {
        fp = fopen("data/fornecedores.dat", "wb");
        tratamentoVerificaNulo(fp, "Erro na criação do arquivo de fornecedores\n");

        fclose(fp);
        return;
    }

    while (fread(&fornecedor, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedor.cnpj, cnpjPesquisa) == 0 && fornecedor.status == '1')
        {
            mostrarFornecedor(&fornecedor);
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
        printf("Fornecedor com CNPJ %s não existe ou esta inativo.\n", cnpjPesquisa);
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
    }
}

// editar fornecedor
void editarFornecedor(Fornecedor *lista)
{
    mostrarMenuEditarFornecedor();
    char cnpjBusca[50];
    printf("Informe o CNPJ do fornecedor que deseja editar: ");
    scanf(" %[^\n]", cnpjBusca);
    limparBuffer();

    FILE *fp = fopen("data/fornecedores.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Fornecedor fornecedorAtual;

    while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedorAtual.cnpj, cnpjBusca) == 0)
        {
            mostrarFornecedor(&fornecedorAtual);
            printf("\nDeseja editar este fornecedor? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                limparTela();
                mostrarMenuEditarFornecedor();
                printf("* 1. Editar CNPJ                                                            *\n");
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
                        printf("Informe o novo CNPJ do fornecedor: ");
                        scanf(" %[^\n]", fornecedorAtual.cnpj);
                        limparBuffer();
                    } while (!validarCnpj(fornecedorAtual.cnpj) || ehCnpjRegistrado(fornecedorAtual.cnpj));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 2:
                    do
                    {
                        printf("Informe o novo EMAIL do fornecedor: ");
                        scanf(" %[^\n]", fornecedorAtual.email);
                        limparBuffer();
                    } while (!validarEmail(fornecedorAtual.email) || ehCnpjRegistrado(fornecedorAtual.email));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 3:
                    do
                    {
                        printf("Informe o novo TELEFONE do fornecedor: ");
                        scanf(" %[^\n]", fornecedorAtual.telefone);
                        limparBuffer();
                    } while (!validarTelefone(fornecedorAtual.telefone));
                    printf(green "Fornecedor editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 4:
                    do
                    {
                        printf("Informe o novo NOME do fornecedor: ");
                        scanf(" %[^\n]", fornecedorAtual.nome);
                        limparBuffer();
                    } while (!validarNome(fornecedorAtual.nome));
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
                fseek(fp, -sizeof(Fornecedor), SEEK_CUR);
                // Escreve o registro modificado
                fwrite(&fornecedorAtual, sizeof(Fornecedor), 1, fp);
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

// excluir fornecedor
void excluirFornecedor(Fornecedor *lista, const char *cnpj)
{
    FILE *fp = fopen("data/fornecedores.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Fornecedor fornecedorAtual;

    while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedorAtual.cnpj, cnpj) == 0)
        {
            mostrarFornecedor(&fornecedorAtual);
            printf("\nDeseja excluir este fornecedor? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                // mudando o status para inativo
                fornecedorAtual.status = '0';

                // voltando para o início do arquivo
                fseek(fp, -sizeof(Fornecedor), SEEK_CUR);
                // escreve a modificacao no arquivo
                fwrite(&fornecedorAtual, sizeof(Fornecedor), 1, fp);
                printf(green "Fornecedor excluido com sucesso!\n" reset);
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
    printf("Fornecedor não encontrado.\n");
}

// obtendo o proximo valor de id
int pegarProximoId()
{
    FILE *fp = fopen("fornecedores.dat", "rb");
    if (fp == NULL)
    {
        return 1;
    }

    Fornecedor ultimoFornecedorLista;
    fseek(fp, -sizeof(Fornecedor), SEEK_END);
    fread(&ultimoFornecedorLista, sizeof(Fornecedor), 1, fp);
    fclose(fp);

    return ultimoFornecedorLista.id + 1;
}

// exibindo o fornecedor
void mostrarFornecedor(const Fornecedor *fornecedor)
{
    printf("\n");
    printf("********* Dados do Fornecedor *********\n");
    printf("ID: %d\n", fornecedor->id);
    printf("Nome: %s\n", fornecedor->nome);
    printf("CNPJ: %s\n", fornecedor->cnpj);
    printf("Email: %s\n", fornecedor->email);
    printf("Telefone: %s\n", fornecedor->telefone);
    printf("Status: %s\n", (fornecedor->status == '1') ? green "Ativo" reset : red "Inativo" reset);
    printf("***************************************\n");
}

// verificando se o email ja esta registrado
int ehEmailRegistrado(const char *email)
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    if (fp == NULL)
    {
        fp = fopen("data/fornecedores.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura ou criação do arquivo");
        fclose(fp);
        return 0;
    }

    Fornecedor fornecedorAtual;
    while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedorAtual.email, email) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// verificando se o cnpj ja esta registrado
int ehCnpjRegistrado(const char *cnpj)
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    if (fp == NULL)
    {
        fp = fopen("data/fornecedores.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura ou criação do arquivo");
        fclose(fp);
        return 0;
    }

    Fornecedor fornecedorAtual;
    while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedorAtual.cnpj, cnpj) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// verificando se o fornecedor ja esta cadastrado
int fornecedorJaCadastrado(const char *cnpj, const char *email)
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    if (fp == NULL)
    {
        fp = fopen("data/fornecedores.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura ou criação do arquivo");
        fclose(fp);
        return 0;
    }

    Fornecedor fornecedorAtual;
    while (fread(&fornecedorAtual, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (strcmp(fornecedorAtual.email, email) == 0)
        {
            fclose(fp);
            printf("E-mail já cadastrado. Tente outro.\n");
            return 1;
        }

        if (strcmp(fornecedorAtual.cnpj, cnpj) == 0)
        {
            fclose(fp);
            printf("CNPJ já cadastrado. Tente outro.\n");
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// exclusao logica do fornecedor por cnpj
void excluirFornecedorPorCNPJ(Fornecedor *lista)
{
    mostrarMenuExcluirFornecedor();
    char cnpjBusca[50];
    printf("Informe o CNPJ do fornecedor que deseja excluir: ");
    scanf(" %[^\n]", cnpjBusca);
    limparBuffer();

    if (!ehCnpjRegistrado(cnpjBusca))
    {
        printf("CNPJ não encontrado.\n");
        return;
    }

    excluirFornecedor(lista, cnpjBusca);
}