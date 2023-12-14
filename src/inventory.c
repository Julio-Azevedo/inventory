#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common/menus.h"
#include "../modules/sobre.h"

int main()
{
    char opcao;
    do
    {
        mostrarMenuInicial();
        opcao = pegarMenuEscolha();

        switch (opcao)
        {
        case '1':
            menuPrincipal();
            break;
        case '2':
            telaSobre();
            break;
        case '0':
            break;
        default:
            printf("Escolha invalida, tente novamente\n");
        }
    } while (opcao != '0');

    return 0;
}