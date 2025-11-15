#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Contadores de comparação
long compSequencial = 0;
long compBinaria = 0;

// ======== STRUCTS ========

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;


Item mochilaVetor[MAX];
int vetorTamanho = 0;

// Inserção no vetor
void inserirItemVetor(Item item) {
    if (vetorTamanho >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }
    mochilaVetor[vetorTamanho] = item;
    vetorTamanho++;
}

// Remoção por nome
void removerItemVetor(char nome[]) {
    for (int i = 0; i < vetorTamanho; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < vetorTamanho-1; j++) {
                mochilaVetor[j] = mochilaVetor[j+1];
            }
            vetorTamanho--;
            printf("Item removido com sucesso.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Listagem
void listarVetor() {
    printf("\n--- ITENS NO VETOR ---\n");
    for (int i = 0; i < vetorTamanho; i++) {
        printf("%s | %s | %d\n",
            mochilaVetor[i].nome,
            mochilaVetor[i].tipo,
            mochilaVetor[i].quantidade
        );
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(char nome[]) {
    compSequencial = 0;
    for (int i = 0; i < vetorTamanho; i++) {
        compSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenação (bubble sort)
void ordenarVetor() {
    for (int i = 0; i < vetorTamanho - 1; i++) {
        for (int j = 0; j < vetorTamanho - 1 - i; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome!\n");
}

// Busca binária
int buscarBinariaVetor(char nome[]) {
    compBinaria = 0;

    int inicio = 0;
    int fim = vetorTamanho - 1;

    while (inicio <= fim) {
        compBinaria++;
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    return -1;
}

No* listaInicio = NULL;

// Inserção na lista
void inserirItemLista(Item item) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = listaInicio;
    listaInicio = novo;
}

// Remoção por nome
void removerItemLista(char nome[]) {
    No *atual = listaInicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                listaInicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

// Listagem
void listarLista() {
    No *aux = listaInicio;
    printf("\n--- ITENS NA LISTA ---\n");
    while (aux != NULL) {
        printf("%s | %s | %d\n",
            aux->dados.nome,
            aux->dados.tipo,
            aux->dados.quantidade
        );
        aux = aux->proximo;
    }
}

// Busca sequencial na lista
No* buscarSequencialLista(char nome[]) {
    compSequencial = 0;
    No *aux = listaInicio;

    while (aux != NULL) {
        compSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}


Item criarItem() {
    Item i;
    printf("Nome: ");
    scanf(" %[^\n]", i.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", i.tipo);
    printf("Quantidade: ");
    scanf("%d", &i.quantidade);
    return i;
}

void menuVetor() {
    int op;
    char nome[30];

    do {
        printf("\n=== MOCHILA (VETOR) ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                inserirItemVetor(criarItem());
                break;

            case 2:
                printf("Nome do item para remover: ");
                scanf(" %[^\n]", nome);
                removerItemVetor(nome);
                break;

            case 3:
                listarVetor();
                break;

            case 4:
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nome);
                int pos;
                pos = buscarSequencialVetor(nome);
                if (pos >= 0)
                    printf("Encontrado! Comparacoes = %ld\n", compSequencial);
                else
                    printf("Nao encontrado. Comparacoes = %ld\n", compSequencial);
                break;

            case 5:
                ordenarVetor();
                break;

            case 6:
                printf("Nome para busca binaria: ");
                scanf(" %[^\n]", nome);
                pos = buscarBinariaVetor(nome);
                if (pos >= 0)
                    printf("Encontrado! Comparacoes = %ld\n", compBinaria);
                else
                    printf("Nao encontrado. Comparacoes = %ld\n", compBinaria);
                break;
        }
    } while (op != 0);
}

void menuLista() {
    int op;
    char nome[30];

    do {
        printf("\n=== MOCHILA (LISTA ENCADEADA) ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                inserirItemLista(criarItem());
                break;

            case 2:
                printf("Nome do item para remover: ");
                scanf(" %[^\n]", nome);
                removerItemLista(nome);
                break;

            case 3:
                listarLista();
                break;

            case 4: {
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nome);
                No* r = buscarSequencialLista(nome);
                if (r != NULL)
                    printf("Encontrado! Comparacoes = %ld\n", compSequencial);
                else
                    printf("Nao encontrado. Comparacoes = %ld\n", compSequencial);
                break;
            }
        }
    } while (op != 0);
}

int main() {

    int escolha;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1 - Usar mochila com vetor\n");
        printf("2 - Usar mochila com lista encadeada\n");
        printf("0 - Sair\n");
        scanf("%d", &escolha);

        if (escolha == 1)
            menuVetor();
        else if (escolha == 2)
            menuLista();

    } while (escolha != 0);

    return 0;
}
