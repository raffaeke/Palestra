#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>

#include "cliente_coda.h"

int main(void) {
    listaCliente l = newLista();
    codaCliente q=newCoda();
    l=LoadInizio(l);
    srand(time(NULL));
    int num_clienti = rand() % 10;
    while(num_clienti>0) {
        cliente temp;
        char cod_fiscale[17];
        printf("\nInserisci identificativo (codice fiscale)\n");
        gets(cod_fiscale);
        temp=trovaCliente(l,cod_fiscale);
        if (!clienteNULL(temp)) {
            printf("\nBenvenuto! sei un nuovo cliente, lascia Cod Fiscale|Nome|Cognome|data di nascita| e quanti mesi di abbonamento vuole fare!");
            temp=NewAbbonamento(l);
        }
        if(enqueue(q,temp)!=1)printf("\nInserimento nella coda non avvenuto");
        num_clienti--;
    }

    return 0;
}
