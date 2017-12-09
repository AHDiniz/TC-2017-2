#include "agMedico.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

agMedico ConstruirMedico(char nome[], int nl, int id, char especialidade[], int el, int agenda[][D])
{
    agMedico a; // variável que será retornada
    int i, j;   // variáveis de incrementação
    // Inicializando o nome do médico:
    strncpy(a.nome, nome, nl);
    // Inicializando o id do médico:
    a.id = id;
    // Inicializando a especialidade do médico:
    strncpy(a.especialidade, especialidade, el);
    // Inicializando a agenda do médico:
    for (i = 0; i < H; i++)
        for (j = 0; j < D; j++)
            a.agenda[i][j] = agenda[i][j];
    return a;
}

int ConsultasMarcadas(agMedico medico)
{
    int consultas = 0; // variável que conta a quantidade de consultas marcadas
    int i, j;          // variáveis de incrementação
    // Procurando na agenda médica todos os horários que não sejam vagos ou indisponíveis:
    for (i = 0; i < H; i++)
        for (j = 0; j < D; j++)
            if (medico.agenda[i][j] != 0 && medico.agenda[i][j] != -1)
                consultas++;
    return consultas;
}

void AgendaRandom(int agenda[][D])
{
    srand(time(NULL));
    int i, j;
    for (i = 0; i < H; i++)
        for (j = 0; j < D; j++)
            agenda[i][j] = rand() % 2 - 1;
    for (i = 0; i < D; i++)
        agenda[4][i] = -1;
}

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

void ImprimirAgenda(int agenda[][D])
{
    int i, j;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < D; j++)
            printf(" %3d", agenda[i][j]);
        printf("\n");
    }
}

void QSortConsulta(agMedico medicos[], int inicio, int fim)
{
    int pivot, i, j, aux;
    agMedico mAux;
    
    int *consultas = (int *)malloc(abs(fim - inicio) * (sizeof(int))); // Construindo dinamicamente um array que terá a quantidade de consultas para cada médico de acordo com a posição
    for (i = 0; i <= abs(fim - inicio); i++) // Populando o array de quantidade de consultas marcadas por médico
        *(consultas + i) = ConsultasMarcadas(medicos[i]);

    if (inicio < fim) // Se o índice inicial for menor que o final, o pivô será escolhido:
    {
        pivot = i = inicio;
        j = fim;
        
        // Fazendo o quick sort:
        while (i < j)
        {
            while (*(consultas + i) <= *(consultas + pivot) && i < fim)
                i++;
            while (*(consultas + i) > *(consultas + pivot))
                j--;
            if (i < j)
            {
                aux = *(consultas + i);
                mAux = medicos[i];
                *(consultas + i) = *(consultas + j);
                medicos[i] = medicos[j];
                *(consultas + j) = aux;
                medicos[j] = mAux;
            }
        }

        aux = *(consultas + pivot);
        mAux = medicos[pivot];
        *(consultas + pivot) = *(consultas + j);
        medicos[pivot] = medicos[j];
        *(consultas + j) = aux;
        medicos[j] = mAux;

        free(consultas); // Limpando o espaço de memória usado

        QSortConsulta(medicos, inicio, j - 1);
        QSortConsulta(medicos, j + 1, fim);
    }
}