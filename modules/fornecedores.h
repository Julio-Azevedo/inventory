// estrutura de informações de um fornecedor
typedef struct {
    char nome[50];
    int CNPJ[20];
    int telefone[12];
    char estado[2];
    char cidade[40];
    char email[50];
} Fornecedores;

// chamada das funções
void modulo_fornecedores(void);
char tela_fornecedores(void);
void tela_cadastra_fornecedor(void);