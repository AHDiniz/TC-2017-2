/************************************************************************
Trabalho Computacional 2 - Programação 2 - 2017/2 - Ciência da Computação
Grupo: Alan Herculano Diniz e Rafael Belmock Pedruzzi
************************************************************************/

/*Coisas a fazer:
	- Ler um arquivo de texto com dados médicos e instanciar e inicializar médicos; (praticamente pronto)
	- Ler um .txt com dados de clientes e modificar as agendas médicas; (praticamente pronto)
	- Criar um arquivo de texto com as agendas médicas de cada semana;
	- Verificar a especialidade com mais consultas; (pronto)
	- Verificar especialidade mais procurada por faixa etária; (0 a 25, 26 a 50, 51 a 75 e 76 a 100)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "consultaPorEspec.h"
#include "agMedico.h"
#include "cliente.h"
#include "leituraDados.h"

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   5 // limite de médicos em um array / um mesmo arquivo
#define CL  45 // limite de pacientes em um array / um mesmo arquivo

// Funções que relacionam médicos e clientes:
void RelacMedClientes(agMedico *, int, cliente *, int); // Função que compara um array de médicos com um array de clientes para que a marcação de consultas seja feita de forma correta
void MarcarConsulta(agMedico *, cliente);				// Função que marca uma consulta entre médico e cliente

// Funções relacinadas com os relatórios:
void TabelasMedicos(FILE *dados, agMedico *, cliente *, cliente *, cliente *, cliente *, int, int, int, int, int);
void SemEspacos(char *, char *);
void Remove(char *, int);

int main(int *argv, char *argc[])
{
	FILE *dados;
	int conjunto, i;				  // conjunto de exemplos a ser avaliado
	int nMed, nCl1, nCl2, nCl3, nCl4; // numero total de medicos e clientes
	agMedico medicos[ML];			  // vetor de medicos
	cliente clientes1[CL];			  // vetor de clientes da semana 1
	cliente clientes2[CL];			  // vetor de clientes da semana 2
	cliente clientes3[CL];			  // vetor de clientes da semana 3
	cliente clientes4[CL];			  // vetor de clientes da semana 4

	printf("Informe o numero do conjunto a ser avaliado (0 - 5): ");
	scanf("%d", &conjunto);

	LerDadosMedicos(dados, medicos, &nMed, conjunto);
	LerDadosClientes(dados, clientes1, clientes2, clientes3, clientes4, &nCl1, &nCl2, &nCl3, &nCl4, conjunto);

	printf("%d %d %ld %ld\n", strcmp(clientes1[0].medico, clientes1[2].medico), strcmp(medicos[0].nome, clientes1[2].medico), strlen(clientes1[0].medico), strlen(clientes1[2].medico));

	RelacMedClientes(medicos, nMed, clientes1, nCl1);

	for(i = 0 ; i < nMed ; i++)
	{
		ImprimirAgenda(medicos[i].agenda);
		printf("\n");
	}

	TabelasMedicos(dados, medicos, clientes1, clientes2, clientes3, clientes4, nMed, nCl1, nCl2, nCl3, nCl4);

	return 0;
}

void RelacMedClientes(agMedico medicos[], int ml, cliente clientes[], int cl)
{
	int i, j; // variáveis de incrementação
	// Para cada cliente no array de clientes:
	for (i = 0; i < cl; i++)
		for (j = 0; j < ml; j++) // Procurar no array de médicos um que seja o mesmo que o cliente deseja
			if (strcmp(clientes[i].medico, medicos[j].nome) == 0)
				MarcarConsulta(&medicos[j], clientes[i]); // E então marcar uma consulta entre o médico e o cliente em questão
}

void MarcarConsulta(agMedico *m, cliente c)
{
	int i, j, k = 0; // variáveis de incrementação

	// Procurando por um horário que esteja vago:
	for (i = 0; i < H && k == 0; i++)
		for (j = 0; j < D; j++)
			if (m->agenda[i][j] == 0)
			{
				m->agenda[i][j] = c.id;
				k++;
				break;
			}
}

void TabelasMedicos(FILE *dados, agMedico medicos[], cliente clientes1[], cliente clientes2[], cliente clientes3[], cliente clientes4[], int nMed, int nCl1, int nCl2, int nCl3, int nCl4)
{

	int i, j; // variáveis de incrementação
	char nomeMed[DIM+4];

	SemEspacos(nomeMed, medicos[0].nome);
	strcat(nomeMed, ".txt");

	dados = fopen(nomeMed, "w");
	fprintf(dados, "Medico: %s", medicos[0].nome);
	fprintf(dados, "\n\n");
	fprintf(dados, "Id: %d\nEspecialidade: %s\n\nQuadro de consultas semanais\n\n", medicos[0].id, medicos[0].especialidade);


	//RelacMedClientes(medicos, nMed, clientes1, nCl1);

	

	fclose(dados);
	
}

void SemEspacos(char d[], char v[])
{

	int i;

	strcpy(d,v);

	for(i = 0 ; i < strlen(d) ; i++)
		if(d[i] == ' ')
			Remove(d, i);
}

void Remove(char d[], int n)
{

	int i;

	for(i = n ; i < strlen(d) ; i++)
		d[i] = d[i+1];
}
