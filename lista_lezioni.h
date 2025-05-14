#ifndef LISTA_LEZIONI_H
#define LISTA_LEZIONI_H
#include "lezioni.h"

typedef struct ListaLezioni* listaLezioni;

listaLezioni newListaL(); //Crea la lista

int emptyListaL(listaLezioni);//Verifica se la lista è vuota

void visualListaL(listaLezioni);//Visualizza l intera lista

listaLezioni consListaL(listaLezioni,lezione);//Aggiunge in testa la lezione passata come parametro

listaLezioni loadListaL(listaLezioni,char[]); //Legge il file e carica il contenuto nella lista

int prenotaLezione(listaLezioni,char[]); //prenotazione

void mostraLezioniDisponibili(listaLezioni); //mostra le lezioni disponibili

int disponibilitaLezione(lezione); //controlla se la lezione è disponibile

void salvaListaLezioni(listaLezioni,char[]); //salva la lista in un file

void resetFile(); //resetta il file delle lezioni

void freeListaL(listaLezioni); //libera la memoria occupata dalla lista
#endif //LISTA_LEZIONI_H
