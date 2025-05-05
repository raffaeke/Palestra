#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>

#include "cliente_coda.h"
#include "lista_lezioni.h"

int main(void) {
    int settimana=0;
    listaCliente lc = newListaC();
    int contCliente=0;
    codaCliente q=newCoda();
    lc=LoadInizio(lc);
    srand(time(NULL));
    int num_clienti =1; //rand() % 10;
    bool risp=0;
    do {
        lc=rimuoviAbbonamenti(lc);
       // lc=updateSettimanale(lc);  FUNZIONA MA SE RIMANE ATTIVO OGNI TEST SCALA GLI ABBONAMENTI
        if (settimana==0) contCliente=sizeListaC(lc); //CONTA I CLIENTI A INIZIO MESE
        if (settimana==5) {
            //report();
            //settimana=0;
        }
        settimana++;
        while(num_clienti>0) {
            char cod_fiscale[17];
            printf("\nInserisci identificativo (codice fiscale)\n");
            gets(cod_fiscale);
            cliente temp = trovaCliente(lc, cod_fiscale);
            if (!clienteNULL(temp)) {
                printf("\nBenvenuto! sei un nuovo cliente, lascia Cod Fiscale|Nome|Cognome|data di nascita| e quanti mesi di abbonamento vuole fare!\n");
                temp=NewAbbonamento(lc);
            }
            if(enqueue(q,temp)!=1)printf("\nInserimento nella coda non avvenuto");
            num_clienti--;
        }
        int sceltamenu;
        do {
            cliente c;
            printf("\nMENU\n1)Rinnova abbonamento\n2)Annulla abbonamento\n3)Prenota lezione\n0)Per uscire\n");
            scanf("%d",&sceltamenu);
            switch (sceltamenu) {
                case 0: break;
                case 1: int rinnova=0;
                    c=dequeue(q);
                    printf("\nCiao %s %s per quanto tempo vuoi prolungare l'abbonamento(numero settimane)?\n",c.nome,c.cogn);
                    scanf("%d",&rinnova);
                    if (RinnovaAbbonamento(lc,c,rinnova)==1)printf("\nAbbonamento rinnovato con successo\n");
                    else printf("\nAbbonamento non rinnovato\n");break;
                case 2: c=dequeue(q);
                    printf("\nCiao %s %s,ci dispiace per la vostra scelta di lasciarci\n",c.nome,c.cogn);
                    if (annullaAbbonamento(lc,c)==1)printf("\nAbbonamento annullato con successo\n");
                    else printf("\nAbbonamento non annullato\n");break;
                case 3: c=dequeue(q);
                    int sceltagiorno;
                    do {
                        printf("\nCiao %s %s, che giorno vuoi prenotare la lezione?\n1)LUNEDI\n2)MARTEDI\n3)MERCOLEDI\n4)GIOVEDI\n5)VENERDI\n6)SABATO\n",c.nome,c.cogn);
                        scanf("%d",&sceltagiorno);
                        switch (sceltagiorno) {
                            case 1: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,lunedi);
                                /*Funzione per prenotare uan lezione va bene anche negli altri 6 case*/
                                break;
                            }
                            case 2: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,martedi);

                                break;
                            }
                            case 3: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,mercoledi);

                                break;
                            }
                            case 4: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,giovedi);

                                break;
                            }
                            case 5: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,venerdi);

                                break;
                            }
                            case 6: {
                                listaLezioni ll = newListaL();
                                ll = loadListaL(ll,sabato);

                                break;
                            }
                            default: printf("\nGiorno non valido");break;
                        }
                        printf("\nVuoi prenotare un'altra lezione? (1=si/0=no)\n");
                        scanf("%d",&risp);
                    }while (risp==1);
            }
        }while (sceltamenu<0||sceltamenu>3);
        updateFileAbb(lc);
        printf("\nVuoi avanzare di una settimana? (1=si/0=no)\n");
        scanf("%d",&risp);
    }while (risp==1);
    return 0;
}
