// estrutura de um produto
typedef struct {
    char nome[50];
    char codigo[8];
    char fornecedor[50];
    int valor_custo[10];
    int valor_venda[10];
    int qtd_estoque[10];
} Produtos;

// chamada das funções
void modulo_produtos(void);
char tela_produtos(void);
void tela_cadastrar_produtos(void);