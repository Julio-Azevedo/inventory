#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Assinaturas
char painelPrincipal(void);
void listarItensEstoque();
void listarItensEstoque();
void adicionarItemEstoque();
void removerItemEstoque();
void listarFornecedores();
void adicionarFornecedor();
void atualizarFornecedor();
void removerFornecedor();

// Painel principal de usuário
void painelUsuario(void) {
    char opcao;
    do {
        opcao = painelPrincipal();
        switch(opcao) {
        case '1':
            break;
        case '2':
            break;
        default:
            break;
        }
    } while (opcao != '0');
}

char painelPrincipal(void) {
    char op;
    system("clear||cls");
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = Bem-vindo ao inventory = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Estoque                                                   ///\n");
    printf("///            2. Fornecedores                                              ///\n");
    printf("///            3. Relatório de entrada                                      ///\n");
    printf("///            4. Relatórios de saída                                       ///\n");
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

// Estrutura para representar um item no estoque
typedef struct {
    char nome[50];
    int quantidade;
    float preco;
} ItemEstoque;

// Array para armazenar os itens de estoque
ItemEstoque estoque[999]; // Supondo um máximo de 100 itens

int numItensEstoque = 0; // Número atual de itens no estoque

// Modulo de Estoque
void moduloEstoque() {
    int estoqueopt;
    do {
        printf("=== Módulo Item de Estoque ===\n");
        printf("1. Listar Itens\n");
        printf("2. Adicionar Item\n");
        printf("3. Atualizar Item\n");
        printf("4. Remover Item\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &estoqueopt);

        switch (estoqueopt) {
            case 1:
                listarItensEstoque();
                break;
            case 2:
                adicionarItemEstoque();
                break;
            case 3:
                atualizarItemEstoque();
                break;
            case 4:
                removerItemEstoque();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (estoqueopt != 0);
}

void listarItensEstoque() {
    if (numItensEstoque == 0) {
        printf("O estoque está vazio.\n");
        return;
    }

    printf("Itens no estoque:\n");
    for (int i = 0; i < numItensEstoque; i++) {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", estoque[i].nome);
        printf("Quantidade: %d\n", estoque[i].quantidade);
        printf("Preço: %.2f\n", estoque[i].preco);
        printf("\n");
    }
}

void adicionarItemEstoque() {
    if (numItensEstoque == 100) {
        printf("O estoque está cheio. Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    scanf("%s", estoque[numItensEstoque].nome);
    printf("Digite a quantidade: ");
    scanf("%d", &estoque[numItensEstoque].quantidade);
    printf("Digite o preço: ");
    scanf("%f", &estoque[numItensEstoque].preco);

    numItensEstoque++;
    printf("Item adicionado com sucesso!\n");
}

void atualizarItemEstoque() {
    if (numItensEstoque == 0) {
        printf("O estoque está vazio.\n");
        return;
    }

    printf("Digite o número do item que deseja atualizar: ");
    int numeroItem;
    scanf("%d", &numeroItem);

    if (numeroItem < 1 || numeroItem > numItensEstoque) {
        printf("Número de item inválido. Tente novamente.\n");
        return;
    }

    printf("Digite o novo nome do item: ");
    scanf("%s", estoque[numeroItem - 1].nome);
    printf("Digite a nova quantidade: ");
    scanf("%d", &estoque[numeroItem - 1].quantidade);
    printf("Digite o novo preço: ");
    scanf("%f", &estoque[numeroItem - 1].preco);

    printf("Item atualizado com sucesso!\n");
}

void removerItemEstoque() {
    if (numItensEstoque == 0) {
        printf("O estoque está vazio.\n");
        return;
    }

    printf("Digite o número do item que deseja remover: ");
    int numeroItem;
    scanf("%d", &numeroItem);

    if (numeroItem < 1 || numeroItem > numItensEstoque) {
        printf("Número de item inválido. Tente novamente.\n");
        return;
    }

    for (int i = numeroItem - 1; i < numItensEstoque - 1; i++) {
        // Move os itens seguintes uma posição para trás no array para preencher a lacuna
        estoque[i] = estoque[i + 1];
    }

    numItensEstoque--;
    printf("Item removido com sucesso!\n");
}

// Fim da Parte de Estoque

///////////////////////////////////////////////////////////////////////////////////////////////////

// Inicio do módulo de fornecedores
typedef struct {
    char nome[50];
    char contato[50];
    char email[50];
} Fornecedor;

// Array para armazenar os fornecedores
Fornecedor fornecedores[100]; // Supondo um máximo de 100 fornecedores

int numFornecedores = 0; // Número atual de fornecedores

void moduloFornecedores() {
    int opcao;
    do {
        printf("=== Módulo de Fornecedores ===\n");
        printf("1. Listar Fornecedores\n");
        printf("2. Adicionar Fornecedor\n");
        printf("3. Atualizar Fornecedor\n");
        printf("4. Remover Fornecedor\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarFornecedores();
                break;
            case 2:
                adicionarFornecedor();
                break;
            case 3:
                atualizarFornecedor();
                break;
            case 4:
                removerFornecedor();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void listarFornecedores() {
    if (numFornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Fornecedores cadastrados:\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("Fornecedor %d:\n", i + 1);
        printf("Nome: %s\n", fornecedores[i].nome);
        printf("Contato: %s\n", fornecedores[i].contato);
        printf("Email: %s\n", fornecedores[i].email);
        printf("\n");
    }
}

void adicionarFornecedor() {
    if (numFornecedores == 100) {
        printf("O número máximo de fornecedores foi atingido.\n");
        return;
    }

    printf("Digite o nome do fornecedor: ");
    scanf("%s", fornecedores[numFornecedores].nome);
    printf("Digite o contato: ");
    scanf("%s", fornecedores[numFornecedores].contato);
    printf("Digite o email: ");
    scanf("%s", fornecedores[numFornecedores].email);

    numFornecedores++;
    printf("Fornecedor adicionado com sucesso!\n");
}

void atualizarFornecedor() {
    if (numFornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Digite o número do fornecedor que deseja atualizar: ");
    int numeroFornecedor;
    scanf("%d", &numeroFornecedor);

    if (numeroFornecedor < 1 || numeroFornecedor > numFornecedores) {
        printf("Número de fornecedor inválido. Tente novamente.\n");
        return;
    }

    printf("Digite o novo nome do fornecedor: ");
    scanf("%s", fornecedores[numeroFornecedor - 1].nome);
    printf("Digite o novo contato: ");
    scanf("%s", fornecedores[numeroFornecedor - 1].contato);
    printf("Digite o novo email: ");
    scanf("%s", fornecedores[numeroFornecedor - 1].email);

    printf("Fornecedor atualizado com sucesso!\n");
}

void removerFornecedor() {
    if (numFornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Digite o número do fornecedor que deseja remover: ");
    int numeroFornecedor;
    scanf("%d", &numeroFornecedor);

    if (numeroFornecedor < 1 || numeroFornecedor > numFornecedores) {
        printf("Número de fornecedor inválido. Tente novamente.\n");
        return;
    }

    for (int i = numeroFornecedor - 1; i < numFornecedores - 1; i++) {
        // Move os fornecedores seguintes uma posição para trás no array para preencher a lacuna
        fornecedores[i] = fornecedores[i + 1];
    }

    numFornecedores--;
    printf("Fornecedor removido com sucesso!\n");
}

// Fim do módulo de fornecedores

///////////////////////////////////////////////////////////////////////////////////////////////////

// Inicio do módulo de Compras
