#ifndef CLIENTE_LISTA_H
#define CLIENTE_LISTA_H
#include "cliente.h"
#define NOMEFILE "abbonati.txt"
typedef struct ListaCliente* listaCliente;

listaCliente newListaC(); //Crea una nuova lista
int emptyListaC(listaCliente); //verifica se la lista e' vuota
listaCliente consListaC(listaCliente,cliente);
listaCliente LoadInizio(listaCliente); //aggiunge i clienti presenti nel file alla lista
cliente trovaCliente(listaCliente,char[]); //trova il cliente tramite cod fiscale
listaCliente rimuoviAbbonamenti(listaCliente); //rimuove chi ha l abbonamento scaduto o annullato, usata per fare un recap ad ogni inizio settimana
void visualListaC(listaCliente);//Visualizza l'intera lista
int sizeListaC(listaCliente); //FORSE SI USA PER IL REPORT
void updateFileAbb(listaCliente); // Scrive su file solo chi ha abb>0
listaCliente updateSettimanale(listaCliente); // ogni settimana passata diminuisce di 1 l abbonamento dei clienti
cliente NewAbbonamento(listaCliente);
int RinnovaAbbonamento(listaCliente,cliente,int);
int annullaAbbonamento(listaCliente,cliente);
#endif //CLIENTE_LISTA_H
