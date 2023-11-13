#if !defined(FORNECEDORES_H)
#define FORNECEDORES_H

// estrutura de informações de um fornecedor
typedef struct
{
    char nome[51];
    char cnpj[21];
    char cidade[51];
    char estado[4];
    char cep[11];
    char telefone[15];
    char email[50];
    int status;
} Fornecedores;

// declaração das funções
void modulo_fornecedores(void);
char tela_fornecedores(void);
Fornecedores *tela_cadastra_fornecedor(int editando);
Fornecedores *tela_pesquisa_fornecedor(void);
void tela_edita_fornecedor(void);
void tela_excluir_fornecedor(void);
void tela_listar_fornecedor(void);

// declaração das funções auxiliares
void grava_fornecedor(Fornecedores *fornecedor);
void exibe_fornecedor(Fornecedores *fornecedor);
void regrava_fornecedor(Fornecedores *fornecedor);
Fornecedores *busca_cnpj_fornecedor(const char *cnpj);

#endif // FORNECEDORES_H