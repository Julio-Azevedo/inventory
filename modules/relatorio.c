// relatorio.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "fornecedor.h"
#include "produto.h"
#include "cliente.h"
#include "relatorio.h"
#include "../common/menus.h"

void moduloRelatorio()
{
    char opcao;

    do
    {
        mostrarMenuRelatorio();
        opcao = pegarMenuEscolha();

        switch (opcao)
        {
        case '1':
            relatorioTodosFornecedores();
            break;
        case '2':
            relatorioFornecedoresInativos();
            break;
        case '3':
            relatorioFornecedoresOrdemAlfabetica();
            break;
        case '4':
            relatorioTodosProdutos();
            break;
        case '5':
            relatorioProdutoInativos();
            break;
        case '6':
            relatorioProdutosOrdemAlfabetica();
            break;
        case '7':
            relatorioTodosClientes();
            break;
        case '8':
            relatorioClientesInativos();
            break;
        case '9':
            relatorioClientesOrdemAlfabetica();
            break;
        case '0':
            break;
        default:
            printf("Escolha invalida, tente novamente\n");
        }
    } while (opcao != '0');
}

// funcao para colocar Fornecedores em ordem alfabetica
int compararFornecedores(const void *a, const void *b)
{
    return strcmp(((Fornecedor *)a)->nome, ((Fornecedor *)b)->nome);
}

// funcao para colocar produtos em ordem alfabetica
int compararProdutos(const void *a, const void *b)
{
    return strcmp(((Produto *)a)->nome, ((Produto *)b)->nome);
}

// funcao para colocar clientes em ordem alfabetica
int compararClientes(const void *a, const void *b)
{
    return strcmp(((Cliente *)a)->nome, ((Cliente *)b)->nome);
}

void relatorioTodosFornecedores()
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Fornecedor fornecedor;

    printf("Relatório de Fornecedores:\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CNPJ", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    while (fread(&fornecedor, sizeof(Fornecedor), 1, fp) == 1)
    {
        printf("| %-15s | %-5d | %-50s | %-6c |\n", fornecedor.cnpj, fornecedor.id, fornecedor.nome, fornecedor.status);
        printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    }
    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioFornecedoresAtivos()
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Fornecedor fornecedor;

    printf("Relatório de Fornecedores:\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CNPJ", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    while (fread(&fornecedor, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (fornecedor.status == '1')
        {
            printf("| %-15s | %-5d | %-50s | %-6c |\n", fornecedor.cnpj, fornecedor.id, fornecedor.nome, fornecedor.status);
            printf("|-----------------|-------|----------------------------------------------------|--------|\n");
        }
    }
    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioFornecedoresInativos()
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Fornecedor fornecedor;

    printf("Relatório de Fornecedores:\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CNPJ", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    while (fread(&fornecedor, sizeof(Fornecedor), 1, fp) == 1)
    {
        if (fornecedor.status == '0')
        {
            printf("| %-15s | %-5d | %-50s | %-6c |\n", fornecedor.cnpj, fornecedor.id, fornecedor.nome, fornecedor.status);
            printf("|-----------------|-------|----------------------------------------------------|--------|\n");
        }
    }
    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioFornecedoresOrdemAlfabetica()
{
    FILE *fp = fopen("data/fornecedores.dat", "rb");
    if (fp == NULL)
    {
        tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");
        return;
    }

    Fornecedor *fornecedores;
    int numFornecedores = 0;

    // Contar o número de fornecedores
    fseek(fp, 0, SEEK_END);
    long tamanhoArquivo = ftell(fp);
    numFornecedores = tamanhoArquivo / sizeof(Fornecedor);
    rewind(fp);

    // Alocar espaço para os fornecedores
    fornecedores = (Fornecedor *)malloc(numFornecedores * sizeof(Fornecedor));
    if (fornecedores == NULL)
    {
        fclose(fp);
        fprintf(stderr, "Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    // Ler os fornecedores do arquivo
    fread(fornecedores, sizeof(Fornecedor), numFornecedores, fp);

    // Ordenar os fornecedores pelo nome
    qsort(fornecedores, numFornecedores, sizeof(Fornecedor), compararFornecedores);

    // Imprimir o relatório
    printf("Relatório de Fornecedores (Ordenado por Nome):\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CNPJ", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    for (int i = 0; i < numFornecedores; i++)
    {
        printf("| %-15s | %-5d | %-50s | %-6c |\n", fornecedores[i].cnpj, fornecedores[i].id, fornecedores[i].nome, fornecedores[i].status);
        printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    }
    printf("\n");
    printf("\t<ENTER> para continuar\n");

    // Liberar a memória alocada
    free(fornecedores);

    // Fechar o arquivo
    fclose(fp);

    // Aguardar a tecla Enter
    getchar();
}

void relatorioTodosProdutos()
{
    FILE *fp = fopen("data/produtos.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto produto;

    printf("Relatório de Produtos:\n\n");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    printf("| %-15s | %-5s | %-50s | %-8s | %-9s | %-7s | %-6s |\n", "CNPJ", "ID", "Nome", "Qtd.", "V. Cmp", "V. Vnd", "Status");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");

    while (fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        printf("| %-15s | %-5d | %-50s | %-8s | %-9s | %-7s | %-6c |\n",
               produto.cnpj, produto.id, produto.nome, produto.quantidade, produto.valor_compra, produto.valor_venda, produto.status);
        printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioProdutosAtivos()
{
    FILE *fp = fopen("data/produtos.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto produto;

    printf("Relatório de Produtos:\n\n");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    printf("| %-15s | %-5s | %-50s | %-8s | %-9s | %-7s | %-6s |\n", "CNPJ", "ID", "Nome", "Qtd.", "V. Cmp", "V. Vnd", "Status");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");

    while (fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        // verifica se o produto está ativo
        if (produto.status == '1')
        {
            printf("| %-15s | %-5d | %-50s | %-8s | %-9s | %-7s | %-6c |\n",
                   produto.cnpj, produto.id, produto.nome, produto.quantidade, produto.valor_compra, produto.valor_venda, produto.status);
            printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
        }
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioProdutoInativos()
{
    FILE *fp = fopen("data/produtos.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto produto;

    printf("Relatório de Produtos:\n\n");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    printf("| %-15s | %-5s | %-50s | %-8s | %-9s | %-7s | %-6s |\n", "CNPJ", "ID", "Nome", "Qtd.", "V. Cmp", "V. Vnd", "Status");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");

    while (fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        // verifica se o produto está inativo
        if (produto.status == '0')
        {
            printf("| %-15s | %-5d | %-50s | %-8s | %-9s | %-7s | %-6c |\n",
                   produto.cnpj, produto.id, produto.nome, produto.quantidade, produto.valor_compra, produto.valor_venda, produto.status);
            printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
        }
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();
    fclose(fp);
}

void relatorioProdutosOrdemAlfabetica()
{
    FILE *fp = fopen("data/produtos.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Produto *produtos = NULL;
    size_t numProdutos = 0;

    Produto produto;

    // Lê todos os produtos do arquivo
    while (fread(&produto, sizeof(Produto), 1, fp) == 1)
    {
        produtos = realloc(produtos, (numProdutos + 1) * sizeof(Produto));
        produtos[numProdutos] = produto;
        numProdutos++;
    }

    // Ordena os produtos em ordem alfabética
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutos);

    printf("Relatório de Produtos em Ordem Alfabetica:\n\n");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    printf("| %-15s | %-5s | %-50s | %-8s | %-9s | %-7s | %-6s |\n", "CNPJ", "ID", "Nome", "Qtd.", "V. Cmp", "V. Vnd", "Status");
    printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");

    // Exibe os produtos ordenados
    for (size_t i = 0; i < numProdutos; i++)
    {
        printf("| %-15s | %-5d | %-50s | %-8s | %-9s | %-7s | %-6c |\n",
               produtos[i].cnpj, produtos[i].id, produtos[i].nome, produtos[i].quantidade, produtos[i].valor_compra, produtos[i].valor_venda, produtos[i].status);
        printf("|-----------------|-------|----------------------------------------------------|----------|-----------|---------|--------|\n");
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");
    getchar();

    free(produtos);
    fclose(fp);
}

void relatorioTodosClientes()
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Cliente cliente;

    printf("Relatório de Clientes:\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CPF", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");

    while (fread(&cliente, sizeof(Cliente), 1, fp) == 1)
    {
        printf("| %-15s | %-5d | %-50s | %-6c |\n", cliente.cpf, cliente.id, cliente.nome, cliente.status);
        printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");

    // Aguardar a tecla Enter
    getchar();

    // Fechar o arquivo
    fclose(fp);
}

void relatorioClientesInativos()
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");

    Cliente cliente;

    printf("Relatório de Clientes:\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CPF", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");

    while (fread(&cliente, sizeof(Cliente), 1, fp) == 1)
    {
        if (cliente.status == '0')
        {
            printf("| %-15s | %-5d | %-50s | %-6c |\n", cliente.cpf, cliente.id, cliente.nome, cliente.status);
            printf("|-----------------|-------|----------------------------------------------------|--------|\n");
        }
    }

    printf("\n");
    printf("\t<ENTER> para continuar\n");

    // Aguardar a tecla Enter
    getchar();

    // Fechar o arquivo
    fclose(fp);
}

void relatorioClientesOrdemAlfabetica()
{
    FILE *fp = fopen("data/clientes.dat", "rb");
    if (fp == NULL)
    {
        tratamentoVerificaNulo(fp, "Erro na abertura do arquivo");
        return;
    }

    Cliente *clientes;
    int numClientes = 0;

    // Contar o número de clientes
    fseek(fp, 0, SEEK_END);
    long tamanhoArquivo = ftell(fp);
    numClientes = tamanhoArquivo / sizeof(Cliente);
    rewind(fp);

    // Alocar espaço para os clientes
    clientes = (Cliente *)malloc(numClientes * sizeof(Cliente));
    if (clientes == NULL)
    {
        fclose(fp);
        fprintf(stderr, "Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    // Ler os clientes do arquivo
    fread(clientes, sizeof(Cliente), numClientes, fp);

    // Ordenar os clientes pelo nome
    qsort(clientes, numClientes, sizeof(Cliente), compararClientes);

    // Imprimir o relatório
    printf("Relatório de Clientes (Ordenado por Nome):\n\n");
    printf("| %-15s | %-5s | %-50s | %-6s |\n", "CPF", "ID", "Nome", "Status");
    printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    for (int i = 0; i < numClientes; i++)
    {
        printf("| %-15s | %-5d | %-50s | %-6c |\n", clientes[i].cpf, clientes[i].id, clientes[i].nome, clientes[i].status);
        printf("|-----------------|-------|----------------------------------------------------|--------|\n");
    }
    printf("\n");
    printf("\t<ENTER> para continuar\n");

    // Liberar a memória alocada
    free(clientes);

    // Fechar o arquivo
    fclose(fp);

    // Aguardar a tecla Enter
    getchar();
}