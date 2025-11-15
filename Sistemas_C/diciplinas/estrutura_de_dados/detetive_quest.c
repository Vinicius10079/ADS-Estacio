/*
 Detective Quest - Sistema de coleta de pistas
 Implementação em C conforme requisitos:
 - Árvore binária fixa representa o mapa da mansão (cada sala tem nome e pista opcional)
 - BST armazena as pistas coletadas (ordenadas alfabeticamente)
 - Navegação a partir do "Hall de Entrada": esquerda (e), direita (d), sair (s)
 - Ao entrar em uma sala, a pista (se existir) é automaticamente inserida na BST
 - Ao final, exibe todas as pistas coletadas em ordem alfabética

 Autor: Enigma Studios (exemplo)
 Data: 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---- Estruturas ---- */

/* Estrutura que representa uma sala do mapa (árvore binária) */
typedef struct Sala {
    char *nome;           /* nome da sala */
    char *pista;          /* pista opcional (NULL se não houver) */
    struct Sala *esq;     /* caminho à esquerda */
    struct Sala *dir;     /* caminho à direita */
} Sala;

/* Nó da BST que armazena pistas coletadas */
typedef struct PistaNode {
    char *pista;
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

/* ---- Funções utilitárias ---- */

/* strdup portável: duplica string em memória alocada */
char *strdup_port(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) {
        fprintf(stderr, "Erro de alocação de memória em strdup_port\n");
        exit(EXIT_FAILURE);
    }
    memcpy(p, s, n);
    return p;
}

/* Função que converte string para uma nova string "lowercase" para comparação
   opcional (não usaremos para exibir; apenas para comparação se desejar case-insensitive).
   Para este programa usamos comparação case-sensitive simples com strcmp() conforme solicitado.
*/

/* ---- Funções principais (documentadas) ---- */

/*
 criarSala()
 Cria dinamicamente uma sala com nome e pista opcionais.
 - nome: nome da sala (string)
 - pista: conteúdo da pista (string) ou NULL se não houver pista
 Retorna: ponteiro para Sala alocada
*/
Sala *criarSala(const char *nome, const char *pista) {
    Sala *s = (Sala *)malloc(sizeof(Sala));
    if (!s) {
        fprintf(stderr, "Erro de memória ao criar sala\n");
        exit(EXIT_FAILURE);
    }
    s->nome = strdup_port(nome);
    s->pista = (pista ? strdup_port(pista) : NULL);
    s->esq = s->dir = NULL;
    return s;
}

/*
 inserirPista()
 Insere uma nova pista na árvore de pistas (BST) de forma ordenada.
 Evita inserir pistas duplicadas (comparação por strcmp).
  rootPtr: ponteiro para o ponteiro raiz da BST
  novaPista: string da pista a ser inserida (copiada internamente)
*/
void inserirPista(PistaNode **rootPtr, const char *novaPista) {
    if (!novaPista || strlen(novaPista) == 0) return; /* nada a inserir */

    if (*rootPtr == NULL) {
        PistaNode *n = (PistaNode *)malloc(sizeof(PistaNode));
        if (!n) {
            fprintf(stderr, "Erro de memória ao inserir pista\n");
            exit(EXIT_FAILURE);
        }
        n->pista = strdup_port(novaPista);
        n->esq = n->dir = NULL;
        *rootPtr = n;
        printf("Pista coletada e adicionada: \"%s\"\n", novaPista);
        return;
    }

    int cmp = strcmp(novaPista, (*rootPtr)->pista);
    if (cmp == 0) {
        /* já coletada */
        printf("Pista já coletada anteriormente: \"%s\" (ignorando)\n", novaPista);
        return;
    } else if (cmp < 0) {
        inserirPista(&((*rootPtr)->esq), novaPista);
    } else {
        inserirPista(&((*rootPtr)->dir), novaPista);
    }
}

/*
 explorarSalasComPistas()
 Controla a navegação entre salas e coleta automática de pistas.
 A cada entrada em uma sala, se houver pista, ela é inserida na BST de pistas.
 - atual: sala inicial (ex: Hall de Entrada)
 - rootPistas: ponteiro para a raiz da BST de pistas (será modificada)
*/
void explorarSalasComPistas(Sala *atual, PistaNode **rootPistas) {
    char opcao[16];

    printf("Iniciando exploração a partir de: %s\n", atual->nome);
    /* Ao entrar na sala inicial, coletar pista se houver */
    if (atual->pista) inserirPista(rootPistas, atual->pista);

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        if (atual->pista) {
            printf("Pista nesta sala: \"%s\"\n", atual->pista);
        } else {
            printf("Nenhuma pista visível nesta sala.\n");
        }
        printf("Opções: (e) esquerda  (d) direita  (s) sair\n");
        printf("Escolha: ");
        if (!fgets(opcao, sizeof(opcao), stdin)) {
            /* leitura falhou, sair */
            printf("\nEntrada encerrada. Saindo da exploração.\n");
            break;
        }

        /* pegar apenas a primeira letra non-space */
        char cmd = 0;
        for (size_t i = 0; i < strlen(opcao); ++i) {
            if (!isspace((unsigned char)opcao[i])) {
                cmd = opcao[i];
                break;
            }
        }
        if (cmd == 0) continue;

        if (cmd == 's' || cmd == 'S') {
            printf("Você optou por sair da exploração.\n");
            break;
        } else if (cmd == 'e' || cmd == 'E') {
            if (atual->esq) {
                atual = atual->esq;
                if (atual->pista) inserirPista(rootPistas, atual->pista);
            } else {
                printf("Não há sala à esquerda. Escolha outra opção.\n");
            }
        } else if (cmd == 'd' || cmd == 'D') {
            if (atual->dir) {
                atual = atual->dir;
                if (atual->pista) inserirPista(rootPistas, atual->pista);
            } else {
                printf("Não há sala à direita. Escolha outra opção.\n");
            }
        } else {
            printf("Comando não reconhecido. Use 'e', 'd' ou 's'.\n");
        }
    }
}

/*
 exibirPistas()
 Imprime a árvore de pistas em ordem alfabética (inorder traversal).
 - root: raiz da BST de pistas
*/
void exibirPistas(PistaNode *root) {
    if (!root) return;
    exibirPistas(root->esq);
    printf("- %s\n", root->pista);
    exibirPistas(root->dir);
}

/* ---- Funções auxiliares para liberar memória ---- */

void liberarSalas(Sala *s) {
    if (!s) return;
    liberarSalas(s->esq);
    liberarSalas(s->dir);
    free(s->nome);
    if (s->pista) free(s->pista);
    free(s);
}

void liberarPistas(PistaNode *p) {
    if (!p) return;
    liberarPistas(p->esq);
    liberarPistas(p->dir);
    free(p->pista);
    free(p);
}

/* ---- main: define o mapa da mansão (fixo) e executa a exploração ---- */

int main(void) {
    /* Criando mapa fixo da mansão (árvore binária) */

    Sala *hall = criarSala("Hall de Entrada", "Pegadas molhadas perto da porta");
    Sala *salaEstar = criarSala("Sala de Estar", "Copo quebrado no tapete");
    Sala *cozinha = criarSala("Cozinha", "Garrafa vazia com etiqueta rasgada");
    Sala *biblioteca = criarSala("Biblioteca", "Livro rasgado entre as prateleiras");
    Sala *quarto = criarSala("Quarto Principal", NULL); /* sem pista */
    Sala *jardim = criarSala("Jardim", "Pegada do jardineiro próxima à cerca");
    Sala *sotao = criarSala("Sótão", "Foto antiga com personagem riscado");

    /* Monta o mapa (ligações) */
    hall->esq = salaEstar;
    hall->dir = cozinha;

    salaEstar->esq = biblioteca;
    salaEstar->dir = quarto;

    cozinha->esq = jardim;
    cozinha->dir = sotao;

    /* Raiz da BST de pistas coletadas */
    PistaNode *raizPistas = NULL;

    /* Instruções iniciais para o usuário */
    printf("Bem-vindo(a), Detetive!\n");
    printf("Explore a mansão a partir do Hall de Entrada.\n");
    printf("Navegue usando 'e' (esquerda), 'd' (direita) ou 's' (sair) quando desejar encerrar.\n");
    printf("Pistas encontradas serão adicionadas automaticamente ao seu caderno.\n\n");

    /* iniciar exploração */
    explorarSalasComPistas(hall, &raizPistas);

    /* Exibe todas as pistas coletadas em ordem alfabética */
    printf("\n--- Pistas coletadas (ordem alfabética) ---\n");
    if (!raizPistas) {
        printf("Nenhuma pista coletada.\n");
    } else {
        exibirPistas(raizPistas);
    }

    /* Liberar memória */
    liberarSalas(hall);
    liberarPistas(raizPistas);

    printf("\nExploração finalizada. Boa sorte na investigação!\n");
    return 0;
}
