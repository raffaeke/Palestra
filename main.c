#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "cliente_coda.h"
#include "lista_lezioni.h"
void init(int * cont_cliente, int * cont_new_abbonamento, int * cont_rinnova_abbonamento, int * cont_annulla_abbonamento, int * cont_prenota_lezione,int contLezioni[]);
int maxLezioni(int contLezioni[]);
#ifdef _WIN32
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

int controlla_sistema_operativo() {
    if (OS_WINDOWS) {
        return 1; // Windows
    } else {
        return 0; // Linux o altro
    }
}
int main(void) {
    int contNewAbbonamento=0,contRinnovaAbbonamento=0,contAnnullaAbbonamento=0,contPrenotaLezione=0;
    int settimana=0;
    listaCliente lc = newListaC();
    int contCliente=0;
    int contLezioni[7]={0,0,0,0,0,0,0};
    codaCliente q=newCoda();
    lc=LoadInizio(lc);
    srand(time(NULL));
    int risp=0;
    do {
        resetFile();
        if (controlla_sistema_operativo()==1) {
        system("cls");
        }else system("clear");
        int num_clienti =rand() % 10;
        lc=rimuoviAbbonamenti(lc);
        lc=updateSettimanale(lc);  // MA SE RIMANE ATTIVO OGNI TEST SCALA GLI ABBONAMENTI
        if (settimana==0) {
            contCliente=sizeListaC(lc); //CONTA I CLIENTI A INIZIO MESE
            init(&contCliente,&contNewAbbonamento,&contRinnovaAbbonamento,&contAnnullaAbbonamento,&contPrenotaLezione,contLezioni);
        }
        if (settimana==5) {
            const char* lezioniDisponibili[] = {
                "Attrezzi", "Yoga", "Karate", "Pilates", "Funzionale", "Fitness", "Zumba"
            };
            printf("\nReport mensile:\nAbbonamenti totali prima e dopo: %d->%d\n",contCliente,sizeListaC(lc));
            printf("\nNuovi abbonamenti: %d\n",contNewAbbonamento);
            printf("\nAbbonamenti rinnovati: %d\n",contRinnovaAbbonamento);
            printf("\nAbbonamenti annullati: %d\n",contAnnullaAbbonamento);
            printf("\nPrenotazioni totali: %d\n",contPrenotaLezione);
            printf("\nLa lezione che ha ricevuto più prenotazioni è la %s",lezioniDisponibili[maxLezioni(contLezioni)]);
            printf("Premere un tasto per continuare . . .");
            getchar();
            settimana=0;
        }
        settimana++;
        printf("\nOggi ci sono %d clienti\n",num_clienti);
        while(num_clienti>0) {
            char cod_fiscale[17];
            printf("\nInserisci identificativo (codice fiscale)\n");
            fflush(stdin);
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
                case 4: printf("\nIl cliente %s %s ha lasciato la coda, Avanti il prossimo\n",getNome(&c),getCognome(&c));break;
                case 1: int rinnova=0;
                        printf("\nCiao %s %s per quanto tempo vuoi prolungare l'abbonamento(numero settimane)?\n",getNome(&c),getCognome(&c));
                        scanf("%d",&rinnova);
                        if (RinnovaAbbonamento(lc,c,rinnova)==1) {
                            printf("\nAbbonamento rinnovato con successo\n");
                            contRinnovaAbbonamento++;
                        }
                        else printf("\nAbbonamento non rinnovato\n");
                    break;
                case 2:
                        printf("\nCiao %s %s,ci dispiace per la vostra scelta di lasciarci\n",getNome(&c),getCognome(&c));
                        if (annullaAbbonamento(lc,c)==1) {
                            printf("\nAbbonamento annullato con successo\n");
                            contAnnullaAbbonamento++;
                        }
                        else printf("\nAbbonamento non annullato\n");
                    break;
                case 3:
                       int sceltagiorno;
                        do {
                            printf("\nCiao %s %s, che giorno vuoi prenotare la lezione?\n1)LUNEDI\n2)MARTEDI\n3)MERCOLEDI\n4)GIOVEDI\n5)VENERDI\n6)SABATO\n",getNome(&c),getCognome(&c));
                            scanf("%d",&sceltagiorno);
                            switch (sceltagiorno) {
                                case 1: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,lunedi);
                                    int controllo = prenotaLezione(ll,lunedi,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
                                    break;
                                }
                                case 2: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,martedi);
                                    int controllo = prenotaLezione(ll,martedi,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
                                    break;
                                }
                                case 3: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,mercoledi);
                                    int controllo = prenotaLezione(ll,mercoledi,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
                                    break;
                                }
                                case 4: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,giovedi);
                                    int controllo = prenotaLezione(ll,giovedi,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
                                    break;
                                }
                                case 5: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,venerdi);
                                    int controllo = prenotaLezione(ll,venerdi,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
                                    break;
                                }
                                case 6: {
                                    listaLezioni ll = newListaL();
                                    ll = loadListaL(ll,sabato);
                                    int controllo = prenotaLezione(ll,sabato,contLezioni);
                                    if (controllo==1) {
                                        printf("\nLezione prenotata con successo\n");
                                        contPrenotaLezione++;
                                    }
                                    else printf("\nLezione non prenotata\n");
                                    freeListaL(ll);
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
    freeListaC(lc);
    freeCoda(q);
    return 0;
}
