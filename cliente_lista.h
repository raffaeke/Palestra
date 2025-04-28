#ifndef CLIENTE_LISTA_H
#define CLIENTE_LISTA_H
#include "cliente.h"
typedef struct ListaCliente* listaCliente;

listaCliente newLista(); //Crea una nuova lista
int emptyLista(listaCliente); //verifica se la lista e' vuota
listaCliente consLista(listaCliente,cliente);
listaCliente LoadInizio(listaCliente); //aggiunge i clienti presenti nel file alla lista
cliente trovaCliente(listaCliente,char[]); //trova il cliente tramite cod fiscale
listaCliente rimuoviAbbonamentiScaduti(listaCliente); //rimuove chi ha l abbonamento scaduto
void visualLista(listaCliente);//Visualizza l'intera lista
int sizeLista(listaCliente); //FORSE SI USA PER IL REPORT
void Updatefile(listaCliente); // Scrive su file solo chi ha abb>0
cliente NewAbbonamento(listaCliente);
void RinnovaAbbonamento(listaCliente,cliente,int);
#endif //CLIENTE_LISTA_H
