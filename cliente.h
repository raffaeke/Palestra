#ifndef CLIENTE_H
#define CLIENTE_H
#define MAX_L 30
#include <stdbool.h>
typedef struct{
    char cod_fis[17];
    char nome[MAX_L];
    char cogn[MAX_L];
    char data[11];// 00/00/0000
    int abb;
}cliente;
extern const cliente NULL_CLIENTE;

//Set
void setCodFis(cliente*, const char*);
void setNome(cliente*, const char*);
void setCognome(cliente*, const char*);
void setData(cliente*, const char*);
void setAbbonamento(cliente*, int);
void setCliente(cliente*, const cliente*);
//Get
const char* getCodFis(const cliente*);
const char* getNome(const cliente*);
const char* getCognome(const cliente*);
const char* getData(const cliente*);
int getAbbonamento(const cliente*);

void output_cliente(cliente);//Stampa il contenuto della struct

bool clienteNULL(cliente);//Controlla se il cliente passato è uguale alla sua versione NULL dichiarata,
//restituisce 0 se falso, 1 altrimenti

#endif // CLIENTE_H
