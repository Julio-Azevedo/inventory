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
    do
    {
        mostrarMenuProdutos();
        opcao = pegarMenuEscolha();

        switch (opcao)
        {
        case '1':
            cadastrarProduto();
            break;
        case '2':
            pesquisarProdutos();
            break;
        case '3':
            editarProduto();
            break;
        case '4':
            excluirProdutoPorCNPJ();
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

// cadastro de produto
void cadastrarProduto()
{
    // aloca memoria para a struct
    Produto *novoProduto = (Produto *)malloc(sizeof(Produto));
    // exibindo o menu de cadastro de produto
    mostrarMenuCadastroProduto();

    // solicitando o cnpj do fornecedor do produto
    do
    {
        printf("Informe o CNPJ do fornecedor do produto: ");
        scanf(" %[^\n]", novoProduto->cnpj);
        limparBuffer();
    } while (!validarCnpj(novoProduto->cnpj) || !ehCnpjRegistrado(novoProduto->cnpj));

    // solicitando a quantidade de produtos para adicionar ao estoque
    do
    {
        printf("Informe a QUANTIDADE de unidades do produto: ");
        scanf(" %[^\n]", novoProduto->quantidade);
        limparBuffer();
    } while (!validarNumero(novoProduto->quantidade));

    // solicitando o nome do produto
    do
    {
        printf("Informe o NOME do produto: ");
        scanf(" %[^\n]", novoProduto->nome);
        limparBuffer();
    } while (!validarNome(novoProduto->nome));

    // solicitando o valor que o produto foi comprado
    do
    {
        printf("Informe o VALOR DE COMPRA do produto: ");
        scanf(" %[^\n]", novoProduto->valor_compra);
        limparBuffer();
    } while (!validarNumero(novoProduto->valor_compra));

    // solicitando o valor que o produto vai ser vendido
    do
    {
        printf("Informe o VALOR DE VENDA do produto: ");
        scanf(" %[^\n]", novoProduto->valor_venda);
        limparBuffer();
    } while (!validarNumero(novoProduto->valor_venda));

    // adicionando um novo id ao produto
    novoProduto->id = pegarProximoIdProduto();
    // informando que o status do produto esta ativo
    novoProduto->status = '1';
    // inicializando o ponteiro prox como NULL
    novoProduto->prox = NULL;

    // abrindo o arquivo de produtos
    FILE *fp = fopen("data/produtos.dat", "ab");
    // fazendo o tratamento de erro
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo para escrita.");

    // escrevendo novo produto no arquivo de produtos
    fwrite(novoProduto, sizeof(Produto), 1, fp);
    // fechando o arquivo de produtos
    fclose(fp);

    printf("\n");
    printf(green "Produto cadastrado com sucesso!\n" reset);
    printf("\t<ENTER> para continuar\n");
    getchar();
    free(novoProduto);
}

// pesquisa de produtos
void pesquisarProdutos()
{
    Produto produto;
    int encontrado = 0;
    char opcaoPesquisa;
    char termoPesquisa[50];

    mostrarMenuPesquisaProduto();

    printf("* Escolha o critério de pesquisa:                                           *\n");
    printf("* 1. CNPJ                                                                   *\n");
    printf("* 2. Nome do Produto                                                        *\n");
    printf("*****************************************************************************\n");
    printf("\n");
    printf("Opção: ");
    scanf(" %c", &opcaoPesquisa);
    limparBuffer();

    switch (opcaoPesquisa)
    {
    case '1':
        printf("Informe o CNPJ do fornecedor do produto (somente números): ");
        scanf(" %[^\n]", termoPesquisa);
        limparBuffer();
        break;
    case '2':
        printf("Informe o Nome do Produto: ");
        scanf(" %[^\n]", termoPesquisa);
        limparBuffer();
        break;
    default:
        printf("Opção de pesquisa inválida.\n");
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
        return;
    }

    FILE *fp = fopen("data/produtos.dat", "rb");

    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo de produtos.\n");
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
        return;
    }

    while (!feof(fp) && fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        if ((opcaoPesquisa == '1' && strcmp(produto.cnpj, termoPesquisa) == 0) ||
            (opcaoPesquisa == '2' && strcmp(produto.nome, termoPesquisa) == 0) &&
                produto.status == '1')
        {
            mostrarProduto(&produto);
            printf("\n");
            encontrado = 1;
        }
    }

    fclose(fp);

    if (!encontrado)
    {
        printf("Nenhum produto encontrado com o critério de pesquisa especificado.\n");
        printf("\n");
        printf("\t<ENTER> para continuar\n");
        getchar();
    }

    printf("\t<ENTER> para voltar\n");
    getchar();
}

// editar produto
void editarProduto()
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

// excluir produto
void excluirProduto(const char *cnpj)
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

// FUNCOES AUXILIARES DE PRODUTOS

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
    // Abra o arquivo de fornecedores para leitura
    FILE *fornecedoresFile = fopen("data/fornecedores.dat", "rb");
    if (fornecedoresFile == NULL)
    {
        printf("Erro na abertura do arquivo de fornecedores.\n");
        return;
    }

    // Procure o fornecedor pelo CNPJ
    Fornecedor fornecedor;
    int encontrado = 0;
    while (fread(&fornecedor, sizeof(Fornecedor), 1, fornecedoresFile) == 1)
    {
        if (strcmp(fornecedor.cnpj, produto->cnpj) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    // Feche o arquivo de fornecedores
    fclose(fornecedoresFile);

    printf("\n");
    printf("********* Dados do Fornecedor *********\n");
    printf("ID: %d\n", produto->id);
    printf("Nome: %s\n", produto->nome);
    printf("Fornecedor: %s (%s)\n", fornecedor.nome, produto->cnpj);
    printf("Quantidade em estoque: %s\n", produto->quantidade);
    printf("Valor de Compra: %s\n", produto->valor_compra);
    printf("Valor de Venda: %s\n", produto->valor_venda);
    printf("Status: %s\n", (produto->status == '1') ? green "Ativo" reset : red "Inativo" reset);
    printf("***************************************\n");
}

// exclusao logica do fornecedor por cnpj
void excluirProdutoPorCNPJ()
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

    excluirProduto(cnpjBusca);
}
