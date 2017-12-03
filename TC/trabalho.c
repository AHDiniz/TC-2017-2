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
#include <time.h>

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   5 // limite de médicos em um array / um mesmo arquivo
#define CL  45 // limite de pacientes em um array / um mesmo arquivo

// Definição das características relevantes de um médico:
typedef struct agMedico
{
	char nome[DIM];			 // o nome do médico
	int id;					 // o número de identificação do médico
	char especialidade[DIM]; // a especialidade do médico
	int agenda[H][D];		 // a matriz da agenda do médico
} agMedico;

// Definição das características relevantes de um cliente:
typedef struct cliente
{
	char nome[DIM];   // o nome do cliente
	int id;			  // o número de identificação do cliente
	long int fone;	// o número de telefone do cliente
	int idade;		  // a idade do cliente
	char medico[DIM]; // o médico pelo qual o cliente deseja ser atendido
} cliente;

// Structs auxiliares:
typedef struct conslPorEspec
{
	char          especialidade[DIM]; // a especialidade médica em questão
	int           numConsultas;	      // número de consutas marcadas para a dita especialidade
} conslPorEspec;

// Funções provisórias:
void ImprimirAgenda(int (*)[D]); // Função provisória que imprime cada elemento de uma agenda médica
void AgendaRandom  (int (*)[D]); // Função que constrói uma agenda com elementos randômicos
void ConstroiAgenda(int (*)[D]); // Função que constrói a agenda generica do medico

// Funções para inicializar structs:
agMedico      ConstruirMedico       (char *, int, int, char *, int, int (*)[D]);	// Função que inicializa um médico
cliente       ConstruirCliente      (char *, int, int, long int, int, char *, int); // Função que inicializa um cliente
conslPorEspec ConstruirContadorConsl(char *, int);                                  // Função que inicializa um constador de consultas por especialidade médica

// Funçõoes para ler dados específicos em arquivos texto:
void ConstruirAgenda(int (*)[D], int, int *, int); // Função que cria uma matriz a paartir dos dados de uma agenda médica

// Funções para ler arquivos de texto:
void LerDadosMedicos (FILE *, agMedico *, int *, int);     // Função que lê um arquivo de texto com dados médicos e popula um array de elementos do tipo agMedico
void LerDadosClientes(FILE *, int, cliente *, int *, int); // Função que lê um arquivo de texto com dados de clientes e popula um array de elementos do tipo cliente

// Funções que relacionam médicos e clientes:
void RelacMedClientes(agMedico *, int, cliente *, int); // Função que compara um array de médicos com um array de clientes para que a marcação de consultas seja feita de forma correta
void MarcarConsulta  (agMedico, cliente);				// Função que marca uma consulta entre médico e cliente

// Funções relacinadas com os relatórios:
char *MedicoMaisOcupado   (agMedico *, int);				 // Função que verifica o médico com a maior quantidade de consultas na sua agenda
char *EspecMaisRequisitada(agMedico *, int);	   			 // Função que verifica a especialidade com a maior quantidade de consultas marcadas
char *EspecPorFaixaEtaria (agMedico *, int, cliente *, int); // Função que verifica a especialidade mais procurada para cada faixa etária

// Funções auxiliares:
int  ConsultasMarcadas(agMedico);               // Calcula a quantidade de consultas marcadas que um médico possui em sua agenda
void RemoverRepetidos (conslPorEspec *, int *); // Remove elementos repetidos em um array de relações consulta-especialidade

int main(int *argv, char *argc[])
{
	FILE *dm, *lp1, *lp2, *lp3, *lp4;
	int conjunto;					  // conjunto de exemplos a ser avaliado
	int nMed, nCl1, nCl2, nCl3, nCl4; // numero total de medicos e clientes
	agMedico medicos[ML];			  // vetor de medicos
	cliente clientes1[CL];			  // vetor de clientes da semana 1
	cliente clientes2[CL];			  // vetor de clientes da semana 2
	cliente clientes3[CL];			  // vetor de clientes da semana 3
	cliente clientes4[CL];			  // vetor de clientes da semana 4

	printf("Informe o numero do conjunto a ser avaliado (0 - 5): ");
	scanf("%d", &conjunto);

	LerDadosMedicos(dm, medicos, &nMed, conjunto);

	LerDadosClientes(lp1, 1, clientes1, &nCl1, conjunto);
	RelacMedClientes(medicos, nMed, clientes1, nCl1);

	LerDadosClientes(lp2, 2, clientes2, &nCl2, conjunto);
	RelacMedClientes(medicos, nMed, clientes2, nCl2);

	LerDadosClientes(lp3, 3, clientes3, &nCl3, conjunto);
	RelacMedClientes(medicos, nMed, clientes3, nCl3);

	LerDadosClientes(lp4, 4, clientes4, &nCl4, conjunto);
	RelacMedClientes(medicos, nMed, clientes4, nCl4);
	return 0;
}

void AgendaRandom(int agenda[][D])
{
	srand(time(NULL));
	int i, j;
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			agenda[i][j] = rand() % 2 - 1;
	for (i = 0; i < D; i++)
		agenda[4][i] = -1;
}

void ConstruirAgenda(int agenda[][D], int dia, int horarios[], int tam)
{
	int i, j;
	for (i = 0; i < tam; i++)
		agenda[horarios[i] - 8][dia - 2] = -1;
}

void ConstroiAgenda(int agenda[][D])
{
	int i, j;
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			agenda[i][j] = 0;

	for (i = 0; i < D; i++)
		agenda[4][i] = -1;
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
	strncpy(a.nome, nome, nl);
	// Inicializando o id do médico:
	a.id = id;
	// Inicializando a especialidade do médico:
	strncpy(a.especialidade, especialidade, el);
	// Inicializando a agenda do médico:
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			a.agenda[i][j] = agenda[i][j];
	return a;
}

cliente ConstruirCliente(char nome[], int nl, int id, long int fone, int idade, char medico[], int ml)
{
	cliente c; // variável que será retornada
	// Inicializando o nome do cliente:
	strncpy(c.nome, nome, nl);
	// Inicializando o id do cliente:
	c.id = id;
	// Inicializando o telefone do cliente:
	c.fone = fone;
	// Inicializando a idade do cliente:
	c.idade = idade;
	// Inicializando o médico desejado do cliente:
	strncpy(c.medico, medico, ml);
	return c;
}

conslPorEspec ConstruirContadorConsl(char *especialidade, int consultas)
{
	conslPorEspec c;
	strcpy(c.especialidade, especialidade);
	c.numConsultas = consultas;
	return c;
}

void LerDadosMedicos(FILE *dados, agMedico medicos[], int *nMed, int conjunto)
{
	int i, j, k; // variáveis de incrementação
	int nMedc;   // numero total de medicos

	// Variáveis que auxiliaram na construção dos médicos:
	int tam, dia;
	char indisponivel[DIM];
	int horario[DIM];

	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	switch (conjunto)
	{
		case 0:
			dados = fopen("Conjunto0/dadosMedicos.txt", "r");
			break;
		case 1:
			dados = fopen("Conjunto1/dadosMedicos.txt", "r");
			break;
		case 2:
			dados = fopen("Conjunto2/dadosMedicos.txt", "r");
			break;
		case 3:
			dados = fopen("Conjunto3/dadosMedicos.txt", "r");
			break;
		case 4:
			dados = fopen("Conjunto4/dadosMedicos.txt", "r");
			break;
		case 5:
			dados = fopen("Conjunto5/dadosMedicos.txt", "r");
			break;
		default:
			printf("Conjunto nao existe!                                                                                                           ...idiota\n");
			exit(0);
	}

	// Verificando se não há erro:
	if (dados == NULL)
	{
		printf("Incapaz de abrir ou encontrar arquivo");
		exit(1);
	}

	// Extraindo informacoes dos medicos:
	nMedc = 0;
	do
	{
		ConstroiAgenda(medicos[nMedc].agenda); // Inicializando a matriz agenda generica

		// Nome, id e especialidade:
		fscanf(dados, "%[^\n]\n%d\n%[^\n]\n", medicos[nMedc].nome, &medicos[nMedc].id, medicos[nMedc].especialidade);

		// Extraindo os horarios indisponiveis:
		fscanf(dados, "%d %[^\n]", &dia, indisponivel);

		while (dia != 0)
		{
			// Selecionando os numeros e transferindo-os para um vetor int:
			for (i = 2, j = 0, tam = 0; i < strlen(indisponivel); i++)
				if (indisponivel[i] == '1' || indisponivel[i] == '2' || indisponivel[i] == '3' || indisponivel[i] == '4' || indisponivel[i] == '5' || indisponivel[i] == '6' || indisponivel[i] == '7' || indisponivel[i] == '8' || indisponivel[i] == '9' || indisponivel[i] == '0')
				{
					horario[j] = indisponivel[i] - 48;
					j++;
					tam++;
				}

			// Obtendo os horarios para a matriz agenda: (agrupando os algarismos de dois em dois)
			for (i = 0, j = 0; i < tam; i += 2, j++)
			{
				k = horario[i] * 10 + horario[i + 1];
				horario[j] = k;
			}

			// Incluindo os horarios indisponiveis na agenda:
			ConstruirAgenda(medicos[nMedc].agenda, dia, horario, j);

			// Reinicializando as condicoes da recursao:
			dia = 0;
			fscanf(dados, "%d %[^\n]", &dia, indisponivel);
		}

		nMedc++; // Atualizando o numero de medicos

	} while (!feof(dados));

	*nMed = nMedc;

	fclose(dados); // fechando o arquivo

	// Impressao para teste
	for (i = 0; i < nMedc; i++)
	{
		printf("%s\n%d\n%s\n", medicos[i].nome, medicos[i].id, medicos[i].especialidade);

		ImprimirAgenda(medicos[i].agenda);
	}
}

void LerDadosClientes(FILE *dados, int semana, cliente clientes[], int *nCl, int conjunto)
{

	int i, j, k; // variáveis de incrementação
	int nClien;  // numero total de clientes

	// Variáveis que auxiliaram na construção dos clientes:
	int anoNasc;
	char nascimento[DIM];
	int ano[4];

	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	switch (conjunto)
	{
		case 0:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto0/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto0/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto0/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto0/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		case 1:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto1/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto1/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto1/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto1/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		case 2:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto2/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto2/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto2/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto2/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		case 3:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto3/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto3/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto3/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto3/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		case 4:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto4/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto4/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto4/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto4/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		case 5:
			switch (semana)
			{
			case 1:
				dados = fopen("Conjunto5/listaPacientes-Semana1.txt", "r");
				break;
			case 2:
				dados = fopen("Conjunto5/listaPacientes-Semana2.txt", "r");
				break;
			case 3:
				dados = fopen("Conjunto5/listaPacientes-Semana3.txt", "r");
				break;
			case 4:
				dados = fopen("Conjunto5/listaPacientes-Semana4.txt", "r");
				break;
			}
			break;
		default:
			printf("Conjunto nao existe!\n");
			exit(0);
	}

	// Verificando se não há erro:
	if (dados == NULL)
	{
		printf("Incapaz de abrir ou encontrar arquivo");
		exit(1);
	}

	// Extraindo informacoes dos clientes:
	nClien = 0;
	do
	{
		fscanf(dados, "%[^\n]\n%d\n%ld\n%[^\n]\n%[^\n]\n", clientes[nClien].nome, &clientes[nClien].id, &clientes[nClien].fone, nascimento, clientes[nClien].medico);

		for (i = 6; i < 10; i++)
			ano[i - 6] = nascimento[i] - 48;

		anoNasc = ano[0] * 1000 + ano[1] * 100 + ano[2] * 10 + ano[3];
		clientes[nClien].idade = 2017 - anoNasc;

		nClien++; // Atualizando o numero de clientes

	} while (!feof(dados));

	*nCl = nClien;

	fclose(dados); // fechando o arquivo

	// Impressao para teste
	for (i = 0; i < nClien; i++)
		printf("%s\n%d\n%ld\n%d\n%s\n%d\n\n", clientes[i].nome, clientes[i].id, clientes[i].fone, clientes[i].idade, clientes[i].medico, nClien);
}

void RelacMedClientes(agMedico medicos[], int ml, cliente clientes[], int cl)
{
	int i, j; // variáveis de incrementação
	// Para cada cliente no array de clientes:
	for (i = 0; i < cl; i++)
		for (j = 0; j < ml; j++) // Procurar no array de médicos um que seja o mesmo que o cliente deseja
			if (strcmp(clientes[i].medico, medicos[j].nome) == 0)
				MarcarConsulta(medicos[j], clientes[i]); // E então marcar uma consulta entre o médico e o cliente em questão
}

void MarcarConsulta(agMedico m, cliente c)
{
	int i, j;					  // variáveis de incrementação
	int semVagas = 0;			  // contador de horários ocupados ou indisponíveis
	if (strcmp(m.nome, c.medico) == 0) // verificando se o médico é o que o cliente deseja marcar consulta
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
			printf("O medico %s esta com a agenda toda ocupada para o cliente %s.\n", m.nome, c.nome); // Mensagem de erro se a agenda estiver toda ocupada
		return;
	}
	else
	{
		printf("Erro: o cliente %s nao quer consulta com esse medico %s.\n", c.nome, m.nome); // Mensagem de erro se forem médicos diferentes
	}
}

char *MedicoMaisOcupado(agMedico medicos[], int ml)
{
	int i, j, k;	   // variáveis de incrementação
	int consultas = 0; // quantidade de consultas do médico da iteração atual do loop
	int consulAnt = 0; // quantidade de consultas do médico da iteração anterior
	int desejado = 0;  // médico com a maior quantidade de consultas marcadas

	// Procurando o médico com a maior quantidade de consultas:
	for (i = 0; i < ml; i++) // Varrendo o array de médicos
	{
		consultas = ConsultasMarcadas(medicos[i]); // Calculando a quantidade de consultas marcadas
		// Atualizando os valores do médico desejado e das consultas anterior e atual:
		consulAnt = consultas;
		consultas = 0;
		if (consultas >= consulAnt)
			desejado = i;
	}
	return medicos[desejado].nome; // retornando o médico mais procurado
}

char *EspecMaisRequisitada(agMedico medicos[], int ml)
{
	int i, j, k;                         // variáveis de incrementação
	int qEspec;                          // quantidade de especialidades médicas existentes
	int consulMed[DIM];                  // quantidade de consultas de cada médico
	char especialidades[DIM][DIM];       // contém todas as especialidades de cada médico (com as posições correspondentes)
	conslPorEspec reqEspec;		         // especialidade mais requisitada.
	conslPorEspec consultaPorEspec[DIM]; // Relacionará a quantidade de consultas por especialidade médica existente no array de médicos

	// Colocar todas as especialidades existentes em um array de strings
	for (i = 0; i < ml; i++)
		strcpy(especialidades[i], medicos[i].especialidade);
	
	// Contar as consultas de cada médico:
	for (i = 0; i < ml; i++)
		consulMed[i] = ConsultasMarcadas(medicos[i]);	

	// Armazenar informações no array de relação consulta-especialidade:
	for (i = 0; i < ml; i++)
		consultaPorEspec[i] = ConstruirContadorConsl(especialidades[i], consulMed[i]);
	
	// Procurar e remover por repetições de especialidades:
	qEspec = ml;
	RemoverRepetidos(consultaPorEspec, &qEspec);

	for (i = 0; i < qEspec; i++)
		printf("%s\n", consultaPorEspec[i].especialidade);

	for (i = 0; i < qEspec; i++)
		printf("%d\n", consultaPorEspec[i].numConsultas);

	reqEspec = ConstruirContadorConsl(consultaPorEspec[0].especialidade, consultaPorEspec[0].numConsultas);
	for (i = 1; i < qEspec; i++)
		if (consultaPorEspec[i].numConsultas > reqEspec.numConsultas)
			reqEspec = ConstruirContadorConsl(consultaPorEspec[i].especialidade, consultaPorEspec[i].numConsultas);
	for (i = 0; i < qEspec; i++)
		if (strcmp(medicos[i].especialidade, reqEspec.especialidade) == 0)
			return medicos[i].especialidade;
}

int ConsultasMarcadas(agMedico medico)
{
	int consultas = 0; // variável que conta a quantidade de consultas marcadas
	int i, j;          // variáveis de incrementação
	// Procurando na agenda médica todos os horários que não sejam vagos ou indisponíveis:
	for (i = 0; i < H; i++)
		for (j = 0; j < D; j++)
			if (medico.agenda[i][j] != 0 && medico.agenda[i][j] != -1)
				consultas++;
	return consultas;
}

void RemoverRepetidos(conslPorEspec c[DIM], int *l)
{
	int i, j, k; // variáveis de incrementação

	for (i = 0; i < *l; i++)
		printf("%s\n", c[i].especialidade);

	for (i = *l; i >= 0; i--)
		for (j = 0; j < i; j++)
			if (strcmp(c[j].especialidade, c[i].especialidade) == 0 && c[j].especialidade != NULL && c[i].especialidade != NULL)
			{
				c[j].numConsultas += c[i].numConsultas;
				for (k = j + 1; k < *l; k++)
					c[k] = ConstruirContadorConsl(c[k].especialidade, c[k].numConsultas);
				*l--;
			}
}