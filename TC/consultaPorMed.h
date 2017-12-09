#ifndef CONSULTA_POR_MED_H

#define CONSULTA_POR_MED_H

#include "agMedico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct consultaPorMed
{
    agMedico medico;
    int consultas;
} consultaPorMed;

// Função que constrói um struct:
consultaPorMed ConstruirConslMed(agMedico);

// Funções auxiliares:
void QSortConsultaMed(agMedico *, int, int); // ordenação por seleção
void BSortConsultaMed(agMedico *, int);      // ordenação por bolha

#endif