#ifndef LISTA_LEZIONI_H
#define LISTA_LEZIONI_H
#include "lezioni.h"

typedef struct ListaLezioni* listaLezioni;

listaLezioni newListaL(); //Crea la lista

int emptyListaL(listaLezioni);//Verifica se la lista è vuota

void visualListaL(listaLezioni);//Visualizza l intera lista

listaLezioni consListaL(listaLezioni,lezione);//Aggiunge in testa la lezione passata come parametro

listaLezioni loadListaL(listaLezioni,char[]); //Legge il file e carica il contenuto nella lista

int prenotaLezione(listaLezioni); //prenotazione

void mostraLezioniDisponibili(listaLezioni); //mostra le lezioni disponibili

#endif //LISTA_LEZIONI_H
