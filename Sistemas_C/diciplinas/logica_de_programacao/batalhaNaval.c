
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Tamanho fixo do tabuleiro e das matrizes de habilidade
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

// Função para imprimir o tabuleiro com legenda
void imprimir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Legenda: 0 = Agua, 3 = Navio, 5 = Habilidade\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

// Função para sobrepor matriz de habilidade ao tabuleiro
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        int origem_linha, int origem_coluna) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origem_linha + (i - centro);
                int coluna = origem_coluna + (j - centro);

                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == 0) {
                        tabuleiro[linha][coluna] = 5; // Marca habilidade se não tiver navio
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionar navios
    int navio1_l[] = {2, 2, 2}, navio1_c[] = {4, 5, 6};
    int navio2_l[] = {5, 6, 7}, navio2_c[] = {7, 7, 7};
    int navio3_l[] = {0, 1, 2}, navio3_c[] = {0, 1, 2};
    int navio4_l[] = {0, 1, 2}, navio4_c[] = {9, 8, 7};

    for (int i = 0; i < 3; i++) {
        tabuleiro[navio1_l[i]][navio1_c[i]] = 3;
        tabuleiro[navio2_l[i]][navio2_c[i]] = 3;
        tabuleiro[navio3_l[i]][navio3_c[i]] = 3;
        tabuleiro[navio4_l[i]][navio4_c[i]] = 3;
    }

    // Matriz Cone (formato de pirâmide invertida)
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= 2 - i && j <= 2 + i && i <= 2) {
                cone[i][j] = 1;
            }
        }
    }

    // Matriz Cruz
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 2 || j == 2) {
                cruz[i][j] = 1;
            }
        }
    }

    // Matriz Octaedro (losango)
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                octaedro[i][j] = 1;
            }
        }
    }

    // Aplicar habilidades em posições fixas
    aplicar_habilidade(tabuleiro, cone, 2, 2);       // Cone em (2,2)
    aplicar_habilidade(tabuleiro, cruz, 5, 5);       // Cruz em (5,5)
    aplicar_habilidade(tabuleiro, octaedro, 7, 7);   // Octaedro em (7,7)

    // Imprimir resultado final
    imprimir_tabuleiro(tabuleiro);

    return 0;
}
