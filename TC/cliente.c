#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

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