#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5       // Tamanho fixo da fila de peças futuras
#define TAM_PILHA 3      // Capacidade máxima da pilha de reserva

// -------------------------------
// Estrutura de uma peça do jogo
// -------------------------------
typedef struct {
    char tipo;   // Tipo da peça ('I', 'O', 'T', 'L')
    int id;      // Identificador único
} Peca;

// -------------------------------
// Estruturas da Fila Circular
// -------------------------------
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

// -------------------------------
// Estrutura da Pilha Linear
// -------------------------------
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// -------------------------------
// Protótipos das funções
// -------------------------------
void inicializarFila(Fila *fila);
void inicializarPilha(Pilha *pilha);
Peca gerarPeca();
void enfileirar(Fila *fila, Peca p);
Peca desenfileirar(Fila *fila);
void empilhar(Pilha *pilha, Peca p);
Peca desempilhar(Pilha *pilha);
int filaCheia(Fila *fila);
int filaVazia(Fila *fila);
int pilhaCheia(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void exibirEstado(Fila fila, Pilha pilha);

// -------------------------------
// Variável global para gerar IDs únicos
// -------------------------------
int contador_id = 0;

// -------------------------------
// Função principal
// -------------------------------
int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    
    srand(time(NULL)); // Semente para gerar tipos aleatórios

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }

    do {
        printf("\n===== ESTADO ATUAL =====\n");
        exibirEstado(fila, pilha);

        printf("\n===== OPÇÕES DE AÇÃO =====\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = desenfileirar(&fila);
                    printf("Você jogou a peça [%c %d]\n", jogada.tipo, jogada.id);
                    // Após jogar, gera uma nova peça e adiciona ao final da fila
                    enfileirar(&fila, gerarPeca());
                } else {
                    printf("A fila está vazia!\n");
                }
                break;
            }

            case 2: {
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca reservada = desenfileirar(&fila);
                        empilhar(&pilha, reservada);
                        printf("Você reservou a peça [%c %d]\n", reservada.tipo, reservada.id);
                        // Reposição automática da fila
                        enfileirar(&fila, gerarPeca());
                    } else {
                        printf("A pilha de reserva está cheia!\n");
                    }
                } else {
                    printf("A fila está vazia!\n");
                }
                break;
            }

            case 3: {
                if (!pilhaVazia(&pilha)) {
                    Peca usada = desempilhar(&pilha);
                    printf("Você usou a peça reservada [%c %d]\n", usada.tipo, usada.id);
                } else {
                    printf("A pilha de reserva está vazia!\n");
                }
                break;
            }

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// -------------------------------
// Implementação das funções
// -------------------------------

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->qtd = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int filaCheia(Fila *fila) {
    return fila->qtd == TAM_FILA;
}

int filaVazia(Fila *fila) {
    return fila->qtd == 0;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void enfileirar(Fila *fila, Peca p) {
    if (!filaCheia(fila)) {
        fila->pecas[fila->fim] = p;
        fila->fim = (fila->fim + 1) % TAM_FILA;
        fila->qtd++;
    }
}

Peca desenfileirar(Fila *fila) {
    Peca p = {'?', -1};
    if (!filaVazia(fila)) {
        p = fila->pecas[fila->inicio];
        fila->inicio = (fila->inicio + 1) % TAM_FILA;
        fila->qtd--;
    }
    return p;
}

void empilhar(Pilha *pilha, Peca p) {
    if (!pilhaCheia(pilha)) {
        pilha->pecas[++pilha->topo] = p;
    }
}

Peca desempilhar(Pilha *pilha) {
    Peca p = {'?', -1};
    if (!pilhaVazia(pilha)) {
        p = pilha->pecas[pilha->topo--];
    }
    return p;
}

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = contador_id++;
    return nova;
}

void exibirEstado(Fila fila, Pilha pilha) {
    printf("Fila de peças:\t");
    int i = fila.inicio;
    for (int j = 0; j < fila.qtd; j++) {
        printf("[%c %d] ", fila.pecas[i].tipo, fila.pecas[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    for (int j = pilha.topo; j >= 0; j--) {
        printf("[%c %d] ", pilha.pecas[j].tipo, pilha.pecas[j].id);
    }
    printf("\n");
}
