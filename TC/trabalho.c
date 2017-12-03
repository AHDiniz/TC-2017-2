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
	- Remover essa lista antes de enviar;
*/

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <time.h>

#define DIM 30 // tamanho máximo de uma string
#define H   10 // quantidade de intervalos de uma hora durante o dia (linhas da matriz de agenda de um médico)
#define D    5 // dias úteis da semana (colunas da matriz de agenda de um médico)
#define ML   10 // limite de médicos em um array/um mesmo arquivo
#define CL   45 // limite de pacientes em um array/um mesmo arquivo

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
    long long int fone;        // o número de telefone do cliente
    int      idade;       // a idade do cliente
    char     medico[DIM]; // o médico pelo qual o cliente deseja ser atendido
} cliente;

// Funções provisórias:
void ImprimirAgenda (int (*)[D]); // Função provisória que imprime cada elemento de uma agenda médica

// Funcoes para construcao da agenda do medico:
void ConstroiAgenda   (int (*)[D]);                  // função que constrói a agenda generica do medico
void ConstruirAgenda(int (*)[D], int ,int *, int);   // função que acressenta os horarios indisponiveis na agenda do medico

// Funções para ler arquivos de texto:
void LerDadosMedicos(FILE *, agMedico *, int *, int);
void LerDadosClientes(FILE *, int, cliente *, int *, int);

// Funcoes auxiliares de LerDadosMedicos:
int SomenteInts(int *, char *);   // transfere os numeros de um vetor char para um vetor int e retorna seu tamanho

// Funções que modificam informações de médicos ou clientes:
//void MarcarConsulta(agMedico, cliente); // Função que marca uma consulta entre médico e cliente


int main(int argv, char *argc[])
{
	// Por enquanto somente testes:
	// Alan, nao remova meus comentarios zuados, eles dao vida pro projeto! (e nao eh como se fossem frazes aleatorias jogadas entre parenteses)
	FILE *dm, *lp1, *lp2, *lp3, *lp4;
	int conjunto;	                    // conjunto de exemplos a ser avaliado
	int nMed, nCl1, nCl2, nCl3, nCl4;   // numero total de medicos e clientes
	agMedico medicos[ML];               // vetor de medicos
	cliente clientes1[CL];              // vetor de clientes da semana 1
	cliente clientes2[CL];              // vetor de clientes da semana 2
	cliente clientes3[CL];              // vetor de clientes da semana 3
	cliente clientes4[CL];              // vetor de clientes da semana 4

	printf("Informe o numero do conjunto a ser avaliado (0 - 5): ");
	scanf("%d", &conjunto);

	LerDadosMedicos(dm, medicos, &nMed, conjunto);
	//LerDadosClientes(lp1, 1, clientes1, &nCl1, conjunto);
	LerDadosClientes(lp2, 2, clientes2, &nCl2, conjunto);
	LerDadosClientes(lp3, 3, clientes3, &nCl3, conjunto);
	LerDadosClientes(lp4, 4, clientes4, &nCl4, conjunto);
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

void LerDadosMedicos(FILE *dados, agMedico medicos[], int *nMed, int conjunto)
{
	int  i, j, k;   // variáveis de incrementação
	int nMedc;	// numero total de medicos

	// Variáveis auxiliares para construção dos médicos:
	int dia;		  // armazena o dia(da semana) com horarios indisponiveis, atualizada numa recursao
	char indisponivel[DIM];   // armazena a string dos horarios indisponiveis (relativos ao dia)
	int horario[DIM];	  // armazena os horarios indisponiveis ("filtra o vetor indisponiveis")
	int tam;		  // armazena o tamanho do vetor horario

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

	// Verificando se não há erro:
	if (dados == NULL)
	{
		printf("Incapaz de abrir ou encontrar arquivo");
		exit(1);
	}

	// Extraindo informacoes dos medicos:
	nMedc = 0;   // contador do numero de medicos (sera transferido para nMed)
	do{
		ConstroiAgenda(medicos[nMedc].agenda); // Inicializando a matriz agenda (vazia)

		// Nome, id e especialidade:
		fscanf(dados, "%[^\n]\n%d\n%[^\n]\n", medicos[nMedc].nome, &medicos[nMedc].id, medicos[nMedc].especialidade);

		// Extraindo os horarios indisponiveis:
		// Preparando a recursao
		dia = 0;  // inicializa a variavel dia, so se altera caso a proxima linha escaneada comece com um numero, consegue advinhar qual?(dica: eh nome de uma variavel)
		fscanf(dados, "%d %[^\n]", &dia, indisponivel);   /* extrai os primeiros horarios indisponiveis e seus respectivos dias.
								     caso nao tenha, 'dia' se mantem igual a 0
								  */

		while(dia != 0){
			// Selecionando somente os numeros e transferindo-os para o vetor horario: (cortando espacos e aquele 'a')
			tam = SomenteInts(horario, indisponivel);   // funcao retorna o tamanho do vetor 'horario' (sim, ja sei, uma gambiarra formidavel!)

			// Incluindo os horarios indisponiveis na agenda:
			ConstruirAgenda(medicos[nMedc].agenda, dia, horario, tam);

			// Reinicializando as condicoes da recursao para extrair os proximos horarios:
			dia = 0;
			fscanf(dados, "%d %[^\n]", &dia, indisponivel); // extraindo proximo horario, caso seja a quebra de linha, 'dia' se mantem igual a 0
		}

		nMedc++; // Atualizando o numero de medicos

	}while(!feof(dados));   // a recursao continua até o fim do arquivo, retirando todos os dados de um unico medico a cada repeticao

	*nMed = nMedc;   // eu avisei
	fclose(dados); // fechando o arquivo



	// Impressao para teste (SOMENTE TESTE)
	for(i = 0 ; i < nMedc ; i++)
	{
	printf("%s\n%d\n%s\n", medicos[i].nome, medicos[i].id, medicos[i].especialidade);

	ImprimirAgenda(medicos[i].agenda);
	}

}

void LerDadosClientes(FILE *dados, int semana, cliente clientes[], int *nCl, int conjunto){

	int  i;          // variáveis de incrementação
	int nClien;				// numero total de clientes

	// Variáveis que auxiliaram na construção dos clientes:
	int dia, mes, ano;

	// Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
	switch(conjunto){
		case 0 : switch(semana){
					case 1 : dados = fopen("Conjunto0/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto0/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto0/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto0/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		case 1 : switch(semana){
					case 1 : dados = fopen("Conjunto1/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto1/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto1/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto1/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		case 2 : switch(semana){
					case 1 : dados = fopen("Conjunto2/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto2/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto2/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto2/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		case 3 : switch(semana){
					case 1 : dados = fopen("Conjunto3/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto3/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto3/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto3/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		case 4 : switch(semana){
					case 1 : dados = fopen("Conjunto4/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto4/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto4/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto4/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		case 5 : switch(semana){
					case 1 : dados = fopen("Conjunto5/listaPacientes-Semana1.txt", "r");
							break;
					case 2 : dados = fopen("Conjunto5/listaPacientes-Semana2.txt", "r");
							break;
					case 3 : dados = fopen("Conjunto5/listaPacientes-Semana3.txt", "r");
							break;
					case 4 : dados = fopen("Conjunto5/listaPacientes-Semana4.txt", "r");
							break;
				}
				break;
		default: printf("Conjunto nao existe!                                                                                                           ...idiota\n");
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
	do{
		fscanf(dados, "%[^\n]\n%d\n%lld\n%d %d %d\n%[^\n]\n", clientes[nClien].nome, &clientes[nClien].id, &clientes[nClien].fone, &dia, &mes, &ano, clientes[nClien].medico);

		clientes[nClien].idade = 2017 - ano;

		nClien++; // Atualizando o numero de clientes

	}while(!feof(dados));

	*nCl = nClien;

	fclose(dados); // fechando o arquivo

	// Impressao para teste
	for(i = 0 ; i < nClien ; i++)
		printf("%s\n%d\n%lld\n%d\n%s\n%d\n\n", clientes[i].nome, clientes[i].id, clientes[i].fone, clientes[i].idade, clientes[i].medico, nClien);


}

int SomenteInts(int horario[], char indisponivel[]){

	int i, j, k, tam;

	for(i = 2, j = 0 ; i < strlen(indisponivel) ; i++)
		if(indisponivel[i] == '1' || indisponivel[i] == '2' || indisponivel[i] == '3' || indisponivel[i] == '4' || indisponivel[i] == '5' || indisponivel[i] == '6' || indisponivel[i] == '7' || indisponivel[i] == '8' || indisponivel[i] == '9' || indisponivel[i] == '0')   // identificando se eh numero
		{
			horario[j] = indisponivel[i]-48;   // alocando os numeros como int
			j++;   // age como o tamanha atual do vetor, o real tera a metade (ver abaixo)
		}

	// Acima, os numeros foram separados individualmente ('08' foi alocado como '0' e '8', por exemplo), agora serao reagrupados:
	for(i = 0, tam = 0 ; i < j ; i += 2, tam++){
		k = horario[i]*10 + horario[i+1];
		horario[tam] = k;
	}

	return tam; // o tamanho real do vetor, somente a parte dos numeros reagrupados
}

/*
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
}*/
