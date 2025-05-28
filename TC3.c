#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>
#include "cliente_coda.h"
#include "lista_lezioni.h"
/*Verifica che il report generato contenga informazioni corrette e complete sulle prenotazioni*/
int maxLezioni(int contLezioni[]);

int main(void) {
    listaCliente lc = newListaC();
    lc=LoadInizio(lc);
    int contCliente=sizeListaC(lc);
    int contLezioni[7]={0,0,0,0,0,0,0};
    const char* lezioniDisponibili[] = {
        "Attrezzi", "Yoga", "Karate", "Pilates", "Funzionale", "Fitness", "Zumba"
    };
    cliente c={"ABCDEFGHI","NOME","COGNOME","00/00/0000", 0};
    lc=consListaC(lc,c);
    listaLezioni ll=newListaL();
    ll=loadListaL(ll,martedi);
    for (int i=0;i<4;i++) {

        int controllo=prenotaLezione(ll,martedi,contLezioni);
        if (controllo==1) {
            printf("\nLezione prenotata con successo\n");
        }
}
    printf("\nReport mensile:\nAbbonamenti totali prima e dopo: %d->%d\n",contCliente,sizeListaC(lc));
    printf("\nLa lezione che ha ricevuto più prenotazioni è la %s",lezioniDisponibili[maxLezioni(contLezioni)]);
}