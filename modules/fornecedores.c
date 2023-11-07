#include <stdio.h>
#include <string.h>
#include <stdlib.h> // para a função system
#include <unistd.h> // para a função sleep
#include "util.h"
#include "fornecedores.h"

// chamada das funções
char tela_fornecedores(void);
Fornecedores *tela_cadastra_fornecedor(int editando);
void grava_fornecedor(Fornecedores *fornecedor);
void exibe_fornecedor(Fornecedores *fornecedor);
void tela_listar_fornecedor(void);
void regrava_fornecedor(Fornecedores *fornecedor);
Fornecedores *tela_pesquisa_fornecedor(void);
void tela_edita_fornecedor(void);
Fornecedores *busca_cnpj_fornecedor(const char *cnpj);
void tela_excluir_fornecedor(void);
//

void modulo_fornecedores(void)
{
    char opcao;
    Fornecedores *rel;
    do
    {
        opcao = tela_fornecedores();
        switch (opcao)
        {
        case '1':
            rel = tela_cadastra_fornecedor(0);
            grava_fornecedor(rel);
            break;
        case '2':
            tela_pesquisa_fornecedor();
            break;
        case '3':
            tela_edita_fornecedor();
            break;
        case '4':
            tela_excluir_fornecedor();
            break;
        case '5':
            tela_listar_fornecedor();
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

char tela_fornecedores(void)
{
    char op;

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                    = = = = = Fornecedores = = = = =                        *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* 1. Cadastrar um novo fornecedor                                            *\n");
    printf("* 2. Pesquisar fornecedor                                                    *\n");
    printf("* 3. Editar fornecedor                                                       *\n");
    printf("* 4. Excluir fornecedor                                                      *\n");
    printf("* 5. Listar fornecedores                                                     *\n");
    printf("* 0. Voltar                                                                  *\n");
    printf("******************************************************************************\n");
    printf("Selecione a alternativa desejada: ");
    scanf(" %c", &op);
    getchar();
    printf("<<< ... Aguarde ... >>>\n");
    sleep(1);
    return op;
}

// função que realiza o cadastro de fornecedores - code 1
Fornecedores *tela_cadastra_fornecedor(int editando)
{
    int cnpj_exite = 0;
    int cnpj_valido = 0;
    Fornecedores *fornecedor = (Fornecedores *)malloc(sizeof(Fornecedores));
    if (fornecedor == NULL)
    {
        perror("Erro na alocação de memória");
        return NULL;
    }
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                 = = = = = Cadastrar Fornecedor = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    do
    {
        printf("Digite o nome do fornecedor: ");
        scanf(" %[^\n]", fornecedor->nome);
        limpa_buffer();
    } while (!valida_nome(fornecedor->nome));

    do
    {
        printf("Digite o cnpj do fornecedor (apenas numeros): ");
        scanf(" %[^\n]", fornecedor->cnpj);
        limpa_buffer();

        cnpj_exite = verifica_cnpj_fornecedor(fornecedor->cnpj);

        if (!editando)
        {
            cnpj_exite = verifica_cnpj_fornecedor(fornecedor->cnpj);
            if (cnpj_exite)
            {
                printf("\n");
                printf("<<< cnpj de fornecedor já cadastrado >>>\n");
                printf("\n");
                continue;
            }
        }

        if (valida_cnpj(fornecedor->cnpj))
        {
            cnpj_valido = 1;
        }
        else
        {
            printf("\n");
            printf("<<< cnpj invalido, tente novamente >>>\n");
            printf("\n");
        }

    } while (!cnpj_valido || (cnpj_exite && !editando));

    do
    {
        printf("Digite a cidade do fornecedor: ");
        scanf(" %[^\n]", fornecedor->cidade);
        limpa_buffer();
    } while (!valida_nome(fornecedor->nome));

    do
    {
        printf("Digite a Unidade Federativa do fornecedor(Ex: RN, SP, RJ): ");
        scanf(" %[^\n]", fornecedor->estado);
        limpa_buffer();
    } while (!valida_nome(fornecedor->nome));

    do
    {
        printf("Digite o CEP do fornecedor: ");
        scanf(" %[^\n]", fornecedor->cep);
        limpa_buffer();
    } while (!valida_cep(fornecedor->cep));

    do
    {
        printf("Digite o telefone do fornecedor: ");
        scanf(" %[^\n]", fornecedor->telefone);
        limpa_buffer();
    } while (!valida_telefone(fornecedor->telefone));

    do
    {
        printf("Digite o email do fornecedor: ");
        scanf(" %[^\n]", fornecedor->email);
        limpa_buffer();
    } while (!valida_email(fornecedor->email));

    fornecedor->status = 1;

    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
    return fornecedor;
}

// função que pesquisa um fornecedor ou pelo nome ou pelo cnpj - code 2
Fornecedores *tela_pesquisa_fornecedor(void)
{
    char cnpj_pesquisa[15];
    char nome_pesquisa[51];
    int opt_pesquisa;
    Fornecedores *fornecedor = (Fornecedores *)malloc(sizeof(Fornecedores));
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Pesquisar Clientes = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("Escolha o metodo de pesquisa:\n");
    printf("1 - Por CNPJ\n");
    printf("2 - Por Nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opt_pesquisa);
    limpa_buffer();

    FILE *fp = fopen("fornecedores.dat", "rb");
    if (fp == NULL)
    {
        printf("O programa ainda nao possui fornecedores cadastrados\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        free(fornecedor);
        return NULL;
    }

    int possui_fornecedor = 0;

    if (opt_pesquisa == 1)
    {
        printf("Informe o CNPJ do fornecedor: ");
        scanf(" %21s", cnpj_pesquisa);
        limpa_buffer();
        if (!valida_cnpj(cnpj_pesquisa))
        {
            printf("CNPJ invalido!\n");
        }
        else
        {
            while (fread(fornecedor, sizeof(Fornecedores), 1, fp))
            {
                if ((fornecedor->status == 1) && (strcmp(fornecedor->cnpj, cnpj_pesquisa) == 0))
                {
                    exibe_fornecedor(fornecedor);
                    possui_fornecedor = 1;
                }
            }
        }
    }
    else if (opt_pesquisa == 2)
    {
        printf("Informe o nome do fornecedor: ");
        scanf(" %[^\n]", nome_pesquisa);
        limpa_buffer();
        while (fread(fornecedor, sizeof(Fornecedores), 1, fp))
        {
            if ((fornecedor->status == 1) && (strstr(fornecedor->nome, nome_pesquisa) != NULL))
            {
                exibe_fornecedor(fornecedor);
                possui_fornecedor = 1;
            }
        }
    }
    else
    {
        printf("Opção de pesquisa invalida!\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }

    fclose(fp);

    if (!possui_fornecedor)
    {
        printf("\nNenhum fornecedor encontrado.\n");
        printf("\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        return NULL;
    }

    printf("\nTecle <ENTER> para continuar.\n");
    getchar();

    return NULL;
}

// função que faz a edicao de um fornecedor - code 3
void tela_edita_fornecedor(void)
{
    Fornecedores *fornecedor;
    char *cnpj_pesquisa = (char *)malloc(26 * sizeof(char));

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Editar Fornecedores = = = = =                  *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    do
    {
        printf("Informe o CNPJ do cliente que deseja editar: ");
        scanf(" %[^\n]", cnpj_pesquisa);
        limpa_buffer();
    } while (!valida_cnpj(cnpj_pesquisa));

    fornecedor = busca_cnpj_fornecedor(cnpj_pesquisa);

    if (fornecedor == NULL)
    {
        printf("\n");
        printf("<<< Nenhum fornecedor encontrado >>>\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }
    else
    {
        char opt;
        int valida_opt = 0;

        exibe_fornecedor(fornecedor);

        while (!valida_opt)
        {
            printf("Deseja realmente editar este fornecedor? (S/N): ");
            scanf(" %c", &opt);
            limpa_buffer();

            if (opt == 'S' || opt == 's')
            {
                valida_opt = 1;
                fornecedor = tela_cadastra_fornecedor(1);
                regrava_fornecedor(fornecedor);
                free(fornecedor);
            }
            else if (opt == 'N' || opt == 'n')
            {
                valida_opt = 1;
                printf("<<< Edicao Cancelada >>>\n");
                printf("<<< Tecle <ENTER> para continuar >>>\n");
                getchar();
                free(fornecedor);
                return;
            }
            else
            {
                printf("Resposta invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n");
            }
        }
    }

    free(cnpj_pesquisa);
}

// função que irá excluir o fornecedor do arquivo - code 4
void tela_excluir_fornecedor(void)
{
    int possui_cliente = 0;
    long posicao;
    Fornecedores *fornecedor = (Fornecedores *)malloc(sizeof(Fornecedores));
    char cnpj_pesquisa[15];

    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Excluir Fornecedor = = = = =                   *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    do
    {
        printf("Informe o CNPJ do cliente que deseja excluir: ");
        scanf(" %[^\n]", cnpj_pesquisa);
        limpa_buffer();
    } while (!valida_cnpj(cnpj_pesquisa));

    FILE *fp = fopen("fornecedores.dat", "r+b");
    if (fp == NULL)
    {
        printf("O programa ainda nao possui fornecedores cadastrados\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        return;
    }

    while (fread(fornecedor, sizeof(Fornecedores), 1, fp))
    {
        if (strcmp(fornecedor->cnpj, cnpj_pesquisa) == 0 && fornecedor->status == 1)
        {
            possui_cliente = 1;
            posicao = ftell(fp) - sizeof(Fornecedores);
            break;
        }
    }

    if (!possui_cliente)
    {
        printf("\nNenhum fornecedor ativo encontrado com esse CPF.\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }
    else
    {
        char opt;
        int valida_opt = 0;

        exibe_fornecedor(fornecedor);

        while (!valida_opt)
        {
            printf("Deseja realmente excluir este fornecedor? (S/N): ");
            scanf(" %c", &opt);
            limpa_buffer();

            if (opt == 'S' || opt == 's')
            {
                valida_opt = 1;
                fseek(fp, posicao, SEEK_SET);
                fornecedor->status = 0;
                fwrite(&fornecedor, sizeof(Fornecedores), 1, fp);
                printf("\nFornecedor excluido com sucesso.\n");
            }
            else if (opt == 'N' || opt == 'n')
            {
                valida_opt = 1;
                printf("<<< Exclusao Cancelada >>>\n");
                printf("<<< Tecle <ENTER> para continuar >>>\n");
                getchar();
                free(fornecedor);
                return;
            }
            else
            {
                printf("Resposta invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n");
            }
        }
    }

    fclose(fp);
    free(fornecedor);
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
}
// função que exibe na tela todos os fornecedores - code 5
void tela_listar_fornecedor(void)
{
    int possui_fornecedor = 0;
    Fornecedores *fornecedor = (Fornecedores *)malloc(sizeof(Fornecedores));
    if (fornecedor == NULL)
    {
        perror("Erro na alocação de memória");
        return;
    }
    system("clear||cls");
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                   = = = = = Lista de Fornecedores = = = = =                *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");

    FILE *fp = fopen("fornecedores.dat", "rb");
    if (fp == NULL)
    {
        printf("O programa ainda nao possui fornecedores cadastrados\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
        free(fornecedor);
        return;
    }

    // função que irá ler os fornecedors que estão no arquivo
    while (fread(fornecedor, sizeof(Fornecedores), 1, fp))
    {
        if (fornecedor->status == 1)
        {
            exibe_fornecedor(fornecedor);
            possui_fornecedor = 1;
        }
    }

    // se não possuir nenhum fornecedor no arquivo
    if (!possui_fornecedor)
    {
        printf("\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }

    // liberando a memória alocada
    free(fornecedor);
    // fechando o arquivo
    fclose(fp);
    limpa_buffer();
    // esperando confirmação do usuário
    printf("\n");
    printf("<<< Tecle <ENTER> para continuar >>>\n");
    getchar();
}

/////////////////////////////////////////////////////////////////////////////
// funções auxiliares
void grava_fornecedor(Fornecedores *fornecedor)
{
    FILE *fp = fopen("fornecedores.dat", "ab");
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo");
        return;
    }
    fwrite(fornecedor, sizeof(Fornecedores), 1, fp);
    fclose(fp);
}
// estrutura que será exibida quando for verificado os fornecedores em lista
void exibe_fornecedor(Fornecedores *fornecedor)
{
    printf("********* Dados do Fornecedor *********\n");
    printf("Nome: %s\n", fornecedor->nome);
    printf("Cnpj: %s\n", fornecedor->cnpj);
    printf("Cidade: %s\n", fornecedor->cidade);
    printf("Estado: %s\n", fornecedor->estado);
    printf("Endereco: %s\n", fornecedor->cep);
    printf("Telefone: %s\n", fornecedor->telefone);
    printf("Email: %s\n", fornecedor->email);
    printf("Status: %s\n", fornecedor->status == 1 ? "\033[0;32mATIVO\033[0m\n" : "\033[0;31mINATIVO\033[0m\n");
    printf("************************************\n");
}
// estrutura que substitui o fornecedor original pelo editado
void regrava_fornecedor(Fornecedores *fornecedor)
{
    Fornecedores fornecedor_lido;
    FILE *fp = fopen("fornecedores.dat", "r+b");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return;
    }

    int possui_fornecedor = 0;
    // Busca o fornecedor pelo CNPJ no arquivo
    while (fread(&fornecedor_lido, sizeof(Fornecedores), 1, fp) == 1)
    { // Verifica se um registro foi lido
        if (strcmp(fornecedor_lido.cnpj, fornecedor->cnpj) == 0)
        {
            possui_fornecedor = 1;
            // Move o ponteiro para trás do tamanho de um Fornecedore
            if (fseek(fp, -1 * sizeof(Fornecedores), SEEK_CUR) != 0)
            {
                perror("Erro ao posicionar o ponteiro do arquivo");
                break; // Se fseek falhar, saia do loop
            }
            fwrite(fornecedor, sizeof(Fornecedores), 1, fp);
            break;
        }
    }

    if (!possui_fornecedor)
    {
        printf("\nCliente não encontrado!\n");
        printf("<<< Tecle <ENTER> para continuar >>>\n");
        getchar();
    }

    fclose(fp); // Fecha o arquivo após o uso
}
// estrutura que busca o fornecedor pelo cnpj
Fornecedores *busca_cnpj_fornecedor(const char *cnpj)
{
    // Alocando a memória
    Fornecedores *fornecedor = (Fornecedores *)malloc(sizeof(Fornecedores));
    if (fornecedor == NULL)
    {
        perror("Erro na alocação de memória");
        return NULL;
    }

    // Abrindo o arquivo
    FILE *fp = fopen("fornecedores.dat", "rb");
    if (fp == NULL)
    {
        printf("Nenhum fornecedor foi cadastrado ainda");
        free(fornecedor); // Não esqueça de liberar a memória alocada em caso de falha
        return NULL;
    }

    // Lendo os fornecedores que estão no arquivo
    while (fread(fornecedor, sizeof(Fornecedores), 1, fp))
    {
        if (strcmp(fornecedor->cnpj, cnpj) == 0 && fornecedor->status == 1)
        {
            // Fechando o arquivo
            fclose(fp);
            // Retorna o fornecedor encontrado
            return fornecedor;
        }
    }

    // Fechando o arquivo
    fclose(fp);
    // Liberando a memória alocada caso não encontre o fornecedor
    free(fornecedor);
    return NULL;
}
