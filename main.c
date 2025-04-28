#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>

#include "cliente_coda.h"

int main(void) {
    int settimana=0;
    listaCliente l = newLista();
    int contCliente=0;
    codaCliente q=newCoda();
    l=LoadInizio(l);
    srand(time(NULL));
    int num_clienti =1; //rand() % 10;
    bool risp=0;
    do {
        if (settimana==0) contCliente=sizeLista(l);
        if (settimana==5) {
            //report();
            //settimana=0;
        }
        settimana++;
        while(num_clienti>0) {
            cliente temp;
            char cod_fiscale[17];
            printf("\nInserisci identificativo (codice fiscale)\n");
            gets(cod_fiscale);
            temp=trovaCliente(l,cod_fiscale);
            if (!clienteNULL(temp)) {
                printf("\nBenvenuto! sei un nuovo cliente, lascia Cod Fiscale|Nome|Cognome|data di nascita| e quanti mesi di abbonamento vuole fare!\n");
                temp=NewAbbonamento(l);
            }
            if(enqueue(q,temp)!=1)printf("\nInserimento nella coda non avvenuto");
            num_clienti--;
        }
        int sceltamenu;
        do {
            cliente c;
            printf("\nMENU\n1)Rinnova abbonamento\n2)Annulla abbonamento\n3)Prenota lezione\n");
            scanf("%d",&sceltamenu);
            switch (sceltamenu) {
                    case 1: int rinnova=0;
                            c=dequeue(q);
                            printf("\nCiao %s %s per quanto tempo vuoi prolungare l'abbonamento(numero settimane)?\n",c.nome,c.cogn);
                            scanf("%d",&rinnova);
                            RinnovaAbbonamento(l,c,rinnova); break;
                   /*case 2: break;
                    case 3: break;*/
                    default: printf("\nScelta non valida");
            }
        }while (sceltamenu<=0||sceltamenu>3);
        printf("\nVuoi avanzare di una settimana? (1=si/0=no)\n");
        scanf("%b",&risp);
    }while (risp==1);
    return 0;
}
