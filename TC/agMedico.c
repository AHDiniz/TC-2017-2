#include "agMedico.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ConstruirAgenda(int agenda[][D], int dia, int horarios[], int tam)
{
    int i, j;
    for (i = 0; i < tam; i++)
        agenda[horarios[i] - 8][dia - 2] = -1;
}

void ConstroiAgenda(int agenda[][D])
{
    int i, j;
    for (i = 0; i < H; i++)
        for (j = 0; j < D; j++)
            agenda[i][j] = 0;

    for (i = 0; i < D; i++)
        agenda[4][i] = -1;
}

void ResetAgenda(int agenda[][D])
{
    int i, j; // variáveis de incrementação
    for (i = 0; i < H; i++)
        for (j = 0; j < D; j++)
            if (agenda[i][j] != 0 && agenda[i][j] != -1)
                agenda[i][j] = 0; // Para cada item da matriz que seja um horário vago, ele deixará de ser vago
}
