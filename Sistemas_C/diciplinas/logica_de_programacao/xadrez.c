#include <stdio.h>

// ---------------- Funções Recursivas ----------------

// Função recursiva para o movimento da Torre (Direita)
void moverTorre(int casas) {
    if (casas == 0) return;
    printf("Direita\n");
    moverTorre(casas - 1);
}

// Função recursiva para o movimento da Rainha (Esquerda)
void moverRainha(int casas) {
    if (casas == 0) return;
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// Função recursiva para o movimento do Bispo (Diagonal: Cima Direita)
void moverBispoRecursivo(int casas) {
    if (casas == 0) return;
    printf("Cima Direita\n");
    moverBispoRecursivo(casas - 1);
}

// ---------------- Função Principal ----------------
int main() {
    // Quantidade de casas a serem percorridas
    const int movimentoTorre = 5;
    const int movimentoRainha = 8;
    const int movimentoBispo = 5;

    // ---------------- TORRE ----------------
    printf("Movimento da Torre:\n");
    moverTorre(movimentoTorre);

    // ---------------- BISPO (Recursivo) ----------------
    printf("\nMovimento do Bispo (Recursivo):\n");
    moverBispoRecursivo(movimentoBispo);

    // ---------------- RAINHA ----------------
    printf("\nMovimento da Rainha:\n");
    moverRainha(movimentoRainha);

    // ---------------- CAVALO (Loops Complexos) ----------------
    printf("\nMovimento do Cavalo:\n");

    // O Cavalo se move 2 casas para cima e 1 para a direita (em "L")
    // Utilizando dois loops aninhados e controle com break/continue
    const int casasVerticais = 2;
    const int casasHorizontais = 1;

    for (int v = 0; v < casasVerticais + 1; v++) {
        if (v >= casasVerticais) break; // Limita a 2 movimentos verticais
        printf("Cima\n");

        for (int h = 0; h < casasHorizontais + 1; h++) {
            if (h >= casasHorizontais) continue; // Limita a 1 movimento horizontal
            if (v == casasVerticais - 1) { // Só movimenta horizontal depois de 2 verticais
                printf("Direita\n");
            }
        }
    }

    // ---------------- BISPO (Loops Aninhados) ----------------
    printf("\nMovimento do Bispo (Loops Aninhados):\n");

    // Movimento diagonal simulado por avanço vertical e horizontal simultâneo
    const int casasDiagonais = 5;
    for (int i = 0; i < casasDiagonais; i++) {
        for (int j = 0; j < 1; j++) { // horizontal avança 1 por vertical
            printf("Cima Direita\n");
        }
    }

    return 0;
}
