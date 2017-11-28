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
void ImprimirAgenda (int (*)[D]); // Função provisória que imprime cada elemento de uma agenda médica
void AgendaRandom   (int (*)[D]); // Função que constrói uma agenda com elementos randômicos

// Funções para inicializar structs:
agMedico ConstruirMedico (char *, int, int, char *, int, int (*)[D]);    // Função que inicializa um médico
cliente  ConstruirCliente(char *, int, int, long int, int, char *, int); // Função que inicializa um cliente

// Funçõoes para ler dados específicos em arquivos texto:
void ConstruirAgenda(int (*)[D], char *); // Função que cria uma matriz a paartir dos dados de uma agenda médica

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *, int);

// Funções que relacionam médicos e clientes:
void RelacMedClientes(agMedico *, int, cliente *, int); // Função que compara um array de médicos com um array de clientes para que a marcação de consultas seja feita de forma correta
void MarcarConsulta  (agMedico, cliente); // Função que marca uma consulta entre médico e cliente

int main(int *argv, char *argc[])
{
	// Por enquanto somente testes:
	FILE *dm;
	int agenda[H][D];
	AgendaRandom(agenda);
	agMedico medicos[] = {ConstruirMedico("Doutor", 6, 12345, "Doutoria", 8, agenda)};
	LerDadosMedicos(dm, medicos, 1);
	return 0;
}

void AgendaRandom(int agenda[][D])
{
	srand(time(NULL));
	int i, j;
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			agenda[i][j] = rand() % 2 - 1;
}

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

void LerDadosMedicos(FILE *dados, agMedico medicos[], int agl)
{
	int  i, j, k;           // variáveis de incrementação
	int  linhas = 0;        // contador de linhas
	int  carac  = 0;        // contador de caracteres
	char arquivo[100][DIM]; // matriz que recebe os caracteres do arquivo de texto
	// Variáveis que auxiliaram na construção dos médicos:
	char nome[DIM], especialidade[DIM];
	int  id,        agenda[H][D];
	char lixo;
	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	dados = fopen("Conjunto0/dadosMedicos.txt", "r");
	// Verificando se não há nenhum erro:
	if (dados == NULL)
	{
		printf("Cannot open or find file");
		return;
	}
	// Inserindo todos os caracteres do arquivo num array e contando a quantidade de linhas e caracteres:
	for (i = 0; !feof(dados); i++)
		fgets(arquivo[i], DIM, dados); // inicializando as linhas da matriz
	i = j = k = 0;
	for (i = 0; i < strlen(arquivo[0]); i++)
		medicos[0].nome[i] = arquivo[0][i];
	medicos[0].nome[i] = "\0";
	medicos[0].id = (int)strtol(arquivo[1], NULL, 10);
	for (i = 0; i < strlen(arquivo[2]); i++)
		medicos[0].especialidade[i] = arquivo[2][i];
	medicos[0].especialidade[i] = "\0";
	j = 3;
	k += strlen(arquivo[0]) + strlen(arquivo[1]) + strlen(arquivo[2]);
	char agenda[H][D];
	int l;
	for (i = 0, l = 0; arquivo[j][k] == arquivo[j + 1][0]; l++)
	{
		agenda[i][l] = arquivo[j][k];
		if (arquivo[j][k] == '\n')
		{
			j++;
			i++;
		}
		k++;
	}
	fclose(dados); // fechando o arquivo
}

void RelacMedClientes(agMedico medicos[], int ml, cliente clientes[], int cl)
{
	int i, j; // variáveis de incrementação
	// Para cada cliente no array de clientes:
	for (i = 0; i < cl; i++)
		for (j = 0; j < ml; j++) // Procurar no array de médicos um que seja o mesmo que o cliente deseja
			if (strcmp(clientes[i].medico, medicos[j].nome))
				MarcarConsulta(medicos[j], clientes[i]); // E então marcar uma consulta entre o médico e o cliente em questão
}

void MarcarConsulta(agMedico m, cliente c)
{
	int i, j;         // variáveis de incrementação
	int semVagas = 0; // contador de horários ocupados ou indisponíveis
	if (strcmp(m.nome, c.medico)) // verificando se o médico é o que o cliente deseja marcar consulta
	{
		// Mudando o primeiro horário vago encontrado se houver horários livres
		for (i = 0; i < H; i++)
			for (j = 0; j < D; j++)
				if (m.agenda[i][j] == 0)
				{
					m.agenda[i][j] = c.id;
					break;
				}
				else
					semVagas++;
		if (semVagas == H * D)
			printf("O medico esta com a agenda toda ocupada"); // Mensagem de erro se a agenda estiver toda ocupada
		return;
	}
	else
	{
		printf("Erro: o cliente %s nao quer consulta com esse medico %s.\n", c.nome, m.nome); // Mensagem de erro se forem médicos diferentes
	}
}