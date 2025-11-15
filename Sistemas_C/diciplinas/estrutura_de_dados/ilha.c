#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// =============================
// Estrutura principal do item
// =============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens (mochila)
Item mochila[MAX_ITENS];
int totalItens = 0; // contador de itens atuais

// =============================
// Funções principais do sistema
// =============================

// Função para inserir um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n=== Cadastro de Novo Item ===\n");
    printf("Nome do item: ");
    scanf(" %29[^\n]", novoItem.nome); // lê até 29 caracteres ou até nova linha

    printf("Tipo do item (arma, munição, cura, etc): ");
    scanf(" %19[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n Item adicionado com sucesso!\n");
}

// Função para remover item por nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // move os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n Item '%s' removido com sucesso!\n", nomeBusca);
            return;
        }
    }

    printf("\n Item não encontrado.\n");
}

// Função para listar todos os itens
void listarItens() {
    printf("\n=== Itens na Mochila ===\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função de busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            return;
        }
    }

    printf("\n Item '%s' não encontrado.\n", nomeBusca);
}

// =============================
// Função principal (menu)
// =============================
int main() {
    int opcao;

    do {
        printf("\n========== Sistema de Inventário ==========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n Saindo do sistema... Até a próxima aventura!\n");
                break;
            default:
                printf("\n Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
