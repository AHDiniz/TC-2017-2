#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consultaPorEspec.h"

conslPorEspec ConstruirContadorConsl(char *especialidade, int consultas)
{
    conslPorEspec c;
    strcpy(c.especialidade, especialidade);
    c.numConsultas = consultas;
    return c;
}

void RemoverRepetidos(conslPorEspec eNc[], int *qE)
{
    int i, j; // variáveis de incrementação

    for (i = *qE - 1; i >= 0; i--)
        for (j = 0; j < i; j++)
            if (strcmp(eNc[j].especialidade, eNc[i].especialidade) == 0)
            {
                eNc[j].numConsultas += eNc[i].numConsultas;
                RemoverElemento(eNc, qE, i);
            }
}

void RemoverElemento(conslPorEspec a[], int *l, int i)
{
    int j; // variável de incrementação
    for (j = i; j < *l - 1; j++)
        a[j] = ConstruirContadorConsl(a[j + 1].especialidade, a[j + 1].numConsultas);
    *l--;
}