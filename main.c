#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>

int main(void) {
    listaCliente l = newLista();
    l=LoadInizio(l);
    int scelta =0;
    do {
        system("CLS");
        printf("\nGESTIONE PALESTRA\n1)ISCRIZIONE NUOVO CLIENTE\n2)EFFETTUA PRENOTAZIONE\n3)DISPONIBILITA DI UNA LEZIONE\n0)USCITA DAL PROGRAMMA\n");
        scanf("%d",&scelta);
        switch (scelta) {
            case 0:printf("Uscita in corso...");
            case 1: NewAbbonamento(l); break;
            case 2:/*TODO*/break;
            case 3:/*TODO*/break;
            default:printf("Scelta invalida\n");
        }
    }while (scelta<3);
    return 0;
}