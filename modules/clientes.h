#if !defined(CLIENTES_H)
#define CLIENTES_H

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

// declaração das funções
void modulo_clientes(void);
char tela_clientes(void);
Clientes *tela_cadastra_cliente(int editando);
Clientes *tela_pesquisa_cliente(void);
void tela_edita_cliente(void);
void tela_excluir_cliente(void);
void tela_lista_cliente(void);

// declaração das funções auxiliares
void grava_cliente(Clientes *cliente);
void exibe_cliente(Clientes *cliente);
Clientes *busca_cpf_cliente(char *cpf);
void regrava_cliente(Clientes *cliente);


#endif // CLIENTES_H