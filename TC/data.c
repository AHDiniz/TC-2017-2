#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   "data.h"

#define DIM 30

struct tm IdadeEmCalend(int data[])
{
    struct tm cData; // data em um formato de calendário
    
    // Calculando o dia do nascimento:
    cData.tm_mday = data[0];

    // Calculando o mês do nascimento:
    cData.tm_mon = data[1];

    // Calculando o ano do nascimento:
    cData.tm_year = data[2];

    return cData;
}

int CalcularIdade(struct tm nasc)
{
    // Ajudarão no cálculo da idade:
    time_t hoje; struct tm *cHoje; 
    int idade = 0; // variável de retorno

    // Achando a data atual:
    time(&hoje);
    cHoje = localtime(&hoje);
    cHoje->tm_year += 1900;

    idade = cHoje->tm_year - nasc.tm_year; // Inicialmente, a idade será a diferença dos anos

    if (nasc.tm_mon > cHoje->tm_mon) // Se o mês de nascimento for maior que o da data atual, quer dizer que a pessoa já teve seu aniversário
        idade++;
    else if (nasc.tm_mon == cHoje->tm_mon && nasc.tm_mday > cHoje->tm_mday) // Isso também acontece se for o mesmo mês, mas o dia do nascimento for maior que o dia de hoje
        idade++;
    
    return idade;
}

int CalculoIdade(int data[])
{
    int idade = CalcularIdade(IdadeEmCalend(data));
    return idade;
}