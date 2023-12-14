// menus.c
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../modules/util.h"
#include "../modules/relatorio.h"
#include "../modules/fornecedor.h"
#include "../modules/produto.h"
#include "../modules/cliente.h"

int pegarMenuEscolha()
{
    char op;
    op = controlarMenu();
    return op;
}

void mostrarMenuBanner()
{
    printf("*****************************************************************************\n");
    printf("*      ___                                  _                               *\n");
    printf("*     |_ _|  _ __   __   __   ___   _ __   | |_    ___    _ __   _   _      *\n");
    printf("*      | |  | '_ \\  \\ \\ / /  / _ \\ | '_ \\  | __|  / _ \\  | '__| | | | |     *\n");
    printf("*      | |  | | | |  \\ V /  |  __/ | | | | | |_  | (_) | | |    | |_| |     *\n");
    printf("*     |___| |_| |_|   \\_/    \\___| |_| |_|  \\__|  \\___/  |_|     \\__, |     *\n");
    printf("*                                                                |___/      *\n");
    printf("*                                                                           *\n");
}

void mostrarMenuInicial()
{
    limparTela();
    mostrarMenuBanner();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Sistema de Estoque = = = = =                   *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Gerir Estoque                                                          *\n");
    printf("* 2. Sobre o Projeto                                                        *\n");
    printf("* 0. Sair                                                                   *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuPrincipal()
{
    limparTela();
    mostrarMenuBanner();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Sistema de Estoque = = = = =                   *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Relatórios                                                             *\n");
    printf("* 2. Fornecedores                                                           *\n");
    printf("* 3. Produtos                                                               *\n");
    printf("* 4. Clientes                                                               *\n");
    printf("* 0. Voltar                                                                 *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuRelatorio()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                      = = = = = Relatorios = = = = =                       *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Relatorio Todos Fornecedores                                           *\n");
    printf("* 2. Relatorio Fornecedores Inativos                                        *\n");
    printf("* 3. Relatorio Fornecedores Ordem Alfabetica                                *\n");
    printf("* 4. Relatorio Todos os Produtos                                            *\n");
    printf("* 5. Relatorio Produtos Inativos                                            *\n");
    printf("* 6. Relatorio Produtos Ordem Alfabetica                                    *\n");
    printf("* 7. Relatorio Todos Clientes                                               *\n");
    printf("* 8. Relatorio Clientes Inativos                                           *\n");
    printf("* 9. Relatorio Clientes Ordem Alfabetica                                   *\n");
    printf("* 0. Voltar                                                                 *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuFornecedor()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                     = = = = = Fornecedores = = = = =                      *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Cadastrar Fornecedor                                                   *\n");
    printf("* 2. Pesquisar Fornecedor                                                   *\n");
    printf("* 3. Editar Fornecedor                                                      *\n");
    printf("* 4. Excluir Fornecedor                                                     *\n");
    printf("* 0. Voltar                                                                 *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuProdutos()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                       = = = = = Produtos = = = = =                        *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Cadastrar Produto                                                      *\n");
    printf("* 2. Pesquisar Produto                                                      *\n");
    printf("* 3. Editar Produto                                                         *\n");
    printf("* 4. Excluir Produto                                                        *\n");
    printf("* 0. Voltar                                                                 *\n");
    printf("*****************************************************************************\n");
}

void menuPrincipal()
{
    char opcao;
    do
    {
        mostrarMenuPrincipal();
        opcao = pegarMenuEscolha();

        switch (opcao)
        {
        case '1':
            moduloRelatorio();
            break;
        case '2':
            moduloFornecedor();
            break;
        case '3':
            moduloProduto();
            break;
        case '4':
            moduloCliente();
            break;
        case '0':
            printf("Voltando ao menu principal\n");
            break;
        default:
            printf("Escolha invalida, tente novamente");
        }
    } while (opcao != '0');
}

void mostrarMenuCadastroFornecedor()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                = = = = = Cadastro de Fornecedor = = = = =                 *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuPesquisaFornecedor()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                = = = = = Pesquisa de Fornecedor = = = = =                 *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuEditarFornecedor()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                 = = = = = Editar de Fornecedor = = = = =                  *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuExcluirFornecedor()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                 = = = = = Excluir de Fornecedor = = = = =                 *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuCadastroProduto()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Cadastro de Produto = = = = =                  *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuPesquisaProduto()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                = = = = = Pesquisa de Fornecedor = = = = =                 *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuEditarProduto()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Editar de Produto = = = = =                    *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuExcluirProduto()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                    = = = = = Excluir Produto = = = = =                    *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuCliente()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                        = = = = = Cliente = = = = =                        *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
    printf("* 1. Cadastrar Cliente                                                      *\n");
    printf("* 2. Pesquisar Cliente                                                      *\n");
    printf("* 3. Editar Cliente                                                         *\n");
    printf("* 4. Excluir Cliente                                                        *\n");
    printf("* 0. Voltar                                                                 *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuCadastroCliente()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                 = = = = = Cadastro de Cliente = = = = =                   *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuPesquisaCliente()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Pesquisa de Cliente = = = = =                  *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuEditarCliente()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Editar de Cliente = = = = =                    *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}

void mostrarMenuExcluirCliente()
{
    limparTela();
    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                  = = = = = Excluir de Cliente = = = = =                   *\n");
    printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
}