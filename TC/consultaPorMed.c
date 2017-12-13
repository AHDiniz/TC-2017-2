#include "consultaPorMed.h"

consultaPorMed ConstruirConslMed(agMedico medico)
{
    consultaPorMed c;

    c.medico = ConstruirMedico(medico.nome, (int)strlen(medico.nome), medico.id, medico.especialidade, (int)strlen(medico.especialidade), medico.agenda);
    c.consultas = ConsultasMarcadas(medico);

    return c;
}

void QSortConsultaMed(agMedico medicos[], int inicio, int fim)
{
    int i, j, k; // variáveis de incrementação e decrementação
    int pivot; // ponto de referência para a seleção
    consultaPorMed aux;
    
    consultaPorMed c[10]; // Declarando dinamicamente um array de relações médico / número de consultas

    if (inicio < fim) // Condição de parada do quick sort
    {
        for (i = 0; i < (fim - inicio); i++)
            *(c + i) = ConstruirConslMed(medicos[i]);

        pivot = i = inicio;
        j = fim;

        while (i < j)
        {
            while ((c + i)->consultas < (c + pivot)->consultas && i < fim)
                i++;
            while ((c + j)->consultas > (c + pivot)->consultas)
                j--;

            if (i < j)
            {
                aux = *(c + i);
                *(c + i) = *(c + j);
                *(c + j) = aux;
            }
        }

        aux = *(c + pivot);
        *(c + pivot) = *(c + j);
        *(c + j) = aux;

        for (k = 0; k < (fim - inicio); k++)
            medicos[k] = (c + k)->medico;

        free(c);
        QSortConsultaMed(medicos, inicio, j - 1);
        QSortConsultaMed(medicos, j + 1, fim);
    }
}

void BSortConsultaMed(agMedico medicos[], int ml)
{
    int i, j; // variáveis de incrementação
    consultaPorMed aux;
    consultaPorMed c[10];
    
    for (i = 0; i < ml; i++)
        *(c + i) = ConstruirConslMed(medicos[i]);
    
    for (i = 0; i < ml - 1; i++)
        for (j = 0; j < ml - i - 1; j++)
            if ((c + j)->consultas > (c + j + 1)->consultas)
            {
                aux = *(c + j);
                *(c + j) = *(c + j + 1);
                *(c + j + 1) = aux;
            }

    for (i = 0; i < ml; i++)
        medicos[i] = (c + i)->medico;

    free(c);
}

int CompareConslMed(const void *a, const void *b)
{
    if (((consultaPorMed *)a)->consultas < ((consultaPorMed *)b)->consultas)
        return -1;
    else if (((consultaPorMed *)a)->consultas == ((consultaPorMed *)b)->consultas)
        return 0;
    else
        return 1;
}