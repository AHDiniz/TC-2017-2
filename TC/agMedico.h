#ifndef AG_MEDICO_H

#define AG_MEDICO_H

#define DIM 50 // tamanho máximo de uma string
#define H 10   // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D 5    // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML 5   // limite de médicos em um array / um mesmo arquivo
#define CL 45  // limite de pacientes em um array / um mesmo arquivo

// Definição das características relevantes de um médico:
typedef struct agMedico
{
    char nome[DIM];          // o nome do médico
    int id;                  // o número de identificação do médico
    char especialidade[DIM]; // a especialidade do médico
    int agenda[H][D];        // a matriz da agenda do médico
} agMedico;

// Funções auxiliares:
void ConstroiAgenda(int (*)[D]); // Função que constrói a agenda generica do medico
void ResetAgenda(int (*)[D]);    // Função que reseta uma agenda médica

// Funçõoes para ler dados específicos em arquivos texto:
void ConstruirAgenda(int (*)[D], int, int *, int); // Função que cria uma matriz a paartir dos dados de uma agenda médica

#endif
