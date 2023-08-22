#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sobre.h"

/* Assinatura das funções */
char telaPrincipal(void);
void telaSobre(void);
void telaEquipe(void);

int main(void) {
    char option;

    do {
        option = telaPrincipal();
        switch (option)
        {
        case '1':
            /* chamando a função */
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
    printf("///            1. Inventory                                                 ///\n");
    printf("///            2. Módulo Componentes                                        ///\n");
    printf("///            3. Módulo Sobre                                              ///\n");
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