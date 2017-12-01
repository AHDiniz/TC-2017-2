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
#define ML   10 // limite de médicos em um array/um mesmo arquivo

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
void ConstroiAgenda   (int (*)[D]); // Função que constrói a agenda generica do medico

// Funções para inicializar structs:
//agMedico ConstruirMedico (char *, int, int, char *, int, int (*)[D]);    // Função que inicializa um médico
//cliente  ConstruirCliente(char *, int, int, long int, int, char *, int); // Função que inicializa um cliente

// Funçõoes para ler dados específicos em arquivos texto:
void ConstruirAgenda(int agenda[][D], int dia,int horarios[], int tam); // Função que acressenta a matriz agenda dados dos horarios

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *, int *nMedicos, int conjunto);

// Funções que modificam informações de médicos ou clientes:
//void MarcarConsulta(agMedico, cliente); // Função que marca uma consulta entre médico e cliente

int main(int argv, char *argc[])
{
	// Por enquanto somente testes:
	FILE *dm;
	int conjunto;	// conjunto de exemplos a ser avaliado
	int nMedicos;	// numero total de medicos
	agMedico medicos[ML];

	printf("Informe o numero do conjunto a ser avaliado (0 - 5): ");
	scanf("%d", &conjunto);

	LerDadosMedicos(dm, medicos, &nMedicos, conjunto);
	return 0;
}

void ConstroiAgenda(int agenda[][D])
{
	int i, j;
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
				agenda[i][j] = 0;

	for(i = 0 ; i < D ; i++)
		agenda[4][i] = -1;
}

void ConstruirAgenda(int agenda[][D], int dia,int horarios[], int tam)
{
	int i, j;
	for(i = 0 ; i < tam ; i++)
		agenda[horarios[i]-8][dia-2] = -1;
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
/*
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
void LerDadosMedicos(FILE *dados, agMedico medicos[], int *nMedicos, int conjunto)
{
	int  i, j, k;           // variáveis de incrementação
	int nMedc;				// numero total de medicos

	// Variáveis que auxiliaram na construção dos médicos:
	char nome[DIM], especialidade[DIM];
	int  id, tam, dia;
	char indisponivel[DIM];
	int horario[DIM];

	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	switch(conjunto){
		case 0 : dados = fopen("Conjunto0/dadosMedicos.txt", "r");
				break;
		case 1 : dados = fopen("Conjunto1/dadosMedicos.txt", "r");
				break;
		case 2 : dados = fopen("Conjunto2/dadosMedicos.txt", "r");
				break;
		case 3 : dados = fopen("Conjunto3/dadosMedicos.txt", "r");
				break;
		case 4 : dados = fopen("Conjunto4/dadosMedicos.txt", "r");
				break;
		case 5 : dados = fopen("Conjunto5/dadosMedicos.txt", "r");
				break;
		default: printf("Conjunto nao existe!                                                                                                           ...idiota\n");
				exit(0);
	}

	// Verificando se não há nenhum erro:
	if (dados == NULL)
	{
		printf("Cannot open or find file");
		exit(1);
	}

	// Extraindo informacoes dos medicos:
	nMedc = 0;
	do{
		ConstroiAgenda(medicos[nMedc].agenda); // Inicializando a matriz agenda generica

		// Nome, id e especialidade:
		fscanf(dados, "%[^\n]\n%d\n%[^\n]\n", medicos[nMedc].nome, &medicos[nMedc].id, medicos[nMedc].especialidade);

		// Extraindo os horarios indisponiveis:
		fscanf(dados, "%d %[^\n]", &dia, indisponivel);

		while(dia != 0){
			// Selecionando os numeros e transferindo-os para um vetor int:
			for(i = 2, j = 0, tam = 0 ; i < strlen(indisponivel) ; i++)
				if(indisponivel[i] == '1' || indisponivel[i] == '2' || indisponivel[i] == '3' || indisponivel[i] == '4' || indisponivel[i] == '5' || indisponivel[i] == '6' || indisponivel[i] == '7' || indisponivel[i] == '8' || indisponivel[i] == '9' || indisponivel[i] == '0')
				{
					horario[j] = indisponivel[i]-48;
					j++;
					tam++;
				}

			// Obtendo os horarios para a matriz agenda: (agrupando os algarismos de dois em dois)
			for(i = 0, j = 0 ; i < tam ; i += 2, j++){
				k = horario[i]*10 + horario[i+1];
				horario[j] = k;
			}

			// Incluindo os horarios indisponiveis na agenda:
			ConstruirAgenda(medicos[nMedc].agenda, dia, horario, j);

			// Reinicializando as condicoes da recursao:
			dia = 0;
			fscanf(dados, "%d %[^\n]", &dia, indisponivel);
		}

		nMedc++; // Atualizando o numero de medicos

	}while(!feof(dados));

	*nMedicos = nMedc;

	// Impressao para teste
	for(i = 0 ; i < nMedc ; i++)
	{
	printf("%s\n%d\n%s\n", medicos[i].nome, medicos[i].id, medicos[i].especialidade);

	ImprimirAgenda(medicos[i].agenda);
	}





/*
	// Inserindo todos os caracteres do arquivo num array e contando a quantidade de linhas e caracteres:
	for (i = 0; !feof(dados); i++)
		fgets(arquivo[i], DIM, dados); // inicializando as linhas da matriz

	fclose(dados); // fechando o arquivo

	// Extraindo informacoes dos medicos:
	j = m = 0;
	do{
		// Nome:
		for (i = 0; i < strlen(arquivo[0]); i++)
			medicos[m].nome[i] = arquivo[0][i];

		medicos[m].nome[i-2] = '\0';
		j++;

		// Id:
		medicos[m].id = (int)strtol(arquivo[1], NULL, 10);
		j++;

		// Especialidade:
		for (i = 0; i < strlen(arquivo[2]); i++)
			medicos[m].especialidade[i] = arquivo[2][i];

		medicos[m].especialidade[i-2] = '\0';
		j++;

		// Horarios indisponiveis:
		for (i = 0, l = 0; arquivo[j][1] != '\n'; l++)
		{
		
			if (arquivo[j][l] == '\n')
			{
				indisponivel[m][i][l-1] = '\0';
				j++;
				i++;
				l = -1;
			}
			else
				indisponivel[m][i][l] = arquivo[j][l];
		}
		j++;
		m++;
	}while(j != k);

	printf("%s\n%d\n%s\n%s", medicos[0].nome, medicos[0].id, medicos[0].especialidade, indisponivel[0][0]);
	printf("%s\n%d\n%s\n%s", medicos[1].nome, medicos[1].id, medicos[1].especialidade, indisponivel[1][0]);
	printf("%s\n%d\n%s\n%s", medicos[2].nome, medicos[2].id, medicos[2].especialidade, indisponivel[2][0]);
	printf("%s\n%d\n%s\n%s", medicos[3].nome, medicos[3].id, medicos[3].especialidade, indisponivel[3][0]);
*/
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
		printf("Erro: o cliente nao quer consulta com esse medico.\n"); // Mensagem de erro se forem médicos diferentes
	}
}
