// estrutura de informações de um cliente
typedef struct
{
    char nome[51];
    char cpf[15];
    char cidade[51];
    char estado[4];
    char endereco[100];
    char telefone[15];
    int status;
} Clientes;

// chamada das funções
void modulo_clientes(void);
char tela_clientes(void);
Clientes *tela_cadastra_cliente(int editando);
void tela_lista_cliente(void);
void grava_cliente(Clientes *);
void exibe_cliente(Clientes *cliente);
Clientes *tela_pesquisa_cliente(void);
Clientes *busca_cpf_cliente(char *cpf);
void tela_edita_cliente(void);
void regrava_cliente(Clientes *cliente);
void tela_excluir_cliente(void);