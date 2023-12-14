// produtos.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "produto.h"
#include "fornecedor.h"
#include "../common/menus.h"

void moduloProduto()
{
    char opcao;
    Produto *rel = NULL;
    do
    {
        mostrarMenuProdutos();
        opcao = pegarMenuEscolha();

        switch (opcao)
        {
        case '1':
            rel = cadastrarProduto(rel);
            break;
        case '2':
            pesquisarProdutos();
            break;
        case '3':
            editarProduto(rel);
            break;
        case '4':
            excluirProdutoPorCNPJ(rel);
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

// cadastro de produto
Produto *cadastrarProduto(Produto *lista)
{
    Produto *novoProduto = (Produto *)malloc(sizeof(Produto));
    mostrarMenuCadastroProduto();

    do
    {
        printf("Informe o CNPJ do fornecedor do produto: ");
        scanf(" %[^\n]", novoProduto->cnpj);
        limparBuffer();
    } while (!validarCnpj(novoProduto->cnpj) || !ehCnpjRegistrado(novoProduto->cnpj));

    do
    {
        printf("Informe a QUANTIDADE de unidades do produto: ");
        scanf(" %[^\n]", novoProduto->quantidade);
        limparBuffer();
    } while (!validarNumero(novoProduto->quantidade));

    do
    {
        printf("Informe o NOME do produto: ");
        scanf(" %[^\n]", novoProduto->nome);
        limparBuffer();
    } while (!validarNome(novoProduto->nome));

    do
    {
        printf("Informe o VALOR DE COMPRA do produto: ");
        scanf(" %[^\n]", novoProduto->valor_compra);
        limparBuffer();
    } while (!validarNumero(novoProduto->valor_compra));

    do
    {
        printf("Informe o VALOR DE VENDA do produto: ");
        scanf(" %[^\n]", novoProduto->valor_venda);
        limparBuffer();
    } while (!validarNumero(novoProduto->valor_venda));

    novoProduto->id = pegarProximoIdProduto();
    novoProduto->status = '1';
    novoProduto->prox = NULL;

    if (lista == NULL)
    {
        FILE *fp = fopen("data/produtos.dat", "ab");
        tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

        fwrite(novoProduto, sizeof(Produto), 1, fp);
        fclose(fp);

        printf("\n");
        printf(green "Produto cadastrado com sucesso!\n" reset);
        printf("\t<ENTER> para continuar\n");
        getchar();
        return novoProduto;
    }

    Produto *atual = lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }

    atual->prox = novoProduto;

    FILE *fp = fopen("data/produtos.dat", "ab");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

    fwrite(novoProduto, sizeof(Produto), 1, fp);
    fclose(fp);

    printf("\n");
    printf(green "Produto cadastrado com sucesso!\n" reset);
    printf("\t<ENTER> para continuar\n");
    getchar();
    return lista;
}

// pesquisa de produtos
void pesquisarProdutos()
{
    Produto produto;
    int encontrado = 0;
    char cnpjPesquisa[50];
    mostrarMenuPesquisaProduto();

    do
    {
        printf("Informe o CNPJ do fornecedor do produto (somente numeros): ");
        scanf(" %[^\n]", cnpjPesquisa);
        limparBuffer();
    } while (!validarCnpj(cnpjPesquisa));

    FILE *fp = fopen("data/produtos.dat", "rb");

    if (fp == NULL)
    {
        fp = fopen("data/produtos.dat", "wb");
        tratamentoVerificaNulo(fp, "Erro na criação do arquivo de produtos\n");

        fclose(fp);
        return;
    }

    while (fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        if (strcmp(produto.cnpj, cnpjPesquisa) == 0 && produto.status == '1')
        {
            mostrarProduto(&produto);
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
        printf("Produto com CNPJ %s não existe ou esta inativo.\n", cnpjPesquisa);
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
    }
}

// editar produto
void editarProduto(Produto *lista)
{
    mostrarMenuEditarProduto();
    char cnpjBusca[50];
    printf("Informe o CNPJ do fornecedor do produto que deseja editar: ");
    scanf(" %[^\n]", cnpjBusca);
    limparBuffer();

    FILE *fp = fopen("data/produtos.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto produtoAtual;

    while (fread(&produtoAtual, sizeof(Produto), 1, fp) == 1)
    {
        if (strcmp(produtoAtual.cnpj, cnpjBusca) == 0)
        {
            mostrarProduto(&produtoAtual);
            printf("\nDeseja editar este produto? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                limparTela();
                mostrarMenuEditarProduto();
                printf("* 1. Editar CNPJ                                                            *\n");
                printf("* 2. Editar Quantidade                                                      *\n");
                printf("* 3. Editar Nome                                                            *\n");
                printf("* 4. Editar Valor da Compra                                                 *\n");
                printf("* 5. Editar Valor da Venda                                                  *\n");
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
                        printf("Informe o novo CNPJ do fornecedor do produto: ");
                        scanf(" %[^\n]", produtoAtual.cnpj);
                        limparBuffer();
                    } while (!validarCnpj(produtoAtual.cnpj) || ehCnpjRegistrado(produtoAtual.cnpj));
                    printf(green "Produto editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 2:
                    do
                    {
                        printf("Informe a nova QUANTIDADE do produto: ");
                        scanf(" %[^\n]", produtoAtual.quantidade);
                        limparBuffer();
                    } while (!validarNumero(produtoAtual.quantidade));
                    printf(green "Produto editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 3:
                    do
                    {
                        printf("Informe o novo NOME do produto: ");
                        scanf(" %[^\n]", produtoAtual.nome);
                        limparBuffer();
                    } while (!validarNome(produtoAtual.nome));
                    printf(green "Produto editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 4:
                    do
                    {
                        printf("Informe o novo VALOR DE COMPRA do produto: ");
                        scanf(" %[^\n]", produtoAtual.valor_compra);
                        limparBuffer();
                    } while (!validarNumero(produtoAtual.valor_compra));
                    printf(green "Produto editado com sucesso!\n" reset);
                    printf("\t<ENTER> para continuar\n");
                    getchar();
                    break;
                case 5:
                    do
                    {
                        printf("Informe o novo VALOR DE VENDA do produto: ");
                        scanf(" %[^\n]", produtoAtual.valor_venda);
                        limparBuffer();
                    } while (!validarNome(produtoAtual.valor_venda));
                    printf(green "Produto editado com sucesso!\n" reset);
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
                fseek(fp, -sizeof(Produto), SEEK_CUR);
                // Escreve o registro modificado
                fwrite(&produtoAtual, sizeof(Produto), 1, fp);
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
    printf("Produto não encontrado.\n");
}

void excluirProduto(Produto *lista, const char *cnpj)
{
    FILE *fp = fopen("data/produtos.dat", "rb+");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto produtoAtual;

    while (fread(&produtoAtual, sizeof(Produto), 1, fp) == 1)
    {
        if (strcmp(produtoAtual.cnpj, cnpj) == 0)
        {
            mostrarProduto(&produtoAtual);
            printf("\nDeseja excluir este produto? (S/N): ");

            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();

            if (resposta == 'S' || resposta == 's')
            {
                // mudando o status para inativo
                produtoAtual.status = '0';

                // voltando para o início do arquivo
                fseek(fp, -sizeof(Produto), SEEK_CUR);
                // escreve a modificacao no arquivo
                fwrite(&produtoAtual, sizeof(Produto), 1, fp);
                printf(green "Produto excluido com sucesso!\n" reset);
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
    printf("Produto não encontrado.\n");
}

// obtendo o proximo valor de id
int pegarProximoIdProduto()
{
    FILE *fp = fopen("data/produtos.dat", "rb");
    if (fp == NULL)
    {
        return 1;
    }

    Produto ultimoProdutoLista;
    fseek(fp, -sizeof(Produto), SEEK_END);
    fread(&ultimoProdutoLista, sizeof(Produto), 1, fp);
    fclose(fp);

    return ultimoProdutoLista.id + 1;
}

// exibindo o produto
void mostrarProduto(const Produto *produto)
{
    printf("\n");
    printf("********* Dados do Fornecedor *********\n");
    printf("ID: %d\n", produto->id);
    printf("Nome: %s\n", produto->nome);
    printf("CNPJ: %s\n", produto->cnpj);
    printf("Valor de Compra: %s\n", produto->valor_compra);
    printf("Valor de Venda: %s\n", produto->valor_venda);
    printf("Status: %s\n", (produto->status == '1') ? green "Ativo" reset : red "Inativo" reset);
    printf("***************************************\n");
}

// exclusao logica do fornecedor por cnpj
void excluirProdutoPorCNPJ(Produto *lista)
{
    mostrarMenuExcluirProduto();
    char cnpjBusca[50];
    printf("Informe o CNPJ do fornecedor do produto que deseja excluir: ");
    scanf(" %[^\n]", cnpjBusca);
    limparBuffer();

    if (!ehCnpjRegistrado(cnpjBusca))
    {
        printf("CNPJ não encontrado.\n");
        return;
    }

    excluirProduto(lista, cnpjBusca);
}