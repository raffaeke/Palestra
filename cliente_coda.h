#ifndef CLIENTE_CODA_H
#define CLIENTE_CODA_H
#include "cliente.h"
typedef struct CodaCliente* codaCliente;

codaCliente newCoda(); //crea la coda

int emptyCoda(codaCliente); //Verifica se la coda è vuota

int enqueue(codaCliente,cliente); //Aggiunge un cliente alla coda

cliente dequeue(codaCliente);//Rimuove un cliente dalla coda e restituisce la sua identita

void freeCoda(codaCliente); //Libera la memoria occupata dalla coda
#endif //CLIENTE_CODA_H
