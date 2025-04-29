#ifndef CLIENTE_CODA_H
#define CLIENTE_CODA_H
#include "cliente.h"
typedef struct CodaCliente* codaCliente;

codaCliente newCoda();
int emptyCoda(codaCliente);
int enqueue(codaCliente,cliente);
cliente dequeue(codaCliente);
#endif //CLIENTE_CODA_H
