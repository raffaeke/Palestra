#ifndef LISTA_LEZIONI_H
#define LISTA_LEZIONI_H
#include "lezioni.h"
typedef struct ListaLezioni* listaLezioni;
listaLezioni newListaL();
int emptyListaL(listaLezioni);
void visualListaL(listaLezioni);
listaLezioni consListaL(listaLezioni,lezione);
listaLezioni loadListaL(listaLezioni,char[]);

#endif //LISTA_LEZIONI_H
