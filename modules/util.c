// arquivo de validações do programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include "util.h"
#include "clientes.h"
#include "fornecedores.h"

// função que limpa o buffer após passar um dado de entrada
void limpa_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// função que apaga o conteúdo da interface
void limpar_tela(void)
{
    system("clear||cls");
}

// função que faz a validação de nomes
int valida_nome(const char *nome)
{
    int i;
    int letras = 0;

    for (i = 0; nome[i] != L'\0'; i++)
    {
        wchar_t c = nome[i];
        if (iswalpha(c) || c == L' ' || c == L'-' || c == L'\'')
        {
            letras = 1;
        }
        else
        {
            // caracter inválido
            return 0;
        }
    }
    // deve conter pelo menos uma letra
    return letras;
}
/////////////////////////////////////////////////////////////////////////////
/// feito por Julio-Azevedo: https://github.com/Julio-Azevedo/inventory

// função que faz a validação de cpfs
int valida_cpf(const char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
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

// validação de digitos numericos
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
/////////////////////////////////////////////////////////////////////////////
/// Flavius Gorgonio: https://github.com/flgorgonio/linguasolta_2020.2

// validação de telefone
int valida_telefone(const char *telefone)
{
    int tam;
    tam = strlen(telefone);
    if (tam != 13)
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
/////////////////////////////////////////////////////////////////////////////
/// Adaptado de Flavius Gorgonio: https://github.com/flgorgonio/linguasolta_2020.2

// verifica se o CPF já está cadastrado
int verifica_cpf_cliente(const char *cpf)
{
    Clientes cliente;
    FILE *fp = fopen("clientes.dat", "ab+");
    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return -1; // indica erro na abertura do arquivo
    }

    // levando o ponteiro para o inicio do arquivo
    fseek(fp, 0, SEEK_SET);

    while (fread(&cliente, sizeof(Clientes), 1, fp))
    {
        if (cliente.status == 1 && strcmp(cliente.cpf, cpf) == 0)
        {
            // fechando o arquivo
            fclose(fp);
            // cpf já existente
            return 1;
        }
    }
    // fechando o arquivo
    fclose(fp);
    // cpf válido
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
///  feito por chatGPT

// validação de cnpj
int valida_cnpj(const char *cnpj)
{
    int resto;
    int i, j, soma, digito1, digito2;
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
/////////////////////////////////////////////////////////////////////////////
///  feito por chatGPT

// verifica se o cnpj ja está cadastrado no arquivo de fornecedores
int verifica_cnpj_fornecedor(const char *cnpj)
{
    Fornecedores fornecedor;
    FILE *fp = fopen("fornecedores.dat", "ab+");
    if (fp == NULL)
    {
        // se não for possível abrir o arquivo, mesmo para criação, retorna -1.
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // levando o ponteiro para o inicio do arquivo
    fseek(fp, 0, SEEK_SET);

    while (fread(&fornecedor, sizeof(Fornecedores), 1, fp))
    {
        if (fornecedor.status == 1 && strcmp(fornecedor.cnpj, cnpj) == 0)
        {
            // fechando o arquivo
            fclose(fp);
            // cnpj já cadastrado
            return 1;
        }
    }
    // fechando o arquivo
    fclose(fp);
    // cnpj livre para cadastro
    return 0;
}
/////////////////////////////////////////////////////////////////////////////
///  feito por chatGPT

// valição de cep para o cadastro de fornecedores
int valida_cep(const char *cep)
{
    int i;

    // Verifica o tamanho do CEP
    if (strlen(cep) != 8)
    {
        return 0;
    }

    // Verifica se todos os caracteres são dígitos
    for (i = 0; i < 8; i++)
    {
        if (!ehDigito((unsigned char)cep[i]))
        {
            return 0; // retorna falso se não for
        }
    }

    // cep válido
    return 1;
}
/////////////////////////////////////////////////////////////////////////////
///  feito por chatGPT

// validação de email para o cadastro de fornecedores
int valida_email(char *email)
{
    char usuario[256], site[256], dominio[256];
    if (sscanf(email, "%[^@ \t\n]@%[^. \t\n].%3[^ \t\n]", usuario, site, dominio) != 3)
        return 0;
    return 1;
}
/////////////////////////////////////////////////////////////////////////////
/// feito por "LACOBUS": https://pt.stackoverflow.com/questions/310096/como-validar-um-e-mail-em-c

char controle_menu(void)
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
/////////////////////////////////////////////////////////////////////////////
/// feito por Julio-Azevedo: https://github.com/Julio-Azevedo/inventory