// estrutura de informações de um cliente
typedef struct {
    char nome[50];
    char cpf[15];
    char estado[2];
    char cidade[40];
    char endereco[120];
    int telefone[12];
} Clientes;

// chamada das funções
void modulo_clientes(void);
char tela_clientes(void);
void tela_cadastra_cliente(void);
void tela_lista_cliente(void);
