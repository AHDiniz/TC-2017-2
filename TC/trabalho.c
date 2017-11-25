/************************************************************************
Trabalho Computacional 2 - Programação 2 - 2017/2 - Ciência da Computação
Grupo: Alan Herculano Diniz e Rafael Belmock Pedruzzi
************************************************************************/

/*Coisas a fazer:
	- Ler um arquivo de texto com dados médicos e instanciar e inicializar médicos;
	- Ler um .txt com dados de clientes e modificar as agendas médicas;
	- Criar um arquivo de texto com as agendas médicas de cada semana;
	- Verificar o médico com mais consultas;
	- Verificar a especialidade com mais consultas;
	- Verificar a faixa etária mais atendida;
*/

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <time.h>

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)

// Definição das características relevantes de um médico:
typedef struct agMedico
{
    char     nome[DIM];          // o nome do médico
    int      id;                 // o número de identificação do médico
    char     especialidade[DIM]; // a especialidade do médico
    int      agenda[H][D];       // a matriz da agenda do médico
} agMedico;

// Definição das características relevantes de um cliente:
typedef struct cliente
{
    char     nome[DIM];   // o nome do cliente
    int      id;          // o número de identificação do cliente
    long int fone;        // o número de telefone do cliente
    int      idade;       // a idade do cliente
    char     medico[DIM]; // o médico pelo qual o cliente deseja ser atendido
} cliente;

// Funções provisórias:
void ConstruirAgenda(int (*)[D]); // Função provisória que cria uma matriz randômica que representará uma agenda médica
void ImprimirAgenda (int (*)[D]); // Função provisória que imprime cada elemento de uma agenda médica

// Funções para inicializar structs:
agMedico ConstruirMedico (char *, int, int, char *, int, int (*)[D]);    // Função que inicializa um médico
cliente  ConstruirCliente(char *, int, int, long int, int, char *, int); // Função que inicializa um cliente

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *);

int main(int argv, char *argc[])
{
	// Por enquanto somente testes:
	FILE *dm;
	int agenda[H][D];
	ConstruirAgenda(agenda);
	agMedico medicos[] = {ConstruirMedico("Doutor", 6, 123, "Doutoria", 8, agenda)};
	LerDadosMedicos(dm, medicos);
    return 0;
}

void ConstruirAgenda(int agenda[][D])
{
	int i, j;
	srand(time(NULL));
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			if (i != 4)
				agenda[i][j] = rand() % 2 - 1;
			else
				agenda[i][j] = -1;	
}

void ImprimirAgenda(int agenda[][D])
{
	int i, j;
	for (i = 0; i < H; i++)
	{
		for (j = 0; j < D; j++)
			printf("%3d", agenda[i][j]);
		printf("\n");
	}
}

agMedico ConstruirMedico(char nome[], int nl, int id, char especialidade[], int el, int agenda[][D])
{
	agMedico a; // variável que será retornada
	int i, j;   // variáveis de incrementação
	// Inicializando o nome do médico:
	for (i = 0; i < nl; i++)
		a.nome[i] = nome[i];
	// Inicializando o id do médico:
	a.id = id;
	// Inicializando a especialidade do médico:
	for (i = 0; i < el; i++)
		a.especialidade[i] = especialidade[i];
	// Inicializando a agenda do médico:
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			a.agenda[i][j] = agenda[i][j];
	return a;
}

cliente ConstruirCliente(char nome[], int nl, int id, long int fone, int idade, char medico[], int ml)
{
	cliente c; // variável que será retornada
	int i;     // variável de incrementação
	// Inicializando o nome do cliente:
	for (i = 0; i < nl; i++)
		c.nome[i] = nome[i];
	// Inicializando o id do cliente:
	c.id = id;
	// Inicializando o telefone do cliente:
	c.fone = fone;
	// Inicializando a idade do cliente:
	c.idade = idade;
	// Inicializando o médico desejado do cliente:
	for (i = 0; i < ml; i++)
		c.medico[i] = medico[i];
	return c;
}

void LerDadosMedicos(FILE *dados, agMedico medicos[])
{
	int i, j; // variáveis de incrementação
	dados = fopen("dadosMedicos.txt", "r"); // inicializando o ponteiro do arquivo desejado
	// Verificando se não há nenhum erro:
	if (dados == NULL)
	{
		printf("Cannot open or find file");
		return;
	}
	fclose(dados);
}