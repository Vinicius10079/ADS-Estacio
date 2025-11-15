/*
  war_missoes.c
  Implementação de sistema de missões para jogadores (exercício em C).
  - Modularizado em funções: atribuirMissao, verificarMissao, exibirMissao, atacar, exibirMapa, liberarMemoria, main.
  - Usa malloc/calloc para alocação dinâmica.
  - Missões são strings copiadas com strcpy para buffers alocados (missões por jogador).
  - srand(time(NULL)) para aleatoriedade.
  - Comentários explicam cada função.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSAO_LEN 120
#define MAX_TERRITORIOS 20

/* Estrutura do território */
typedef struct {
    char nome[30];
    char cor[10];   /* cor do jogador/dono: ex "vermelha", "azul", "neutra" */
    int tropas;
} Territorio;

/* --- Protótipos das funções (modularização) --- */

/* Sorteia uma missão e copia para 'destino' (destino deve apontar para área alocada) */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);

/* Verifica se uma missão (string) foi cumprida dado o mapa (lógica simples inicial).
   Retorna 1 se cumprida, 0 caso contrário.
   A função interpreta alguns padrões nas descrições de missão:
     - "Conquistar 3 territorios seguidos" -> busca 3 territórios consecutivos com mesma cor
     - "Eliminar todas as tropas da cor X" -> verifica se não existe mais nenhum território com cor X ou tropas X>0
     - "Controlar N territorios" -> busca número N na string e verifica se existe cor mencionada na string (se não houver, não considera cor)
   Obs: por simplicidade, a função procura palavras-chave e cores "vermelha" e "azul". */
int verificarMissao(char* missao, Territorio* mapa, int tamanho);

/* Exibe a missão (passagem por valor: recebe char* e apenas imprime) */
void exibirMissao(char* missao);

/* Simula ataque entre dois territórios (validando que sejam de cores diferentes) */
void atacar(Territorio* atacante, Territorio* defensor);

/* Exibe o mapa (lista de territórios) */
void exibirMapa(Territorio* mapa, int tamanho);

/* Libera memória alocada para missões e mapas */
void liberarMemoria(Territorio* mapa, int tamanho, char** missoesJogadores, int numJogadores);

/* Função auxiliar: lê número inteiro no intervalo [min,max] de stdin (robusta) */
int lerIntIntervalo(int min, int max);

/* --- Implementações --- */

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    /* Realiza sorteio de uma missão e copia para destino usando strcpy */
    if (totalMissoes <= 0 || destino == NULL) return;
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (missao == NULL || mapa == NULL || tamanho <= 0) return 0;

    /* Lowercase simplificado para checagens (cria cópia) */
    char buf[MAX_MISSAO_LEN];
    strncpy(buf, missao, MAX_MISSAO_LEN-1);
    buf[MAX_MISSAO_LEN-1] = '\0';
    /* converte para minúsculas */
    for (int i = 0; buf[i]; ++i) {
        if (buf[i] >= 'A' && buf[i] <= 'Z') buf[i] = buf[i] - 'A' + 'a';
    }

    /* Caso 1: Conquistar 3 territorios seguidos */
    if (strstr(buf, "conquistar 3 territorios seguidos") != NULL ||
        strstr(buf, "conquistar 3 territórios seguidos") != NULL) {
        /* Busca três territorios consecutivos que tenham a mesma cor e tropas > 0 */
        for (int i = 0; i <= tamanho - 3; ++i) {
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i+2].cor) == 0 &&
                mapa[i].tropas > 0 && mapa[i+1].tropas > 0 && mapa[i+2].tropas > 0) {
                /* Encontrou sequência de 3 do mesmo dono */
                return 1;
            }
        }
        return 0;
    }

    /* Caso 2: Eliminar todas as tropas da cor X (procura "vermelha" ou "azul") */
    if (strstr(buf, "eliminar todas as tropas da cor vermelha") != NULL ||
        strstr(buf, "eliminar todas as tropas da cor vermelha.") != NULL) {
        /* Verifica se existe território com cor "vermelha" que tenha tropas > 0 */
        for (int i = 0; i < tamanho; ++i) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }
    if (strstr(buf, "eliminar todas as tropas da cor azul") != NULL ||
        strstr(buf, "eliminar todas as tropas da cor azul.") != NULL) {
        for (int i = 0; i < tamanho; ++i) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }

    /* Caso 3: Controlar N territorios da cor X (ex.: "Controlar 4 territorios da cor azul") */
    if (strstr(buf, "controlar") != NULL && strstr(buf, "territor") != NULL) {
        /* tenta extrair um número presente na string */
        int alvoN = 0;
        for (int i = 0; buf[i]; ++i) {
            if (buf[i] >= '0' && buf[i] <= '9') {
                alvoN = atoi(&buf[i]);
                break;
            }
        }
        if (alvoN > 0) {
            /* detectar cor alvo */
            char corAlvo[10] = "";
            if (strstr(buf, "vermelha") != NULL) strcpy(corAlvo, "vermelha");
            else if (strstr(buf, "azul") != NULL) strcpy(corAlvo, "azul");
            else corAlvo[0] = '\0';

            if (corAlvo[0] == '\0') return 0; /* sem cor definida, falha simplificada */

            int cont = 0;
            for (int i = 0; i < tamanho; ++i) {
                if (strcmp(mapa[i].cor, corAlvo) == 0) cont++;
            }
            return (cont >= alvoN) ? 1 : 0;
        }
    }

    /* Caso padrão/fallback: se a missão contém 'vazia' ou 'cumprida' (não aplicável) */
    return 0;
}

void exibirMissao(char* missao) {
    if (missao == NULL) return;
    printf(">> MISSÃO: %s\n", missao);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante == NULL || defensor == NULL) return;

    /* Validar: só pode atacar se cores diferentes */
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido: %s e %s pertencem à mesma cor (%s).\n",
               atacante->nome, defensor->nome, atacante->cor);
        return;
    }
    if (atacante->tropas <= 0) {
        printf("Ataque falhou: %s não possui tropas.\n", atacante->nome);
        return;
    }

    int rollAt = (rand() % 6) + 1;
    int rollDf = (rand() % 6) + 1;
    printf("%s (cor %s) ataca %s (cor %s): dado atacante=%d, defensor=%d\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor, rollAt, rollDf);

    if (rollAt > rollDf) {
        /* atacante vence: transfere cor e metade das tropas (arredonda para baixo) */
        int transferencia = atacante->tropas / 2;
        if (transferencia < 1) transferencia = 1;
        printf("Atacante venceu! Transferindo %d tropas para %s e mudando sua cor para %s.\n",
               transferencia, defensor->nome, atacante->cor);
        /* defender passa a ter a cor do atacante e recebe as tropas transferidas */
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transferencia;
        atacante->tropas -= transferencia;
        if (atacante->tropas < 0) atacante->tropas = 0;
    } else {
        /* defensor vence: atacante perde uma tropa */
        printf("Defensor resistiu! %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

void exibirMapa(Territorio* mapa, int tamanho) {
    if (mapa == NULL || tamanho <= 0) return;
    printf("\n--- MAPA (territórios) ---\n");
    for (int i = 0; i < tamanho; ++i) {
        printf("[%2d] %s | cor: %s | tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("--------------------------\n");
}

void liberarMemoria(Territorio* mapa, int tamanho, char** missoesJogadores, int numJogadores) {
    /* mapa foi alocado como vetor de Territorio por calloc/malloc */
    (void)tamanho;
    if (mapa != NULL) {
        free(mapa);
    }
    if (missoesJogadores != NULL) {
        for (int i = 0; i < numJogadores; ++i) {
            if (missoesJogadores[i] != NULL) free(missoesJogadores[i]);
        }
        free(missoesJogadores);
    }
}

/* Leitura robusta de inteiro com intervalo */
int lerIntIntervalo(int min, int max) {
    int v;
    while (1) {
        if (scanf("%d", &v) != 1) {
            while (getchar() != '\n'); /* limpa input */
            printf("Entrada inválida. Digite um número entre %d e %d: ", min, max);
            continue;
        }
        if (v < min || v > max) {
            printf("Fora do intervalo. Digite entre %d e %d: ", min, max);
            continue;
        }
        break;
    }
    return v;
}

/* --- main: monta mapa, jogadores, sorteia missões, simula turnos --- */
int main() {
    srand((unsigned int) time(NULL));

    /* Definição de algumas missões possíveis (vetor de strings) */
    char* missoesPadrao[] = {
        "Conquistar 3 territorios seguidos", /* missão genérica: 3 consecutivos de mesma cor */
        "Eliminar todas as tropas da cor vermelha",
        "Eliminar todas as tropas da cor azul",
        "Controlar 3 territorios da cor vermelha",
        "Controlar 2 territorios da cor azul"
    };
    int totalMissoes = sizeof(missoesPadrao) / sizeof(missoesPadrao[0]);

    /* Configuração do número de jogadores (fixamos 2 para o exemplo) */
    int numJogadores = 2;
    char* coresJogadores[] = {"vermelha", "azul"}; /* jogador 0 = vermelho, 1 = azul */

    /* Aloca vetor de ponteiros para missões dos jogadores (cada um apontará para malloc) */
    char** missoesJogadores = (char**) malloc(sizeof(char*) * numJogadores);
    if (missoesJogadores == NULL) {
        fprintf(stderr, "Erro de alocacao para missoesJogadores\n");
        return 1;
    }
    for (int i = 0; i < numJogadores; ++i) {
        missoesJogadores[i] = (char*) malloc(sizeof(char) * MAX_MISSAO_LEN);
        if (missoesJogadores[i] == NULL) {
            fprintf(stderr, "Erro de alocacao para missoesJogadores[%d]\n", i);
            /* libera já alocado */
            for (int j = 0; j < i; ++j) free(missoesJogadores[j]);
            free(missoesJogadores);
            return 1;
        }
    }

    /* Criação do mapa com territórios (dinamicamente) */
    int tamanhoMapa = 8; /* exemplo */
    Territorio* mapa = (Territorio*) calloc(tamanhoMapa, sizeof(Territorio));
    if (mapa == NULL) {
        fprintf(stderr, "Erro de alocacao para mapa\n");
        liberarMemoria(NULL, 0, missoesJogadores, numJogadores);
        return 1;
    }

    /* Inicialização manual dos territórios (nomes, cores, tropas) */
    strncpy(mapa[0].nome, "Amazônia", sizeof(mapa[0].nome)-1); strcpy(mapa[0].cor, "vermelha"); mapa[0].tropas = 4;
    strncpy(mapa[1].nome, "Andes", sizeof(mapa[1].nome)-1);      strcpy(mapa[1].cor, "azul");     mapa[1].tropas = 3;
    strncpy(mapa[2].nome, "Pantanal", sizeof(mapa[2].nome)-1);  strcpy(mapa[2].cor, "vermelha"); mapa[2].tropas = 2;
    strncpy(mapa[3].nome, "Caatinga", sizeof(mapa[3].nome)-1);  strcpy(mapa[3].cor, "neutra");   mapa[3].tropas = 1;
    strncpy(mapa[4].nome, "Pampas", sizeof(mapa[4].nome)-1);    strcpy(mapa[4].cor, "azul");     mapa[4].tropas = 2;
    strncpy(mapa[5].nome, "Cerrado", sizeof(mapa[5].nome)-1);   strcpy(mapa[5].cor, "neutra");   mapa[5].tropas = 1;
    strncpy(mapa[6].nome, "Serra", sizeof(mapa[6].nome)-1);      strcpy(mapa[6].cor, "vermelha"); mapa[6].tropas = 3;
    strncpy(mapa[7].nome, "Litoral", sizeof(mapa[7].nome)-1);    strcpy(mapa[7].cor, "azul");     mapa[7].tropas = 4;

    /* Sorteia e atribui missões a cada jogador (copia com strcpy para a memória alocada) */
    for (int i = 0; i < numJogadores; ++i) {
        atribuirMissao(missoesJogadores[i], missoesPadrao, totalMissoes);
    }

    /* Exibir mapa inicial */
    exibirMapa(mapa, tamanhoMapa);

    /* Exibe a missão de cada jogador apenas uma vez (interface intuitiva) */
    printf("\n--- MISSÕES INICIAIS (apenas exibidas uma vez) ---\n");
    for (int i = 0; i < numJogadores; ++i) {
        printf("Jogador %d (cor %s): ", i+1, coresJogadores[i]);
        exibirMissao(missoesJogadores[i]); /* passagem por valor (ponteiro é passado por valor) */
    }
    printf("-----------------------------------------------\n\n");

    /* Loop de turnos simplificado:
       - Jogadores escolhem um território de origem e outro de destino (simulado)
       - Realiza ataque e atualiza mapa
       - Ao final de cada turno, verifica se algum jogador cumpriu sua missão
    */
    int turno = 0;
    int vencedor = -1;
    int maxTurnos = 50; /* limite de segurança para evitar loop infinito em exemplo */
    while (turno < maxTurnos && vencedor == -1) {
        int jogadorAtual = turno % numJogadores;
        printf("\n======== Turno %d: Jogador %d (cor %s) ========\n",
               turno+1, jogadorAtual+1, coresJogadores[jogadorAtual]);

        exibirMapa(mapa, tamanhoMapa);

        /* Para simplificar: pedir ao usuário escolher índice de atacante (território do jogador)
           e índice de defensor (território alvo). Validação garante cor diferente para alvo. */
        printf("Escolha o índice do TERRITÓRIO ATACANTE (pertencente à sua cor): ");
        int idxAt = lerIntIntervalo(0, tamanhoMapa-1);
        if (strcmp(mapa[idxAt].cor, coresJogadores[jogadorAtual]) != 0) {
            printf("Entrada inválida: o território %s não pertence à sua cor (%s). Turno perdido.\n",
                   mapa[idxAt].nome, coresJogadores[jogadorAtual]);
        } else {
            printf("Escolha o índice do TERRITÓRIO DEFENSOR (inimigo): ");
            int idxDf = lerIntIntervalo(0, tamanhoMapa-1);
            if (strcmp(mapa[idxDf].cor, mapa[idxAt].cor) == 0) {
                printf("Ataque inválido: alvo tem a mesma cor. Turno encerrado.\n");
            } else {
                atacar(&mapa[idxAt], &mapa[idxDf]);
            }
        }

        /* Verificações de missão (silenciosas exceto quando cumprida) */
        for (int j = 0; j < numJogadores; ++j) {
            if (verificarMissao(missoesJogadores[j], mapa, tamanhoMapa)) {
                vencedor = j;
                break;
            }
        }

        turno++;
    }

    if (vencedor != -1) {
        printf("\n***** MISSÃO CUMPRIDA! Jogador %d (cor %s) venceu! *****\n",
               vencedor+1, coresJogadores[vencedor]);
        printf("Missão cumprida: %s\n", missoesJogadores[vencedor]);
    } else {
        printf("\nFim do jogo por limite de turnos. Ninguém cumpriu a missão.\n");
    }

    /* Limpeza de memória (free) */
    liberarMemoria(mapa, tamanhoMapa, missoesJogadores, numJogadores);

    return 0;
}
