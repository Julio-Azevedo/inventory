#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sobre.h"
#include "registro.h"

// Assinatura das funções 
char telaPrincipal(void);
void telaSobre(void);
void telaEquipe(void);
void moduloUsuario(void);
int cadastroUsuario();

int main(void) {
    char option;

    do {
        option = telaPrincipal();
        switch (option)
        {
        case '1':
            moduloUsuario();
            break;
        case '2':
            telaEquipe();
            break;
        case '3':
            telaSobre();
            break;
        }
    } while (option != '0');

    return 0;
}

char telaPrincipal(void) {
    char op;

    system("clear||cls");
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = Sistema Inventory = = = = =                        ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Acessar Inventory                                         ///\n");
    printf("///            2. Componentes                                               ///\n");
    printf("///            3. Sobre o projeto                                           ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a opção desejada: ");
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