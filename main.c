#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>
#include "cliente_coda.h"
#include "lista_lezioni.h"
void init(int * cont_cliente, int * cont_new_abbonamento, int * cont_rinnova_abbonamento, int * cont_annulla_abbonamento, int * cont_prenota_lezione);

int main(void) {
    int contNewAbbonamento=0,contRinnovaAbbonamento=0,contAnnullaAbbonamento=0,contPrenotaLezione=0;
    int settimana=0;
    listaCliente lc = newListaC();
    int contCliente=0;
    codaCliente q=newCoda();
    lc=LoadInizio(lc);
    srand(time(NULL));
    bool risp=0;
    do {
        int num_clienti =3; //rand() % 10;
        lc=rimuoviAbbonamenti(lc);
        lc=updateSettimanale(lc);  // MA SE RIMANE ATTIVO OGNI TEST SCALA GLI ABBONAMENTI
        if (settimana==0) {
            contCliente=sizeListaC(lc); //CONTA I CLIENTI A INIZIO MESE
            init(&contCliente,&contNewAbbonamento,&contRinnovaAbbonamento,&contAnnullaAbbonamento,&contPrenotaLezione);
        }
        if (settimana==5) {
            printf("\nReport mensile:\nAbbonamenti totali prima e dopo: %d->%d\n",contCliente,sizeListaC(lc));
            printf("\nNuovi abbonamenti: %d\n",contNewAbbonamento);
            printf("\nAbbonamenti rinnovati: %d\n",contRinnovaAbbonamento);
            printf("\nAbbonamenti annullati: %d\n",contAnnullaAbbonamento);
            printf("\nPrenotazioni totali: %d\n",contPrenotaLezione);
            system("pause");
            settimana=0;
        }
        settimana++;
        while(num_clienti>0) {
            char cod_fiscale[17];
            printf("\nInserisci identificativo (codice fiscale)\n");
            fflush(stdin);
            gets(cod_fiscale);
            cliente temp = trovaCliente(lc, cod_fiscale);
            if (clienteNULL(temp)) {
                temp=NewAbbonamento(lc);
                contNewAbbonamento++;
            }
            if(enqueue(q,temp)!=1)printf("\nInserimento nella coda non avvenuto");
            num_clienti--;
        }

        int sceltamenu;
        cliente c;
        do {
            c=dequeue(q);
            if (clienteNULL(c))break;
            printf("\nMENU\n1)Rinnova abbonamento\n2)Annulla abbonamento\n3)Prenota lezione\n4)Ho cambiato idea, non devo fare nulla\n");
            scanf("%d",&sceltamenu);
            switch (sceltamenu) {
                case 0: break;
                case 4: printf("\nIl cliente %s %s ha lasciato la coda, Avanti il prossimo\n",c.nome,c.cogn);break;
                case 1: int rinnova=0;
                        printf("\nCiao %s %s per quanto tempo vuoi prolungare l'abbonamento(numero settimane)?\n",c.nome,c.cogn);
                        scanf("%d",&rinnova);
                        if (RinnovaAbbonamento(lc,c,rinnova)==1) {
                            printf("\nAbbonamento rinnovato con successo\n");
                            contRinnovaAbbonamento++;
                        }
                        else printf("\nAbbonamento non rinnovato\n");
                    break;
                case 2:
                        printf("\nCiao %s %s,ci dispiace per la vostra scelta di lasciarci\n",c.nome,c.cogn);
                        if (annullaAbbonamento(lc,c)==1) {
                            printf("\nAbbonamento annullato con successo\n");
                            contAnnullaAbbonamento++;
                        }
                        else printf("\nAbbonamento non annullato\n");
                    break;
                case 3:
                       int sceltagiorno;
                        do {
                            printf("\nCiao %s %s, che giorno vuoi prenotare la lezione?\n1)LUNEDI\n2)MARTEDI\n3)MERCOLEDI\n4)GIOVEDI\n5)VENERDI\n6)SABATO\n",c.nome,c.cogn);
                            scanf("%d",&sceltagiorno);
                            switch (sceltagiorno) {
                                case 1: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,lunedi);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    break;
                                }
                                case 2: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,martedi);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");

                                    break;
                                }
                                case 3: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,mercoledi);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    break;
                                }
                                case 4: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,giovedi);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    break;
                                }
                                case 5: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,venerdi);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    break;
                                }
                                case 6: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,sabato);
                                    int controllo = prenotaLezione(ll);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    break;
                                }
                                default: printf("\nGiorno non valido");break;
                            }
                            printf("\nVuoi prenotare un'altra lezione? (1=si/0=no)\n");
                            scanf("%d",&risp);
                        }while (risp==1);
                    break;
                    default: printf("\nScelta non valida, ripeti");break;
            }
        }while (sceltamenu!=0);
        updateFileAbb(lc);
        printf("\nVuoi avanzare di una settimana? (1=si/0=no)\n");
        scanf("%d",&risp);
    }while (risp==1);

    return 0;
}
