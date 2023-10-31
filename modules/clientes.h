// estrutura de informações de um cliente
typedef struct {
    char nome[51];
    char cpf[12];
    char cidade[21];
    char estado[3];
    char endereco[100];
    char telefone[14];
} Clientes;

// chamada das funções
void modulo_clientes(void);
char tela_clientes(void);
Clientes* tela_cadastra_cliente(void);
void tela_lista_cliente(void);
void grava_cliente(Clientes*);
