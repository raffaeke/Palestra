    #include "cliente.h"
#include "lista_lezioni.h"
#include "cliente_lista.h"
#include "cliente_coda.h"
#include "lezioni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
const cliente NULL_CLIENTE = {"","","","", 0};
struct node_c {
    cliente val;
    struct node_c *next;
};
struct ListaCliente {
    struct node_c *testa;
};
struct CodaCliente {
    struct node_c *testa,*coda;
    int num_clienti;
};
struct node_l {
    lezione val;
    struct node_l *next;
};
struct ListaLezioni {
    struct node_l *testa;
};
void init(int *c1,int *c2,int *c3,int *c4,int c5[]) {
    *c1=0;
     *c2=0;
     *c3=0;
     *c4=0;
    for (int i=0;i<5;i++) {
        c5[i]=0;
    }
}
int maxLezioni(int cont[]) {
    int max=0;
    int contMax=0;
    for (int i=0;i<5;i++) {
        if (cont[i]>max) {
            max=cont[i];
            contMax=i;
        }
    }
    return contMax;
}
//-----------------FUNZIONI LISTA_CLIENTE------------------------------------------
listaCliente newListaC() {
    listaCliente l=malloc(sizeof(struct ListaCliente)); //Alloca dinamicamente uno spazio per creare la lista
    if(l!=NULL) l->testa=NULL; //se la malloc va a buon fine settiamo la testa a NULL
    return l;
}

int emptyListaC(listaCliente l) {
    return l->testa==NULL; //Se la testa è uguale a NULL restituisce 1, 0 altrimenti
}

listaCliente consListaC(listaCliente l, const cliente c) {
    struct node_c *nuovo = malloc(sizeof(struct node_c)); //Allochiamo lo spazio per un nuovo nodo
    if (nuovo!=NULL) { //controllo se la malloc va a buon fine
        nuovo->val=c; //Assegnazione del valore
        nuovo->next=l->testa; //Collego il nuovo nodo alla testa della lista
        l->testa=nuovo; //La testa della lista diventa il nuovo nodo
    }
    return l;
}

/*    loadInizio: carica i dati degli abbonati dal file.
 *    Precondizione: la lista deve essere possibilmente vuota,
      inoltre deve esistere un file definito come "NOMEFILE".

     Postcondizione: restituisce una lista contenente tutti gli
     abbonati con abbonamento maggiore di 0 letti dal file.

     Funzionamento: Apriamo il file degli abbonati in modalità lettura,
     leggiamo riga per riga ed estraggo i dati. Controllo la durata degli
     abbonamenti per vedere se tutti hanno ancora accesso alla lista
     abbonati e se viene trovato qualcuno con l abbonamento scaduto andiamo
     a chiamare una funzione che aggiorna anche il file. Chiudiamo il file
     e restituiamo la lista caricata.*/
listaCliente LoadInizio(listaCliente l) {
    cliente temp;
    bool flag=false; //Variabile utilizzata per controllare un eventuale uso di updateFileAbb()
    FILE *f = fopen(NOMEFILE, "r"); //Apertura file abbonati in lettura
    if (f==NULL) { //controllo sull'apertura
        perror("File non aperto");
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {//finché nel file sono presenti abbonati
        sscanf(buffer, "%s %s %s %s %d", temp.cod_fis, temp.nome, temp.cogn, temp.data, &temp.abb); //prelevo i dati
        if (temp.abb>0)l = consListaC(l, temp); //se l abbonamento è valido li aggiungo alla lista
        else {
            flag=true; //se ci sono abbonamenti scaduti la flag diventa true
        }
    }
    fclose(f); //chiusura file
    if (flag) { //se la flag è true chiama la funzione
        updateFileAbb(l);
    }
    return l;
}

/*  rimuoviAbbonamenti: rimuove chi ha l abbonamento scaduto o annullato.
 *
 *  Precondizione: la lista deve contenere dei clienti,
 *  o eventualmente essere vuota.
 *
 *  Postcondizione: restituisce una lista contenente tutti gli
 *  abbonati con abbonamento maggiore di 0 letti dal file.
 *
 *  Funzionamento: Usiamo due puntatori, corrente per scorrere la lista,
 *  precedente invece punta all'elemento prima per collegare la lista
 *  nel caso in cui ci sia una rimozione nel mezzo.
 *  Restituiamo la lista aggiornata.
 */
listaCliente rimuoviAbbonamenti(listaCliente l) {
    struct node_c *corr=l->testa; //nodo corrente
    struct node_c *prec=NULL; //puntatore al nodo precedente
    printf("Lista di clienti cancellati per ABBONAMENTO SCADUTO o ABBONAMENTO ANNULLATO\n");
    while (corr!=NULL) { //finché il puntatore non arriva alla fine della lista
        if (corr->val.abb<=0) { //se l abbonamento è minore o uguale a 0
            output_cliente(corr->val); //stampo i dati del cliente
            if (prec==NULL) {
                l->testa=corr->next; //Il nodo da eliminare è in testa
                free(corr);
                corr=l->testa;
            } else {
                prec->next=corr->next; //Salta il nodo da eliminare collegando il precedente al successivo
                free(corr); //Libera lo spazio del nodo corrente
                corr=prec->next;
            }
        }
        else {
            prec=corr; //Il precedente prende il valore del nodo corrente
            corr=corr->next; //il nodo corrente avanza
        }
    }
    return l;
}

/*  RinnovaAbbonamento: rinnova l abbonamento di un cliente.
*  Precondizione:la lista deve essere caricata,
*  cliente c non deve essere NULL,
*  r deve essere maggiore di 0
*
    Postcondizione: Incrementa le settimane di abbonamento
    del cliente passato di r settimane

    Funzionamento: Usiamo un puntatore per scorrere la lista,
    cerchiamo il cliente nella lista, se lo troviamo sommiamo
    r alle sue settimane di abbonamento e ritorniamo 1 perche
    è andata a buon fine l'operazione. Se non trova il cliente
    o altro ritorna 0.
 */
int RinnovaAbbonamento(listaCliente l, const cliente c, const int r) {
    struct node_c *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            if (strcmp(p->val.cod_fis,c.cod_fis)==0) { //Se trova il codice fiscale
                p->val.abb+=r; //aggiunge le settimane richieste all'abbonamento
                updateFileAbb(l); //aggiorna il file con l abbonamento rinnovato
               return 1; //va a buon fine
            }
            p=p->next; //avanza di nodo
        }}
    return 0; //non va a buon fine
}
/*    updateFileAbb: Scrive su file solo chi ha abb>0.
*    Precondizione: la lista deve contenere tutti gli abbonati
*    validi, deve essere definita una macro "NOMEFILE".

     Postcondizione:Il file passato verrà riempito da capo con
     gli elementi della lista.

    Funzionamento: Apriamo il file in scrittura, scorriamo la lista
    tramite un puntatore e ogni nodo viene scritto sul file.
*/
void updateFileAbb(listaCliente l) {
    FILE *f = fopen(NOMEFILE, "w"); //apertura file in scrittura
    struct node_c *p=l->testa; //puntatore alla testa della lista
    if (f==NULL) {perror("File non aperto");} //controllo sull'apertura
    if (!emptyListaC(l)) {
        while (p!=NULL) {
        fprintf(f,"%s %s %s %s %d\n",p->val.cod_fis,p->val.nome,p->val.cogn,p->val.data,p->val.abb);
            //scrivo i dati del cliente sul file
        p=p->next;//avanza di nodo
        }
    }
    fclose(f); //chiusura file
}

int sizeListaC(listaCliente l) {
    struct node_c *p=l->testa; //puntatore alla testa della lista
    int cont=0;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            cont++; //conta i clienti nella lista
            p=p->next; //avanza di nodo
        }
    }
    return cont;
}

/*      trovaCliente: trova un cliente nella lista.
 *       Precondizione: la lista deve contenere dei clienti,
        o eventualmente essere vuota. Cod è una stringa che
        contiene il codice fiscale da ricercare.

         Postcondizione: se esiste un cliente nella lista con
         quel codice fiscale lo restituisce. Se invece non viene
         trovato, restituiamo NULLCLIENTE.

        Funzionamento: Controlliamo se la lista è vuota, poi viene
        creato un puntatore alla testa della lista in modo da visitare
        l'intera lista, se trova il cliente con il codice fiscale
        passato lo restituisce altrimenti passa la versione NULL di cliente.*/
cliente trovaCliente(listaCliente l,char cod[]) {
    struct node_c *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            cliente temp=p->val; //copia i dati del nodo corrente nella variabile temp
            if (strcmp(temp.cod_fis,cod)==0) { //se equivalgono ritorno al main il cliente
                return temp;
            }
            p=p->next; //avanzo di nodo
        }
    }
    else printf("Lista vuota");
    return NULL_CLIENTE; //se non trovo nessuno ritorno NULL
}
cliente NewAbbonamento(listaCliente l) {
    cliente temp;
    printf("\nBenvenuto! sei un nuovo cliente, lascia Cod Fiscale|Nome|Cognome|data di nascita| e quante settimane di abbonamento vuole fare!\n");
    scanf("%s",temp.cod_fis);
    scanf("%s",temp.nome);
    scanf("%s",temp.cogn);
    scanf("%s",temp.data);
    scanf("%d",&temp.abb);
    l=consListaC(l,temp); //Aggiungo cliente temp alla lista
    updateFileAbb(l); //aggiorno il file con il nuovo abbonato
 return temp;
}

/*  AnnullaAbbonamento: annulla l abbonamento di un cliente.
*  Precondizione: la lista può contenere 0 o più nodi,
*  la struttura cliente passata deve essere valida.
*
    Postcondizione: al cliente passato viene settato il
    campo abbonamento a 0, restituisce 1 se è andata a buon
    fine la funzione, 0 altrimenti.

    Funzionamento: Scorriamo la lista fino a quando non troviamo
    un incrocio tra nodo e cliente, se lo trova setta l'abbonamento
    a 0 e ritorna 1. Se non lo trova ritorna 0.
 */
int annullaAbbonamento(listaCliente l, const cliente c) {
    struct node_c *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            if (strcmp(p->val.cod_fis,c.cod_fis)==0) { //se trova il codice fiscale
                p->val.abb=0; //setta l abbonamento a 0
                return 1; //e la funzione va a buon fine
            }
            p=p->next; //avanzo di nodo
        }
    }
    return 0; //la funzione non è andata a buon fine
}

/*      updateSettimanale: ogni settimana passata diminuisce
 *      di 1 l abbonamento dei clienti.
 *
*       Precondizione:La lista l è correttamente riempita,
*       anche se può essere vuota.
        Postcondizione: a ogni cliente viene decrementato di 1 l'abbonamento.

        Funzionamento: Controllo se la lista è vuota, se non lo è
        scorro la lista e decremento il valore dell'abbonamento.
        Restituisco la lista con i valori aggiornati.
*/
listaCliente updateSettimanale(listaCliente l) {
    struct node_c *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            p->val.abb--; //decremento l abbonamento
            p=p->next; //avanzo di nodo
        }
    }
    return l;
}

void freeListaC(listaCliente l) {
    struct node_c *curr=l->testa;
    while (curr!=NULL) {
        struct node_c *temp=curr;
        curr=curr->next;
        free(temp);
    }
    free(l);
}
//-----------------FUNZIONI CODA_CLIENTE------------------------------------------
codaCliente newCoda() {
    codaCliente q=malloc(sizeof(struct CodaCliente)); //alloco lo spazio per creare la coda
    if (q==NULL) {
        return NULL;
    }
    //INIZIALIZZO
    q->num_clienti=0;
    q->testa=NULL;
    q->coda=NULL;
    return q;
}
int emptyCoda(codaCliente q) {
    if (q==NULL) {
        return -1;      //se la coda non esiste restituisce -1
    }
    return q->num_clienti==0; //se esiste ed e' vuota restituisce 1, 0 altrimenti
}
int enqueue(codaCliente q, const cliente c) {
    // -1= la coda non esiste | 0=nodo non creato correttamente | 1 esecuzione andata a buon fine
    if (q==NULL) {
        return -1;
    }
    struct node_c *nuovo=malloc(sizeof(struct node_c));
    if (nuovo==NULL) {
        return 0;
    }
    nuovo->val=c; //assegna il cliente dato come parametro al valore del nuovo nodo
    nuovo->next=NULL;
    if (q->testa==NULL) q->testa=nuovo; //se è il primo elemento della coda diventa la testa
    else q->coda->next=nuovo; // Altrimenti, collega il nuovo nodo alla fine della coda
    q->coda=nuovo;  //il nuovo nodo diventa la nuova coda
    q->num_clienti++; //incremento dei clienti
    return 1;
}
cliente dequeue(codaCliente q) {
    if (q==NULL || q->num_clienti==0 ) return NULL_CLIENTE; //Se la coda è vuota ritorno null
    cliente ris=q->testa->val; //prelevo il cliente
    struct node_c *temp=q->testa;
    q->testa=q->testa->next; //avanzo di un nodo
    free(temp);
    if (q->testa==NULL) q->coda=NULL; //se la testa della coda è vuota lo sara anche la fine
    q->num_clienti--;
    return ris;
}
void freeCoda(codaCliente q) {
    struct node_c *curr=q->testa;
    while (curr!=NULL) {
        struct node_c *temp=curr;
        curr=curr->next;
        free(temp);
    }
    free(q);
}
//-----------------FUNZIONI CLIENTE_H -------------------------------------------------
void output_cliente(cliente c) {
    printf("%s\t%-10s\t%-10s\t%-10s\t%-5d\n",c.cod_fis,c.nome,c.cogn,c.data,c.abb);
}
/*cliente input_cliente(char cod[],char n[],char c[],char d[], const int a) {
    cliente temp;
    strcpy(temp.cod_fis,cod);
    strcpy(temp.nome,n);
    strcpy(temp.cogn,c);
    strcpy(temp.data,d);
    temp.abb=a;
    return temp;
}*/
bool clienteNULL(cliente c) {
    if ((strcmp(c.cod_fis,"")==0) && (strcmp(c.nome,"")==0) && (strcmp(c.cogn,"")==0) && (strcmp(c.data,"")==0) && (c.abb==0)) return true;
    else return false;
}
//-----------------FUNZIONI LEZIONI_H---------------------------------------------------------
void output_lezione(lezione lez) {
    printf("Lezione: %s | Ora: %d | Prenotati: %d/%d\n",
               lez.desc, lez.ora, lez.pren, lez.maxpren);
}
const char* getDesc(const lezione* l) {
    return l->desc;
}

int getOra(const lezione* l) {
    return l->ora;
}

int getPren(const lezione* l) {
    return l->pren;
}

int getMaxPren(const lezione* l) {
    return l->maxpren;
}

void setDesc(lezione* l, const char* desc) {
    strncpy(l->desc, desc, MAX_L - 1);
    l->desc[MAX_L - 1] = '\0';
}

void setOra(lezione* l, int ora) {
    if (ora >= 0 && ora <= 23) {
        l->ora = ora;
    }
}

void setPren(lezione* l, int pren) {
        l->pren = pren;
}

void setMaxPren(lezione* l, int maxpren) {
        l->maxpren = maxpren;
}
//-----------------FUNZIONI LISTA_LEZIONI_H---------------------------------------------------

listaLezioni newListaL() {
    listaLezioni l=malloc(sizeof(struct ListaLezioni));
    if (l==NULL) { //controllo sulla malloc
        return NULL;
    }
    l->testa=NULL; //inizializzo la lista
    return l;
}
int emptyListaL(listaLezioni l) {
    if (l==NULL) {
        return -1;      //se la lista non esiste restituisce -1
    }
    return l->testa==NULL; //se esiste ed e' vuota restituisce 1, 0 altrimenti
}
void visualListaL(listaLezioni l) {
    const struct node_l *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaL(l)) {
        while (p!=NULL) {
            output_lezione(p->val); //Visualizzo a schermo il valore del nodo
            p=p->next;//avanzo di nodo
        }
    }else printf("Lista vuota");
}
listaLezioni consListaL(listaLezioni l, lezione lez) {
    struct node_l *nuovo = malloc(sizeof(struct node_l));
    nuovo->val = lez;
    nuovo->next = NULL;
        if (l->testa == NULL) {
        l->testa = nuovo;
        return l;
    }

    struct node_l *curr = l->testa;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = nuovo;
    return l;
}

/*  loadListaL: Legge il file e carica il contenuto nella lista
*
*   Precondizione: file deve essere il nome corretto del file da aprire
*   e avere il formato corretto dei dati mentre la lista l deve essere inizializzata.

    Postcondizione: La lista verrà riempita con tutte le lezioni scritte nel file.

    Funzionamento: Apriamo il file in lettura, leggiamo riga per riga il file e
    inseriamo in coda alla lista ogni lezione. Chiudiamo il file e ritorno la lista caricata.
 */
listaLezioni loadListaL(listaLezioni l,char file[]) {
    FILE *f = fopen(file, "r"); //apro il file in lettura
    if (f==NULL) { //controllo sull apertura del file
        perror("File non aperto");
    }
    char buffer[256]; //variabile temporanea per prelevare dal file
    while (fgets(buffer, sizeof(buffer), f)) { //finchè trova righe scritte nel file va avanti
        lezione temp;
        sscanf(buffer, "%s %d %d %d",temp.desc,&temp.ora,&temp.pren,&temp.maxpren); //prelevo
        l=consListaL(l,temp); //aggiungo alla lista
    }
    fclose(f); //chiudo il file
    return l; //ritorno la lista aggiornata
}

/*  mostraLezioniDisponibili: visualizza l'elenco delle lezioni
 *
*   Precondizione:la lista deve contenere almeno una lezione.
*
    Postcondizione: vengono stampate a schermo tutte le lezioni.
    Funzionamento: Usiamo un puntatore per scorrere la lista,
    e stamperemo ogni nodo fino alla fine della lista.
 */
void mostraLezioniDisponibili(listaLezioni lezioni) {
    struct node_l *curr = lezioni->testa;
    printf("\nLezioni disponibili:\n");
    while (curr != NULL) {
        output_lezione(curr->val);
        curr = curr->next;
    }
}

/*  salvaListaLezioni: salva il contenuto della lista in un file
*   Precondizione: la lista l deve essere valida e caricata,
*   file deve essere il nome del file da aprire.
*
    Postcondizione: tutte le lezioni presenti nella lista vengono scritte nel file.

    Funzionamento: apriamo il file in scrittura, usiamo un puntatore
    per scorrere la lista e ogni nodo viene scritto sul file nel
    formato predefinito, e infine chiudiamo il file.
 */
void salvaListaLezioni(listaLezioni lezioni, char filename[]) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Errore apertura file per salvataggio");
        return;
    }
    struct node_l *curr = lezioni->testa;
    while (curr != NULL) {
        fprintf(f, "%s %d %d %d\n",
                curr->val.desc, curr->val.ora,
                curr->val.pren, curr->val.maxpren);
        curr = curr->next;
    }
    fclose(f);
}

/*  prenotaLezione: aggiunge una prenotazione alla lezione scelta dall'utente
 *
*  Precondizione: la lista deve essere caricata con le lezioni disponibili,
*  file deve contenere il nome del file da aprire, contLezioni è un array
*  di 7 interi usato per contare le prenotazioni di ogni lezione.
*
   Postcondizione:il numero di prenotati della lezione scelta viene
   incrementato e scritto sul file, il contatore relativo a quella
   specifica lezione viene aumentato, restituisco 1 se la
   prenotazione è stata effettuata.

    Funzionamento: Stampiamo a schermo le lezioni disponibili,
    e attraverso un menù numerato facciamo scegliere la lezione
    e poi facciamo inserire anche l'orario. Cerchiamo nella lista
    la combinazione inserita dall'utente, verifichiamo la disponibilità se
    conferma la scelta, aggiorniamo il numero di prenotati, contLezione,
    salviamo sul file i cambiamenti e ritorniamo 1. Se la lezione non
    viene trovata o è piena ritorniamo 0.

 */
int prenotaLezione(listaLezioni lezioni,char nomefile[],int contLezioni[]) {
    char lezioneScelta[15];
    int oraScelta;
        mostraLezioniDisponibili(lezioni);

        // Menu numerato
    const char* lezioniDisponibili[] = {
        "Attrezzi", "Yoga", "Karate", "Pilates", "Funzionale", "Fitness", "Zumba"
    };
        int scelta = -1;
        printf("\nSeleziona una lezione tra le seguenti:\n");
        for (int i = 0; i < 7; i++) {
            printf("%d. %s\n", i + 1, lezioniDisponibili[i]);
        }
        do {
            printf("Scelta (1-7): ");
            if (scanf("%d", &scelta) != 1) {
                while (getchar() != '\n');
                scelta = -1;
                printf("Inserisci un numero tra 1 e 7.\n");
            }
        } while (scelta < 1 || scelta > 7);
        strcpy(lezioneScelta, lezioniDisponibili[scelta - 1]);
        strcat(lezioneScelta, "\0");
        // Orario
        printf("Inserisci l'orario della lezione: ");
        if (scanf("%d", &oraScelta)!=1) {
            while (getchar() != '\n');
            printf("Orario non disponibile ci scusiamo.\n");
        }

        // Cerca la lezione
        struct node_l *curr =lezioni->testa;
        while (curr != NULL) {
            int risposta = 0;
            if (strcmp(curr->val.desc, lezioneScelta) == 0 && curr->val.ora == oraScelta) {
                printf("\nLa lezione selezionata ha %d/%d posti\n", curr->val.pren, curr->val.maxpren);
                if (disponibilitaLezione(curr->val)>0) {
                    printf("\nVuoi prenotare la lezione? si=1|no=0 :");
                    scanf("%d", &risposta);
                    if (risposta == 1) {
                        contLezioni[scelta-1]++;
                        curr->val.pren++;
                        printf("\nSei il %d^ cliente della lezione\n", curr->val.pren);
                        salvaListaLezioni(lezioni, nomefile);
                    return 1; //1 = prenotazione effettuata
                        }

                }
              printf("\nLezione piena.\n");
            }
            curr = curr->next;
        }
     return 0; //0 = prenotazione non effettuata
}

/*  disponibilitaLezione: controlla quanti posti ci sono in una lezione
*   Precondizione: lez deve essere correttamente riempito e
*   quindi lez.pren deve essere minore di lez.maxpren.
*
    Postcondizione: la funzione restituisce il numero di posti disponibili.

    Funzionamento: Ritorniamo la differenza tra il
    massimo di posti prenotabili e quelli prenotati.
 */
int disponibilitaLezione(lezione l) {
    return l.maxpren-l.pren;
}

/*  resetFile: inizializzo il numero di prenotazioni di ogni lezione
*   Precondizione: le macro sui file devono essere corrette.
*
    Postcondizione: a tutti i file dal lunedi al sabato verrà
    impostato il campo pren a 0.

    Funzionamento: Definisco un array contenente tutti i nomi dei
    file, creo e carico una lista con tutte le lezioni, setto
    il numero di prenotati a 0 e salvo su file la lista.

 */
void resetFile() {
    char *nomefile[]={lunedi,martedi,mercoledi,giovedi,venerdi,sabato};
    for (int i=0;i<6;i++) {
        listaLezioni ll=newListaL();
        ll=loadListaL(ll,nomefile[i]);
        struct node_l *curr=ll->testa;
        while (curr!=NULL) {
            curr->val.pren=0;
            curr=curr->next;
        }
        salvaListaLezioni(ll,nomefile[i]);
        freeListaL(ll);
    }

}

void freeListaL(listaLezioni l) {
    struct node_l *curr=l->testa;
    while (curr!=NULL) {
        struct node_l *temp=curr;
        curr=curr->next;
        free(temp);
    }
    free(l);
}