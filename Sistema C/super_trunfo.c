#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // Variáveis para a Carta 1
    char estado_01;
    char codigo_01[4];
    char cidade_01[50];
    unsigned long int populacao_01;
    float area_01;
    float pib_01;
    int pontos_turisticos_01;
    float densidadePopulacional_01;
    float pib_per_capita_01;
    float SuperPoder_01;

    // Variáveis para a Carta 2
    char estado_02;
    char codigo_02[4];
    char cidade_02[50];
    unsigned long int populacao_02;
    float area_02;
    float pib_02;
    int pontos_turisticos_02;
    float densidadePopulacional_02;
    float pib_per_capita_02;
    float SuperPoder_02;

    printf("\n----------------------SUPER TRUNFO----------------------\n");
    //CARTA 01----------------------------------------------------------------------------------
    printf("\n1) CADASTRO DA CARTA 01: \n");
    // Leitura dos dados da Carta 1
    printf("Estado (Uma letra de A-H): ");
    scanf(" %c", &estado_01);
    getchar();
    printf("Codigo da Carta (ex: A01): ");
    fgets(codigo_01, sizeof(codigo_01), stdin);
    codigo_01[strcspn(codigo_01, "\n")] = '\0';
    scanf("%s", codigo_01);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade_01);
    printf("Populacao: ");
    scanf("%ld", &populacao_01);
    printf("Area (em km2): ");
    scanf("%f", &area_01);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &pib_01);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &pontos_turisticos_01);

    // Cálculos da Carta 01
    densidadePopulacional_01 = populacao_01 / area_01;
    pib_per_capita_01 = pib_01 / populacao_01;
    SuperPoder_01 = populacao_01 + area_01 + pib_01 + pontos_turisticos_01 + pib_per_capita_01 - densidadePopulacional_01;
    
    //CARTA 02----------------------------------------------------------------------------------
    printf("\n1) CADASTRO DA CARTA 02:\n");
    // Leitura dos dados da Carta 2
    printf("Estado (Uma letra de A-H): ");
    scanf(" %c", &estado_02);
    getchar();
    printf("Codigo da Carta (ex: B02): ");
    fgets(codigo_02, sizeof(codigo_02), stdin);
    codigo_02[strcspn(codigo_02, "\n")] = '\0';
    scanf("%s", codigo_02);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade_02);
    printf("Populacao: ");
    scanf("%ld", &populacao_02);
    printf("Area (em km2): ");
    scanf("%f", &area_02);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &pib_02);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &pontos_turisticos_02);

    // Calculos da Carta 02
    densidadePopulacional_02 = populacao_02 / area_02;
    pib_per_capita_02 = pib_02 / populacao_02;
    SuperPoder_02 = populacao_02 + area_02 + pib_02 + pontos_turisticos_02 + pib_per_capita_02 - densidadePopulacional_02;

    printf("\n----------------------RESULTADO----------------------\n");
    // Saída da Carta 1
    printf("CARTA 01:\n");
    printf("Estado: %c\n", estado_01);
    printf("Codigo: %s\n", codigo_01);
    printf("Nome da Cidade: %s\n", cidade_01);
    printf("Populacao: %ld\n", populacao_01);
    printf("Area: %.2f km2\n", area_01);
    printf("PIB: %.2f bilhoes de reais\n", pib_01);
    printf("Numero de Pontos Turisticos: %d\n", pontos_turisticos_01);
    printf("Densidade Populacional: %.2f hab/km2\n", densidadePopulacional_01);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_01);
    printf("Densidade Populacional: %.2f hab/km2\n", densidadePopulacional_01);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_01);

    // Saída da Carta 2
    printf("\nCARTA 02:\n");
    printf("Estado: %c\n", estado_02);
    printf("Codigo: %s\n", codigo_02);
    printf("Nome da Cidade: %s\n", cidade_02);
    printf("Populacao: %ld\n", populacao_02);
    printf("Area: %.2f km2\n", area_02);
    printf("PIB: %.2f bilhoes de reais\n", pib_02);
    printf("Numero de Pontos Turisticos: %d\n", pontos_turisticos_02);
    printf("Densidade Populacional: %.2f hab/km2\n", densidadePopulacional_02);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_02);
    printf("Densidade Populacional: %.2f hab/km2\n", densidadePopulacional_02);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_02);


    //Resultado da Comparacao de Atributos
    printf("\n----------------------COMPARACAO----------------------\n");
    if (populacao_01 > populacao_02) {
        printf("Populacao: Carta 01 venceu. (1)\n");
    } else if (populacao_01 < populacao_02) {
        printf("Populacao: Carta 02 venceu. (0)\n");
    } else {
        printf("Populacao: Empate. (-)\n");
    }

    if (area_01 > area_02) {
        printf("Area: Carta 01 venceu. (1)\n");
    } else if (area_01 < area_02) {
        printf("Area: Carta 02 venceu. (0)\n");
    } else {
        printf("Area: Empate. (-)\n");
    }

    if (pib_01 > pib_02) {
        printf("PIB: Carta 01 venceu. (1)\n");
    } else if (pib_01 < pib_02) {
        printf("PIB: Carta 02 venceu. (0)\n");
    } else {
        printf("PIB: Empate. (-)\n");
    }

    if (pontos_turisticos_01 > pontos_turisticos_02) {
        printf("Pontos Turisticos: Carta 01 venceu. (1)\n");
    } else if (pontos_turisticos_01 < pontos_turisticos_02) {
        printf("Pontos Turisticos: Carta 02 venceu. (0)\n");
    } else {
        printf("Pontos Turisticos: Empate. (-)\n");
    }

    if (densidadePopulacional_01 < densidadePopulacional_02) {
        printf("Densidade Populacional: Carta 01 venceu. (1)\n");
    } else if (densidadePopulacional_01 > densidadePopulacional_02) {
        printf("Densidade Populacional: Carta 02 venceu. (0)\n");
    } else {
        printf("Densidade Populacional: Empate. (-)\n");
    }

    if (pib_per_capita_01 > pib_per_capita_02) {
        printf("PIB per Capita: Carta 01 venceu. (1)\n");
    } else if (pib_per_capita_01 < pib_per_capita_02) {
        printf("PIB per Capita: Carta 02 venceu. (0)\n");
    } else {
        printf("PIB per Capita: Empate. (-)\n");
    }

    if (SuperPoder_01 > SuperPoder_02) {
        printf("Super Poder: Carta 01 venceu. (1)\n");
    } else if (SuperPoder_01 < SuperPoder_02) {
        printf("Super Poder: Carta 02 venceu. (0)\n");
    } else {
        printf("Super Poder: Empate. (-)\n");
    }

    return 0;
}
