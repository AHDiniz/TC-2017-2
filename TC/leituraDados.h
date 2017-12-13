#ifndef LEITURA_DADOS_H

#define LEITURA_DADOS_H

#include <stdio.h>
#include "cliente.h"
#include "agMedico.h"

#define DIM 50 // tamanho máximo de uma string
#define H 10   // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D 5    // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML 5   // limite de médicos em um array / um mesmo arquivo
#define CL 45  // limite de pacientes em um array / um mesmo arquivo

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *, int *, int);      // Função que lê um arquivo de texto com dados médicos e popula um array de elementos do tipo agMedico
// Função que lê um arquivo de texto com dados de clientes e popula um array de elementos do tipo cliente:
void LerDadosClientes(FILE *, cliente *, cliente *, cliente *, cliente *, int *, int *, int *, int *, int);
void LerClientes(FILE *, cliente *, int *); // Função auxiliar a LerDadosClientes

// Funções auxiliares:
int SomenteInts(int *, char *); // transfere os numeros de um vetor char para um vetor int e retorna seu tamanho
void Remove(char *, int);

#endif
