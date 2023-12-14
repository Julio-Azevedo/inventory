// util.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void limparTela(void)
{
    system("clear||cls");
}

int ehDigito(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char controlarMenu(void)
{
    char op;
    int contador;
    do
    {
        contador = 0;

        printf("Selecione a alternativa desejada: ");
        scanf(" %c", &op);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (ehDigito(c))
            {
                contador++;
            }
        }

        if (contador > 0)
        {
            printf("Entrada invalida, tente novamente\n");
        }

    } while (contador > 0);

    return op;
}

// validador de email
int validarEmail(char *email)
{
    char usuario[256], site[256], dominio[256];
    if (sscanf(email, "%[^@ \t\n]@%[^. \t\n].%3[^ \t\n]", usuario, site, dominio) != 3)
        return 0;
    return 1;
}
// feito por "LACOBUS": https://pt.stackoverflow.com/questions/310096/como-validar-um-e-mail-em-c

// faz o tratamento do nulo
void tratamentoVerificaNulo(void *ponteiro, const char *mensagem_erro)
{
    if (ponteiro == NULL)
    {
        fprintf(stderr, "Erro: %s", mensagem_erro);
        exit(EXIT_FAILURE);
    }
}
// feito por Julio-Azevedo":

// função que valida nomes
int validarNome(const char *nome)
{
    int i;
    int letras = 0;

    for (i = 0; nome[i] != '\0'; i++)
    {
        char c = nome[i];
        if (isalpha(c) || c == ' ' || c == '-' || c == '\'')
        {
            letras = 1;
        }
        else
        {
            return 0;
        }
    }
    return letras;
}

// validador de cnpj
int validarCnpj(const char *cnpj)
{
    int resto;
    int i, soma, digito1, digito2;
    int multiplicador1[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int multiplicador2[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    if (strlen(cnpj) != 14)
        return 0;

    // Verifica CNPJs invalidos conhecidos
    if ((strcmp(cnpj, "00000000000000") == 0) ||
        (strcmp(cnpj, "11111111111111") == 0) ||
        (strcmp(cnpj, "22222222222222") == 0) ||
        (strcmp(cnpj, "33333333333333") == 0) ||
        (strcmp(cnpj, "44444444444444") == 0) ||
        (strcmp(cnpj, "55555555555555") == 0) ||
        (strcmp(cnpj, "66666666666666") == 0) ||
        (strcmp(cnpj, "77777777777777") == 0) ||
        (strcmp(cnpj, "88888888888888") == 0) ||
        (strcmp(cnpj, "99999999999999") == 0))
        return 0;

    // Validação do primeiro dígito verificador
    soma = 0;
    for (i = 0; i < 12; i++)
    {
        soma += (cnpj[i] - '0') * multiplicador1[i];
    }

    resto = soma % 11;
    if (resto < 2)
        digito1 = 0;
    else
        digito1 = 11 - resto;

    if (cnpj[12] - '0' != digito1)
        return 0;

    // Validação do segundo dígito verificador
    soma = 0;
    for (i = 0; i < 13; i++)
    {
        soma += (cnpj[i] - '0') * multiplicador2[i];
    }

    resto = soma % 11;
    if (resto < 2)
        digito2 = 0;
    else
        digito2 = 11 - resto;

    if (cnpj[13] - '0' != digito2)
        return 0;

    return 1;
}
//  feito por ChatGPT : https://chat.openai.com/

// validador de telefone
int validarTelefone(const char *telefone)
{
    int tam;
    tam = strlen(telefone);
    if (tam != 11)
    {
        return 0;
    }
    for (int i = 0; i < tam; i++)
    {
        if (!ehDigito(telefone[i]))
        {
            return 0;
        }
    }
    return 1;
}
// Adaptado de Flavius Gorgonio: https://github.com/flgorgonio/linguasolta_2020.2

int validarNumero(const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Não é um dígito
        }
    }
    return 1; // Todos os caracteres são dígitos
}

int validarCpf(const char *cpf)
{
    size_t i, j;
    int digito1 = 0, digito2 = 0;
    if (strlen(cpf) != 11)
        return 0;
    else if ((strcmp(cpf, "00000000000") == 0) || (strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) ||
             (strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || (strcmp(cpf, "55555555555") == 0) ||
             (strcmp(cpf, "66666666666") == 0) || (strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) ||
             (strcmp(cpf, "99999999999") == 0))
        return 0; /// se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        /// digito 1---------------------------------------------------
        for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--) /// multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i] - 48) * j;
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 0; /// se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        /// digito 2--------------------------------------------------
        {
            for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--) /// multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                digito2 += (cpf[i] - 48) * j;
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
                return 0; /// se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}
// feito por "EDUARDO EDSON": https://gist.github.com/eduardoedson