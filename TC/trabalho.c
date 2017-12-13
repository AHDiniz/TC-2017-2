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
#include "consultaPorMed.h"

#define DIM 50 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   5 // limite de médicos em um array / um mesmo arquivo
#define CL  45 // limite de pacientes em um array / um mesmo arquivo

// Funções que relacionam médicos e clientes:
void RelacMedClientes(agMedico *, int, cliente *, int, relacMC *, int *); // Função que compara um array de médicos com um array de clientes para que a marcação de consultas seja feita de forma correta
void MarcarConsulta(agMedico *, cliente);								  // Função que marca uma consulta entre médico e cliente

// Funções relacinadas com os relatórios:
void RankingMedico(agMedico *, int);					   // Função que faz um ranking dos médicos com relação às consultas
void EspecMaisRequisitada(agMedico *, int, int);		   // Função que verifica a especialidade com a maior quantidade de consultas marcadas
void EspecPorFaixaEtaria(agMedico *, int, cliente *, int); // Função que verifica a especialidade mais procurada para cada faixa etária

// Funções relacinadas com os relatórios:
void TabelasMedicos(FILE *, agMedico *, cliente *, cliente *, cliente *, cliente *, int, int, int, int, int, relacMC *, int *);
void ImprimeTabela(FILE *, agMedico *, int, int);

// Relaciona o nome e a especialidade do médico com a idade do cliente
typedef struct relacMC
{
	char medico[DIM];
	char especialidade[DIM];
	int idade;
} relacMC;

// Funções auxiliares:
// int MaiorNumConsulMed(consultaPorMed *, int); // Função que retorna o maior número de consultas existente em um array de relações médico/número de consultas
void SemEspacos(char *, char *);

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
	relacMC lista[DIM];
	int nRel = 0;

	printf("Informe o numero do conjunto a ser avaliado (0 - 5): ");
	scanf("%d", &conjunto);

	LerDadosMedicos(dados, medicos, &nMed, conjunto);
	LerDadosClientes(dados, clientes1, clientes2, clientes3, clientes4, &nCl1, &nCl2, &nCl3, &nCl4, conjunto);

	TabelasMedicos(dados, medicos, clientes1, clientes2, clientes3, clientes4, nMed, nCl1, nCl2, nCl3, nCl4, lista, &nRel);

	for (i = 0; i < nRel; i++)
		printf("%s\n%s\n%d\n\n", lista[i].medico, lista[i].especialidade, lista[i].idade);

	return 0;
}

void RelacMedClientes(agMedico medicos[], int ml, cliente clientes[], int cl, relacMC lista[], int *nRel)
{
	int i, j, nc = *nRel; // variáveis de incrementação
	// Para cada cliente no array de clientes:
	for (i = 0; i < cl; i++)
		for (j = 0; j < ml; j++) // Procurar no array de médicos um que seja o mesmo que o cliente deseja
			if (strcmp(clientes[i].medico, medicos[j].nome) == 0)
			{
				MarcarConsulta(&medicos[j], clientes[i]); // E então marcar uma consulta entre o médico e o cliente em questão
				strcpy(lista[nc].medico, medicos[j].nome);
				strcpy(lista[nc].especialidade, medicos[j].especialidade);
				lista[nc].idade = clientes[i].idade;
				nc++;
			}
	nc -= *nRel;
	*nRel += nc;
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

void RankingMedico(agMedico medicos[], int ml)
{
	int i; // variável de incrementação
	int consl[10]; // número de consultas por médico
	QSortConsultaMed(medicos, 0, ml - 1); // Ordenando o array de médicos de acordo com o número de consultas

}

void EspecMaisRequisitada(agMedico medicos[], int ml, int conjunto)
{
	int i;								 // variável de incrementação
	int qEspec;							 // quantidade de especialidades médicas existentes
	int consulMed[DIM];					 // quantidade de consultas de cada médico
	char especialidades[DIM][DIM];		 // contém todas as especialidades de cada médico (com as posições correspondentes)
	conslPorEspec reqEspec;				 // especialidade mais requisitada.
	conslPorEspec consultaPorEspec[DIM]; // Relacionará a quantidade de consultas por especialidade médica existente no array de médicos
	FILE *arq;

	qEspec = ml;
	for (i = 0; i < ml; i++)
		consultaPorEspec[i] = ConstruirContadorConsl(medicos[i].especialidade, ConsultasMarcadas(medicos[i]));

	RemoverRepetidos(consultaPorEspec, &qEspec);
}

void EspecPorFaixaEtaria(agMedico medicos[], int ml, cliente clientes[], int cl)
{
	/*O que deve ser feito:
		1 - Separar os clientes por faixa etária (provavelmente em uma matriz);
		2 - Calcular a especialidade mais requisitada para cada faixa etária:
			a) Em cada linha da matriz, criar um array de médicos
			b) Calcular a especialidade mais requisitada para cada array de médicos e printar como a faixa etária
	*/
}

void TabelasMedicos(FILE *dados, agMedico medicos[], cliente clientes1[], cliente clientes2[], cliente clientes3[], cliente clientes4[], int nMed, int nCl1, int nCl2, int nCl3, int nCl4, relacMC lista[], int *nRel)
{

	int i; // variáveis de incrementação
	char nomeMed[ML][DIM];

	for (i = 0; i < nMed; i++)
	{
		strcpy(nomeMed[i], medicos[i].nome);
		nomeMed[i][strlen(nomeMed[i]) - 1] = '.';
		strcat(nomeMed[i], "txt");
		SemEspacos(nomeMed[i], medicos[i].nome);
	}

	//printf("%s\n", nomeMed[0]);

	for (i = 0; i < nMed; i++)
	{
		dados = fopen(nomeMed[i], "w");
		fprintf(dados, "Medico: %s\nId: %d\nEspecialidade: %s\n\nQuadro de consultas semanais", medicos[i].nome, medicos[i].id, medicos[i].especialidade);
		fclose(dados);
	}

	RelacMedClientes(medicos, nMed, clientes1, nCl1, lista, nRel);
	for (i = 0; i < nMed; i++)
	{
		dados = fopen(nomeMed[i], "a");
		ImprimeTabela(dados, medicos, i, 1);
		fclose(dados);
		ResetAgenda(medicos[i].agenda);
	}

	RelacMedClientes(medicos, nMed, clientes2, nCl2, lista, nRel);
	for (i = 0; i < nMed; i++)
	{
		dados = fopen(nomeMed[i], "a");
		ImprimeTabela(dados, medicos, i, 2);
		fclose(dados);
		ResetAgenda(medicos[i].agenda);
	}

	RelacMedClientes(medicos, nMed, clientes3, nCl3, lista, nRel);
	for (i = 0; i < nMed; i++)
	{
		dados = fopen(nomeMed[i], "a");
		ImprimeTabela(dados, medicos, i, 3);
		fclose(dados);
		ResetAgenda(medicos[i].agenda);
	}

	RelacMedClientes(medicos, nMed, clientes4, nCl4, lista, nRel);
	for (i = 0; i < nMed; i++)
	{
		dados = fopen(nomeMed[i], "a");
		ImprimeTabela(dados, medicos, i, 4);
		fclose(dados);
		ResetAgenda(medicos[i].agenda);
	}
}

void ImprimeTabela(FILE *dados, agMedico medicos[], int m, int semana)
{
	int i, j = 0;

	fprintf(dados, "\n\nSemana %d:\n\n        2a   3a   4a   5a   6a", semana);

	do
	{
		switch (j)
		{
			case 0:
				fprintf(dados, "\n  8-9");
				break;
			case 1:
				fprintf(dados, "\n 9-10");
				break;
			case 2:
				fprintf(dados, "\n10-11");
				break;
			case 3:
				fprintf(dados, "\n11-12");
				break;
			case 4:
				fprintf(dados, "\n12-13");
				break;
			case 5:
				fprintf(dados, "\n13-14");
				break;
			case 6:
				fprintf(dados, "\n14-15");
				break;
			case 7:
				fprintf(dados, "\n15-16");
				break;
			case 8:
				fprintf(dados, "\n16-17");
				break;
			case 9:
				fprintf(dados, "\n17-18");
				break;
		}

		for (i = 0; i < D; i++)
			fprintf(dados, "  %3d", medicos[m].agenda[j][i]);

		j++;

	} while (j < H);
}

void SemEspacos(char d[], char v[])
{

	int i;

	for (i = 0; i < strlen(d); i++)
		if (d[i] == ' ')
			Remove(d, i);
}
