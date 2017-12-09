#ifndef DATA_H

#define DATA_H

#include <time.h>

// Funções que calculam idade de uma pessoa:
int CalcularIdade(struct tm);   // Função que calcula a idade de uma pessoa de acordo com a data atual
struct tm IdadeEmCalend(int *); // Função que lê uma array de inteiros e constrói um struct de calendário a partir dessa string
int CalculoIdade(int *);        // Função que lê um array de inteiros e retorna a idade

#endif