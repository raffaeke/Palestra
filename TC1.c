#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>
#include "cliente_coda.h"
#include "lista_lezioni.h"

/*Verifica della corretta registrazione delle prenotazioni e dell'aggiornamento
delle disponibilità. */
int main(void) {
    int contLezioni[7]={0};
    lc=LoadInizio(lc);
    listaLezioni ll=newListaL();
    ll=loadListaL(ll,martedi);
    mostraLezioniDisponibili(ll);
    int controllo=prenotaLezione(ll,martedi,contLezioni);
    if (controllo==1) {
printf("\nLezione prenotata con successo\n");
}
    mostraLezioniDisponibili(ll);
}