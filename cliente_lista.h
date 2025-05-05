#ifndef CLIENTE_LISTA_H
#define CLIENTE_LISTA_H
#include "cliente.h"
#define NOMEFILE "abbonati.txt"
typedef struct ListaCliente* listaCliente;

listaCliente newListaC(); //Crea una nuova lista

int emptyListaC(listaCliente); //verifica se la lista e' vuota

listaCliente consListaC(listaCliente,cliente); //Aggiunge il cliente passato nei parametri in testa alla lista

listaCliente LoadInizio(listaCliente); //aggiunge i clienti presenti nel file alla lista

cliente trovaCliente(listaCliente,char[]); //trova il cliente tramite cod fiscale

listaCliente rimuoviAbbonamenti(listaCliente); //rimuove chi ha l abbonamento scaduto o annullato,
//usata per fare un recap ad ogni inizio settimana

void visualListaC(listaCliente);//Visualizza l'intera lista

int sizeListaC(listaCliente); //FORSE SI USA PER IL REPORT

void updateFileAbb(listaCliente); // Scrive su file solo chi ha abb>0

listaCliente updateSettimanale(listaCliente); // ogni settimana passata diminuisce di 1 l abbonamento dei clienti

cliente NewAbbonamento(listaCliente); //Richiede i dati personali all utente per creare un abbonamento a suo nome

int RinnovaAbbonamento(listaCliente,cliente, int); //Aggiunge alla durata abbonamento del cliente passato
//come parametro un INT sempre passato come parametro. Restitusce 1 se è andata a buon fine, 0 altrimenti

int annullaAbbonamento(listaCliente,cliente); //Va a impostare la durata abbonamento del cliente passato a 0
//restitusce 1 se è andata a buon fine, 0 altrimenti
#endif //CLIENTE_LISTA_H
