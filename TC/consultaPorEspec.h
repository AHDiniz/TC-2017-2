#ifndef CONSULTA_POR_ESPEC_H

#define CONSULTA_POR_ESPEC_H

#define DIM 50 // tamanho máximo de uma string
#define H 10   // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D 5    // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML 5   // limite de médicos em um array / um mesmo arquivo
#define CL 45  // limite de pacientes em um array / um mesmo arquivo

typedef struct conslPorEspec
{
    char especialidade[DIM]; // a especialidade médica em questão
    int numConsultas;        // número de consutas marcadas para a dita especialidade
} conslPorEspec;

conslPorEspec ConstruirContadorConsl(char *, int); // Função que inicializa um constador de consultas por especialidade médica
void RemoverRepetidos(conslPorEspec *, int *); // Remove os itens repetidos de um array de relações especialidade-número de consultas
void RemoverElemento(conslPorEspec *, int *, int); // Remove um elemento especcífico de um array

#endif
