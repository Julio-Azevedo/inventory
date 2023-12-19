// fornecedor.h
#if !defined(FORNECEDOR_H)
#define FORNECEDOR_H

typedef struct fornecedor Fornecedor;

struct fornecedor
{
    char cnpj[15];
    char email[50];
    char telefone[15];
    char nome[50];
    int id;
    char status;
    Fornecedor* prox;
};


void moduloFornecedor();
void cadastrarFornecedor();
void pesquisarFornecedor();
void editarFornecedor(Fornecedor *lista);
void excluirFornecedor(const char *cnpj);

// auxiliar
int pegarProximoIdFornecedor();
void mostrarFornecedor(const Fornecedor *fornecedor);
int ehEmailRegistrado(const char *email);
int ehCnpjRegistrado(const char *cnpj);
int fornecedorJaCadastrado(const char *cnpj, const char *email);
void excluirFornecedorPorCNPJ();

// colors
#define green "\x1b[32m"
#define red "\x1b[31m"
#define reset "\x1b[0m"

#endif // FORNECEDOR_H
