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
    float densidadeDemografica_01;
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
    float densidadeDemografica_02;
    float pib_per_capita_02;
    float SuperPoder_02;

    printf("\n----------------------SUPER TRUNFO----------------------\n");
    // CARTA 01----------------------------------------------------------------------------------
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
    densidadeDemografica_01 = populacao_01 / area_01;
    pib_per_capita_01 = pib_01 / populacao_01;
    SuperPoder_01 = populacao_01 + area_01 + pib_01 + pontos_turisticos_01 + pib_per_capita_01 - densidadeDemografica_01;

    // CARTA 02----------------------------------------------------------------------------------
    printf("\n2) CADASTRO DA CARTA 02:\n");
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
    densidadeDemografica_02 = populacao_02 / area_02;
    pib_per_capita_02 = pib_02 / populacao_02;
    SuperPoder_02 = populacao_02 + area_02 + pib_02 + pontos_turisticos_02 + pib_per_capita_02 - densidadeDemografica_02;

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
    printf("Densidade Demografica: %.2f hab/km2\n", densidadeDemografica_01);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_01);
    printf("Densidade Demografica: %.2f hab/km2\n", densidadeDemografica_01);
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
    printf("Densidade Demografica: %.2f hab/km2\n", densidadeDemografica_02);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_02);
    printf("Densidade Demografica: %.2f hab/km2\n", densidadeDemografica_02);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita_02);

    int atributo;

    while (atributo < 1 || atributo > 5)
    {
        // Resultado da Comparacao de Atributos
        printf("\n----------------------COMPARACAO----------------------\n");
        printf("\nSELECIONE UM ATRIBUTO PARA COMPARAR\n");
        printf("Digite 1 para: Populacao\n");
        printf("Digite 2 para: Area\n");
        printf("Digite 3 para: PIB\n");
        printf("Digite 4 para: Pontos Turisticos\n");
        printf("Digite 5 para: Densidade Demografica\n");

        scanf("%d", &atributo);

        printf("\n");

        switch (atributo)
        {
            case 1:
                printf("%s\n", cidade_01);
                printf("populacao_01: %ld\n", populacao_01);
                printf("%s\n", cidade_02);
                printf("populacao_02: %ld\n", populacao_02);

                if (populacao_01 > populacao_02) {
                    printf("\n%s", cidade_01);
                    printf(" VENCEU!");
                } else if (populacao_01 < populacao_02) {
                    printf("\n%s", cidade_02);
                    printf(" VENCEU!");
                } else
                    printf("EMPATE!!!\n");
                break;
            case 2:
                printf("%s", cidade_01);
                printf("Area: %.2f\n", area_01);
                printf("%s", cidade_02);
                printf("Area: %.2f\n", area_02);

                if (area_01 > area_02) {
                    printf("\n%s", cidade_01);
                    printf(" VENCEU!");
                } else if (area_01 < area_02) {
                    printf("\n%s", cidade_02);
                    printf(" VENCEU!");
                } else
                    printf("EMPATE!!!\n");
                break;
            case 3:
                printf("%s\n", cidade_01);
                printf("PIB: %.2f\n", pib_01);
                printf("%s\n", cidade_02);
                printf("PIB: %.2f\n", pib_02);

                if (pib_01 > pib_02) {
                    printf("\n%s", cidade_01);
                    printf(" VENCEU!");
                } else if (pib_01 < pib_02) {
                    printf("\n%s", cidade_02);
                    printf(" VENCEU!");
                } else
                    printf("EMPATE!!!\n");
                break;
            case 4:
                printf("%s\n", cidade_01);
                printf("Pontos Turisticos: %d\n", pontos_turisticos_01);
                printf("%s\n", cidade_02);
                printf("Pontos Turisticos: %d\n", pontos_turisticos_02);

                if (pontos_turisticos_01 > pontos_turisticos_02) {
                    printf("\n%s", cidade_01);
                    printf(" VENCEU!");
                } else if (pontos_turisticos_01 < pontos_turisticos_02) {
                    printf("\n%s", cidade_02);
                    printf(" VENCEU!");
                } else
                    printf("EMPATE!!!\n");
                break;
            case 5:
                printf("%s\n", cidade_01);
                printf("Densidade Demografica: %.2f\n", densidadeDemografica_01);
                printf("%s\n", cidade_02);
                printf("Densidade Demografica: %.2f\n", densidadeDemografica_02);

                if (densidadeDemografica_01 < densidadeDemografica_02) {
                    printf("\n%s", cidade_01);
                    printf(" VENCEU!");
                } else if (densidadeDemografica_01 > densidadeDemografica_02) {
                    printf("\n%s", cidade_02);
                    printf(" VENCEU!");
                } else
                    printf("EMPATE!!!\n");
                break;
            default:
                printf("Atributo invalido.\n");
                printf("Repetindo processo...\n");
                break;
        }
    }

    return 0;
}
