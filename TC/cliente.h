#ifndef CLIENTE_H

#define CLIENTE_H

#define DIM 30

// Definição das características relevantes de um cliente:
typedef struct cliente
{
    char nome[DIM];     // o nome do cliente
    int id;             // o número de identificação do cliente
    long long int fone; // o número de telefone do cliente
    int idade;          // a idade do cliente
    char medico[DIM];   // o médico pelo qual o cliente deseja ser atendido
} cliente;

cliente ConstruirCliente(char *, int, int, long int, int, char *, int); // Função que inicializa um cliente

#endif