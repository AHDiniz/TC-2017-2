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

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   5 // limite de médicos em um array / um mesmo arquivo
#define CL  45 // limite de pacientes em um array / um mesmo arquivo

// Funções que relacionam médicos e clientes:
void RelacMedClientes(agMedico *, int, cliente *, int); // Função que compara um array de médicos com um array de clientes para que a marcação de consultas seja feita de forma correta
void MarcarConsulta(agMedico *, cliente);					// Função que marca uma consulta entre médico e cliente

// Funções relacinadas com os relatórios:
void RankingMedico(agMedico *, int);					   // Função que faz um ranking dos médicos com relação às consultas
void EspecMaisRequisitada(agMedico *, int, int);		   // Função que verifica a especialidade com a maior quantidade de consultas marcadas
void EspecPorFaixaEtaria(agMedico *, int, cliente *, int); // Função que verifica a especialidade mais procurada para cada faixa etária

// Funções auxiliares:
// int MaiorNumConsulMed(consultaPorMed *, int); // Função que retorna o maior número de consultas existente em um array de relações médico/número de consultas

int main(int *argv, char *argc[])
{
	FILE *dados;
	int conjunto;					  // conjunto de exemplos a ser avaliado
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

	RelacMedClientes(medicos, nMed, clientes1, nCl1);
	RelacMedClientes(medicos, nMed, clientes2, nCl2);
	RelacMedClientes(medicos, nMed, clientes3, nCl3);
	RelacMedClientes(medicos, nMed, clientes4, nCl4);

	RankingMedico(medicos, nMed);

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

void RankingMedico(agMedico medicos[], int ml)
{
	int i; // variável de incrementação

	consultaPorMed *c = (consultaPorMed *) malloc((ml - 1) * sizeof(consultaPorMed)); // Criando dinamicamente um array de relações médico/número de consultas
	
	for (i = 0; i < ml; i++) // Populando o array criado
		*(c + i) = ConstruirConslMed(medicos[i]);

	qsort(c, ml - 1, sizeof(consultaPorMed), CompareConslMed); // Ordenando o array criado
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