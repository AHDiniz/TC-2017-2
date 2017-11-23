/************************************************************************
Trabalho Computacional 2 - Programação 2 - 2017/2 - Ciência da Computação
Grupo: Alan Herculano Diniz e Rafael Belmock Pedruzzi
************************************************************************/

#include  <stdio.h>
#include <stdlib.h>

#define DIM 30 // tamanho máximo de uma string
#define   H 10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define   D  5 // dias úteis da semana (colunas da matriz de agenda de um médico)

// Definição das características relevantes de um médico:
typedef struct
{
    char nome[DIM];          // o nome do médico
    int  id;                 // o número de identificação do médico
    char especialidade[DIM]; // a especialidade do médico
    int agenda[H][D];        // a matriz da agenda do médico
} agMedico;

// Definição das características relevantes de um cliente:
typedef struct
{
    char     nome[DIM];   // o nome do cliente
    int      id;          // o número de identificação do cliente
    long int fone;        // o número de telefone do cliente
    int      idade;       // a idade do cliente
    char     medico[DIM]; // o médico pelo qual o cliente deseja ser atendido
} cliente;

agMedico ConstruirMedico (char *, int, char *, int **);        // função responsável por popular uma variável do tipo agMedico
cliente  ConstruirCliente(char *, int, long int, int, char *); // faz o mesmo que a função anterior, mas para o tipo cliente

int main(int argc, char const *argv[])
{

    return 0;
}

agMedico ConstruirMedico(char nome[], int id, char especialidade[], int agenda[][])
{
    agMedico a; // a variável que será retornada
    int i, j;   // variáveis de incrementação
    // Populando o nome do médico:
    for (i = 0; i < DIM; i++)
        if (nome[i] != NULL)
            a.nome[i] = nome[i];
    a.id = id; // populando o id do médico
    // Populando a especialidade do médico:
    for (i = 0; i < DIM; i++)
        if (especialidade[i] != NULL)
            a.especialidade[i] = especialidade[i];
    // Populando a agenda do médico:
    for (i = 0; i < H; i++)
        for (j = 0; i < D; j++)
            if (agenda[i][j] != NULL)
                a.agenda[i][j] = agenda[i][j];
    return a; // retornando o médico populado
}

cliente ConstruirCliente(char nome[], int id, long int fone, int idade, char medico[])
{
    cliente c; // variável que será retornada
    int i;     // variável de incrementação
    // Populando o nome do cliente:
    for (i = 0; i < DIM; i++)
        if (nome[i] != NULL)
            c.nome[i] = nome[i];
    c.id    = id;    // populando o id do cliente
    c.fone  = fone;  // populando o telefone do cliente
    c.idade = idade; // populando a idade do cliente
    // Populando o médico escolhido pelo cliente:
    for (i = 0; i < DIM; i++)
        if (medico[i] != NULL)
            c.medico[i] = medico[i];
}
