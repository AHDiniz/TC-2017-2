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
	- Verificar especialidade mais proocurada por faixa etária;
*/

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <time.h>

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   5 // limite de médicos em um array/um mesmo arquivo

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
//void ImprimirAgenda (int (*)[D]); // Função provisória que imprime cada elemento de uma agenda médica

// Funções para inicializar structs:
//agMedico ConstruirMedico (char *, int, int, char *, int, int (*)[D]);    // Função que inicializa um médico
//cliente  ConstruirCliente(char *, int, int, long int, int, char *, int); // Função que inicializa um cliente

// Funçõoes para ler dados específicos em arquivos texto:
//void ConstruirAgenda(int (*)[D], char *); // Função que cria uma matriz a paartir dos dados de uma agenda médica

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *, int);

int main(int argv, char *argc[])
{
	// Por enquanto somente testes:
	FILE *dm;
	agMedico medicos;
	//int agenda[H][D];
	//ConstruirAgenda(agenda);
	//agMedico medicos[] = {ConstruirMedico("Doutor", 6, 12345, "Doutoria", 8, agenda)};
	LerDadosMedicos(dm, &medicos, 1);
	return 0;
}
/*
void ConstruirAgenda(int agenda[][D], char agChar[])
{
	int i, j;
		
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
	c.id    = id;
	// Inicializando o telefone do cliente:
	c.fone  = fone;
	// Inicializando a idade do cliente:
	c.idade = idade;
	// Inicializando o médico desejado do cliente:
	for (i = 0; i < ml; i++)
		c.medico[i] = medico[i];
	return c;
}
*/
void LerDadosMedicos(FILE *dados, agMedico medicos[], int agl)
{
	int  i, j, k, l;        // variáveis de incrementação
	int  linhas = 0;        // contador de linhas
	int  carac  = 0;        // contador de caracteres
	char arquivo[100][DIM]; // matriz que recebe os caracteres do arquivo de texto
	char agenda[H][D];      // matriz que recebe os horarios indisponiveis

	// Variáveis que auxiliaram na construção dos médicos:
	char nome[DIM], especialidade[DIM];
	int  id;//, agenda[H][D];

	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	dados = fopen("Conjunto0/dadosMedicos.txt", "r");

	// Verificando se não há nenhum erro:
	if (dados == NULL)
	{
		printf("Nao foi possivel abrir ou encontrar o arquivo\n");
		return;
	}
	// Inserindo todos os caracteres do arquivo num array e contando a quantidade de linhas e caracteres:
	for (i = 0; !feof(dados); i++)
		fgets(arquivo[i], DIM, dados); // inicializando as linhas da matriz

	// Inserindo o nome do medico:
	j = k = 0;
	for (i = 0; i < strlen(arquivo[0]); i++)
		medicos[0].nome[i] = arquivo[0][i];

	medicos[0].nome[i] = '\0';

	// Inserindo o id:
	medicos[0].id = (int)strtol(arquivo[1], NULL, 10);

	// Inserindo a especialidade:
	for (i = 0; i < strlen(arquivo[2]); i++)
		medicos[0].especialidade[i] = arquivo[2][i];

	medicos[0].especialidade[i] = '\0';

	// Inserindo os horarios indisponiveis:
	j = 3;
	k += strlen(arquivo[0]) + strlen(arquivo[1]) + strlen(arquivo[2]);

	for (i = 0, l = 0; arquivo[j][k] != '\n' && arquivo[j + 1][0] != '\n'; l++, k++)
	{
		agenda[i][l] = arquivo[j][k];
		if (arquivo[j][k] == '\n')
		{
			j++;
			i++;
		}
	}

	fclose(dados); // fechando o arquivo

	printf("|%s|\n|%d|\n|%s|\n", medicos[0].nome, medicos[0].id, medicos[0].especialidade);
	for(j = 0 ; j < i-1 ; j++)
		printf("%s\n", agenda[j]);
}
