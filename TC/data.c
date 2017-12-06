#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   "data.h"

#define DIM 30

struct tm IdadeEmCalend(char data[])
{
    struct tm cData; // data em um formato de calendário
    char aux[DIM];   // variável que ajudará na construção da data
    
    // Calculando o dia do nascimento:
    aux[0] = data[0];
    aux[1] = data[1];
    cData.tm_mday = (int)strtol(aux, NULL, 10);
    printf("Dia: %d.\n", cData.tm_mday);

    // Calculando o mês do nascimento:
    aux[0] = data[3];
    aux[1] = data[4];
    cData.tm_mon = (int)strtol(aux, NULL, 10) - 1; // o mês varia de 0 a 11, e não de 1 a 12.
    printf("Mes: %d.\n", cData.tm_mon + 1);

    // Calculando o ano do nascimento:
    for (int i = 0; i <= 4; i++)
        aux[i] = data[i + 5];
    cData.tm_year = (int)strtol(aux, NULL, 10);
    printf("Ano: %d.\n", cData.tm_year);

    return cData;
}

int CalcularIdade(struct tm nasc)
{
    time_t tNasc = mktime(&nasc); // data de nascimento da pessoa no tipo algébrico de tempo
    time_t hoje = time(NULL);     // Pegando a data atual
    
    // Diferença em segundos das idades
    double difInSec = difftime(hoje, tNasc);

    return 0; 
}