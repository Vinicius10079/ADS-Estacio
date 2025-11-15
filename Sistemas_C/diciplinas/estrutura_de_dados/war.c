#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct de território
typedef struct {
    char nome[30];
    char cor[10];   // dono do território
    int tropas;     // quantidade de tropas
} Territorio;

// Cadastro inicial dos territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastrar Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor (exercito): ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função principal de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simula dois dados, um para cada lado
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nRESULTADO DO ATAQUE:\n");
    printf("Atacante (%s): Dado = %d\n", atacante->nome, dadoA);
    printf("Defensor (%s): Dado = %d\n\n", defensor->nome, dadoD);

    // Atacante ganha
    if (dadoA > dadoD) {
        printf(">> %s conquistou %s!\n", atacante->nome, defensor->nome);

        strcpy(defensor->cor, atacante->cor);  // muda o dono
        defensor->tropas = atacante->tropas / 2; // metade das tropas migram

        printf("Nova cor do territorio: %s\n", defensor->cor);
        printf("Tropas do defensor agora: %d\n", defensor->tropas);
    }
    // Defensor ganha
    else {
        printf(">> %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas--; // perde uma tropa

        if (atacante->tropas < 0)
            atacante->tropas = 0;

        printf("Tropas restantes do atacante: %d\n", atacante->tropas);
    }
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}


int main() {
    srand(time(NULL)); // garante aleatoriedade dos dados

    int n, op, at, def;

    printf("Quantidade de territorios: ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar territorio\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            exibirTerritorios(mapa, n);
            break;

        case 2:
            exibirTerritorios(mapa, n);

            printf("\nIndice do territorio atacante: ");
            scanf("%d", &at);

            printf("Indice do territorio defensor: ");
            scanf("%d", &def);

            // Validações simples
            if (at < 0 || at >= n || def < 0 || def >= n) {
                printf("Indices invalidos!\n");
                break;
            }
            if (strcmp(mapa[at].cor, mapa[def].cor) == 0) {
                printf("Nao pode atacar um territorio da mesma cor!\n");
                break;
            }
            if (mapa[at].tropas <= 0) {
                printf("O atacante nao possui tropas suficientes!\n");
                break;
            }

            atacar(&mapa[at], &mapa[def]); // ataque ocorre aqui
            break;

        case 0:
            printf("Finalizando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (op != 0);

    // Libera memória
    liberarMemoria(mapa);
    return 0;
}
