// produtos.h
#if !defined(PRODUTOS_H)
#define PRODUTOS_H

typedef struct produto Produto;

struct produto
{
    char cnpj[15];
    char quantidade[9];
    char nome[50];
    char valor_compra[9];
    char valor_venda[9];
    int id;
    char status;
    Produto *prox;
};

void moduloProduto();
void cadastrarProduto();
void pesquisarProdutos();
void editarProduto();
void excluirProduto(const char *cnpj);

// auxiliar
int pegarProximoIdProduto();
void mostrarProduto(const Produto *produto);
void excluirProdutoPorCNPJ();

#endif // PRODUTOS_H
