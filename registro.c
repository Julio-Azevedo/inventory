#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "registro.h"
#include "painel.h"

// Assinaturas
char menuInicial(void);
void painelUsuario(void);

// Função principal de usuários
void moduloUsuario(void) {
    char opcao;
    do {
        opcao = menuInicial();
        switch(opcao) {
        case '1':
            if (loginUsuario()){
                painelPrincipal();
            }
            break;
        case '2':
            cadastroUsuario();
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

char menuInicial(void) {
    char op;

    system("clear||cls");
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = Acessando o Inventory = = = = =                    ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Login                                                     ///\n");
    printf("///            2. Cadastro                                                  ///\n");
    printf("///            0. Voltar                                                    ///\n");
    printf("///                                                                         ///\n");
    printf("///            Digite a opção desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t\t\t<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

// A estrutura de dados de um usuário
typedef struct {
    char nome[50];
    char senha[50];
    char cpf[12];
} Usuario;

// Função para cadastrar novos usuários
int cadastroUsuario() {
    FILE *arquivo;
    Usuario usuario;

    // Solicitando dados para o cadastro
    // Nome
    printf("Informe seu nome: ");
    scanf("%s", usuario.nome);

    // Senha
    printf("Informe sua senha: ");
    scanf("%s", usuario.senha);

    // Cpf
    printf ("Informe seu CPF: ");
    scanf("%s", usuario.cpf);


    // Manipulando o arquivo para salvar as informações
    arquivo = fopen("usuarios.dat", "ab");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0; // Falha no cadastro
    }
    
    // Definindo a estrutura do arquivo usuarios.dat
    fwrite(&usuario, sizeof(Usuario), 1, arquivo);

    // Fechando arquivo
    fclose(arquivo);

    printf("Cadastro realizado com sucesso!");
    return 1; // Sucesso no cadastro
}

// Função para fazer login de usuário
int loginUsuario() {
    FILE *arquivo;
    Usuario usuario;
    char cpfUsuario[12];
    char senhaUsuario[50];

    // Requisitando o CPF
    printf("CPF: ");
    scanf("%s", cpfUsuario);

    // Requisitando a senha
    printf("Senha: ");
    scanf("%s", senhaUsuario);

    // Fazendo leitura do arquivo que de registros
    arquivo = fopen("usuarios.dat", "rb");

    if (arquivo == NULL) {
        perror("Erro ao acessar o banco de dados");
        return 0;
    }
    
    int encontrado = 0;

    // Lendo cada registro que está no arquivo
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
        // Comparando CPF e senha
        if (strcmp(usuario.cpf, cpfUsuario) == 0 && strcmp(usuario.senha, senhaUsuario) == 0) {
            encontrado = 1;
            break;
        }
    }   

    // Fechando o arquivo
    fclose(arquivo);

    if (encontrado) {
        return 1; // Sucesso
    } else {
        return 0; // Falha
    }
}