// arquivo de validações do programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include "util.h"

// funcionalidades
// limpar o buffer apos algum dado de entrada ser passado
void limpa_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// validação de nomes
int valida_nome(const char *nome) {
    int i;
    int letras = 0;

    for (i = 0; nome[i] != L'\0'; i++) {
        wchar_t c = nome[i];
        if (iswalpha(c) || c == L' ' || c == L'-' || c == L'\'') {
            letras = 1;
        } else {
            return 0;  // caracter inválido 
        }
    }

    return letras;  // Deve conter pelo menos uma letra
}

// validação de cpf
int valida_cpf(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}    
// FEITO POR: EDUARDO EDSON /// GIT: https://gist.github.com/eduardoedson

// validação de digitos numericos
int ehDigito(char c) {
  if (c >= '0' && c <= '9') {
    return 1;
  } else {
    return 0;
  }
}
/////////////////////////////////////////////////////////////////////////////
/// Flavius Gorgonio: https://github.com/flgorgonio/linguasolta_2020.2

// validação de telefone
int valida_telefone(char* telefone) {
  int tam;
  tam = strlen(telefone);
  if (tam != 13) {
    return 0;
  }
  for (int i = 0; i < tam; i++) {
    if (!ehDigito(telefone[i])) {
        return 0;
    }
  }
  return 1;
}
/////////////////////////////////////////////////////////////////////////////
/// Adaptado de Flavius Gorgonio: https://github.com/flgorgonio/linguasolta_2020.2