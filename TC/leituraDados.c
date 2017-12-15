#include "leituraDados.h"
#include "data.h"
#include <stdlib.h>
#include <string.h>

int SomenteInts(int horario[], char indisponivel[])
{

    int i, j, k, tam;

    for (i = 0, j = 0; i < strlen(indisponivel); i++)
        if (indisponivel[i] >= '0' && indisponivel[i] <= '9') // identificando se é dígito
        {
            horario[j] = indisponivel[i] - 48; // alocando os numeros como int
            j++;                               // age como o tamanha atual do vetor, o real tera a metade (ver abaixo)
        }

    // Acima, os numeros foram separados individualmente ('08' foi alocado como '0' e '8', por exemplo), agora serao reagrupados:
    for (i = 0, tam = 0; i < j; i += 2, tam++)
    {
        k = horario[i] * 10 + horario[i + 1];
        horario[tam] = k;
    }

    return tam; // o tamanho real do vetor, somente a parte dos numeros reagrupados
}

void Remove(char d[], int n)
{

	int i;

	for(i = n ; i < strlen(d) ; i++)
		d[i] = d[i+1];
}

void LerDadosMedicos(FILE *dados, agMedico medicos[], int *nMed, int conjunto)
{
    int i, j, k; // variáveis de incrementação
    int nMedc;   // numero total de medicos

    // Variáveis auxiliares para construção dos médicos:
    int dia;                // armazena o dia(da semana) com horarios indisponiveis, atualizada num loop
    char indisponivel[DIM]; // armazena a string dos horarios indisponiveis (relativos ao dia)
    int horario[DIM];       // armazena os horarios indisponiveis ("filtra o vetor indisponiveis")
    int tam;                // armazena o tamanho do vetor horario
	char aux[DIM];

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
            printf("Conjunto nao existe!\n");
            exit(0);
    }

    // Verificando se não há erro:
    if (dados == NULL)
    {
        printf("Incapaz de abrir ou encontrar arquivo");
        exit(1);
    }

    // Extraindo informações dos médicos:
    nMedc = 0; // contador do numero de medicos (sera transferido para nMed)
    do
    {
        ConstroiAgenda(medicos[nMedc].agenda); // Inicializando a matriz agenda (vazia)

        // Nome, id e especialidade:
		fgets(medicos[nMedc].nome, DIM, dados);
		medicos[nMedc].nome[strlen(medicos[nMedc].nome)-1] = '\0';

		fgets(aux, DIM, dados);
		aux[strlen(aux)-1] = '\0';
		medicos[nMedc].id = atoi(aux);

		fgets(medicos[nMedc].especialidade, DIM, dados);
		medicos[nMedc].especialidade[strlen(medicos[nMedc].especialidade)-1] = '\0';

        // Extraindo os horarios indisponiveis:
        // Preparando o loop
        dia = 0;                                        // inicializa a variavel dia, so se altera caso a proxima linha escaneada comece com um numero, consegue advinhar qual?(dica: eh nome de uma variavel)
        fscanf(dados, "%d %[^\n]", &dia, indisponivel); // extrai os primeiros horarios indisponíveis e seus respectivos dias. Caso nao tenha, 'dia' se mantém igual a 0.

        while (dia != 0)
        {
            // Selecionando somente os numeros e transferindo-os para o vetor horario: (cortando espacos e aquele 'a')
            tam = SomenteInts(horario, indisponivel); // funcao retorna o tamanho do vetor 'horario' (sim, ja sei, uma gambiarra formidavel!)

            // Incluindo os horarios indisponiveis na agenda:
            ConstruirAgenda(medicos[nMedc].agenda, dia, horario, tam);

            // Reinicializando as condições do loop para extrair os proximos horarios:
            dia = 0;
            fscanf(dados, "%d %[^\n]", &dia, indisponivel); // extraindo proximo horario, caso seja a quebra de linha, 'dia' se mantem igual a 0
        }

        nMedc++; // Atualizando o numero de medicos

    } while (!feof(dados)); // o loop continua até o fim do arquivo, retirando todos os dados de um unico medico a cada repeticao

    *nMed = nMedc; // eu avisei
    fclose(dados); // fechando o arquivo
}

void LerDadosClientes(FILE *dados, cliente clientes1[], cliente clientes2[], cliente clientes3[], cliente clientes4[], int *nCl1, int *nCl2, int *nCl3, int *nCl4, int conjunto)
{

    // Inicializando o ponteiro do arquivo desejado, fazendo que esse seja somente lido:
    switch (conjunto)
    {
        case 0:
            dados = fopen("Conjunto0/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto0/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto0/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto0/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        case 1:
            dados = fopen("Conjunto1/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto1/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto1/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto1/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        case 2:
            dados = fopen("Conjunto2/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto2/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto2/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto2/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        case 3:
            dados = fopen("Conjunto3/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto3/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto3/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto3/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        case 4:
            dados = fopen("Conjunto4/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto4/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto4/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto4/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        case 5:
            dados = fopen("Conjunto5/listaPacientes-Semana1.txt", "r");
            LerClientes(dados, clientes1, nCl1);
            dados = fopen("Conjunto5/listaPacientes-Semana2.txt", "r");
            LerClientes(dados, clientes2, nCl2);
            dados = fopen("Conjunto5/listaPacientes-Semana3.txt", "r");
            LerClientes(dados, clientes3, nCl3);
            dados = fopen("Conjunto5/listaPacientes-Semana4.txt", "r");
            LerClientes(dados, clientes4, nCl4);
            break;
        default:
            printf("Conjunto nao existe!\n");
            exit(0);
    }
}

void LerClientes(FILE *dados, cliente clientes[], int *nCl)
{

    int i;      // variáveis de incrementação
    int nClien; // numero total de clientes

    // Variáveis que auxiliaram na construção dos clientes:
    int dia, mes, ano, tam;
    int dataI[DIM];
    char dataC[DIM], aux[DIM];

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
		fgets(clientes[nClien].nome, DIM, dados);
		clientes[nClien].nome[strlen(clientes[nClien].nome)-1] = '\0';

		fgets(aux, DIM, dados);
		aux[strlen(aux)-1] = '\0';
		clientes[nClien].id = atoi(aux);

		fgets(aux, DIM, dados);
		aux[strlen(aux)-1] = '\0';
		clientes[nClien].fone = atoll(aux);

		fgets(dataC, DIM, dados);

		fgets(clientes[nClien].medico, DIM, dados);
		clientes[nClien].medico[strlen(clientes[nClien].medico)-1] = '\0';

		fscanf(dados, "\n");

        SomenteInts(dataI, dataC);

        dataI[2] = dataI[2] * 100 + dataI[3];

        clientes[nClien].idade = CalculoIdade(dataI);

        nClien++; // Atualizando o numero de clientes

    } while (!feof(dados));

    *nCl = nClien;

    fclose(dados); // fechando o arquivo
}
