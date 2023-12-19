//cliente.h
#if !defined(CLIENTE_H)
#define CLIENTE_H

typedef struct cliente Cliente;

struct cliente 
{
    char cpf[20];
    char email[50];
    char telefone[15];
    char nome[50];
    char status;
    int id;
    Cliente* prox;
};

void moduloCliente();
void cadastrarCliente(); 
void pesquisarCliente();
void editarCliente();
void excluirCliente(const char *cpf);

// auxiliar
int ehEmailClienteRegistrado(const char *email);
int ehCpfRegistrado(const char *cpf);
int pegarProximoIdCliente();
void mostrarCliente(const Cliente *cliente);
void excluirClientePorCPF();


// colors
#define green "\x1b[32m"
#define red "\x1b[31m"
#define reset "\x1b[0m"

#endif // CLIENTE_H
