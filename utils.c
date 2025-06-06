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
    listaCliente l=malloc(sizeof(struct ListaCliente));
    if(l!=NULL) l->testa=NULL;
    return l;
}

int emptyListaC(listaCliente l) {
    return l->testa==NULL; //Se la testa è uguale a NULL restituisce 1, 0 altrimenti
}
void visualizzaListaC(listaCliente l) {
    struct node_c *curr = l->testa;
    printf("\nLista abbonati:\n");
    while (curr != NULL) {
        output_cliente(curr->val);
        curr = curr->next;
    }
}
listaCliente consListaC(listaCliente l, const cliente c) {
    struct node_c *nuovo = malloc(sizeof(struct node_c));
    if (nuovo!=NULL) {
        setCliente(&(nuovo->val), &c);
        nuovo->next=l->testa;
        l->testa=nuovo;
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
    FILE *f = fopen(NOMEFILE, "r");
    if (f==NULL) {
        perror("File non aperto");
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        char cod_fis[17], nome[MAX_L], cogn[MAX_L], data[11];
        int abb;
        sscanf(buffer, "%s %s %s %s %d",cod_fis,nome,cogn,data,&abb);

        setCodFis(&temp, cod_fis);
        setNome(&temp, nome);
        setCognome(&temp, cogn);
        setData(&temp, data);
        setAbbonamento(&temp, abb);

        if (getAbbonamento(&temp))l = consListaC(l, temp);
        else {
            flag=true; //se ci sono abbonamenti scaduti la flag diventa true
        }
    }
    fclose(f);
    if (flag) {
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
    struct node_c *corr=l->testa;
    struct node_c *prec=NULL;
    printf("Lista di clienti cancellati per ABBONAMENTO SCADUTO o ABBONAMENTO ANNULLATO\n");
    while (corr!=NULL) {
        if (getAbbonamento(&(corr->val))<=0) {
            output_cliente(corr->val);
            if (prec==NULL) {
                l->testa=corr->next;
                free(corr);
                corr=l->testa;
            } else {
                prec->next=corr->next;
                free(corr);
                corr=prec->next;
            }
        }
        else {
            prec=corr;
            corr=corr->next;
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
    struct node_c *p=l->testa;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            if (strcmp(getCodFis(&(p->val)), getCodFis(&c)) == 0) {
                int abb = getAbbonamento(&(p->val));
                setAbbonamento(&(p->val), abb + r);
                updateFileAbb(l);
               return 1;
            }
            p=p->next;
        }
    }
    return 0;
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
    FILE *f = fopen(NOMEFILE, "w");
    struct node_c *p=l->testa;
    if (f==NULL) {perror("File non aperto");}
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            fprintf(f, "%s %s %s %s %d\n",
                       getCodFis(&(p->val)),
                       getNome(&(p->val)),
                       getCognome(&(p->val)),
                       getData(&(p->val)),
                       getAbbonamento(&(p->val)));
        p=p->next;
        }
    }
    fclose(f);
}

int sizeListaC(listaCliente l) {
    struct node_c *p=l->testa;
    int cont=0;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            cont++;
            p=p->next;
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

    struct node_c *p=l->testa;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            if (strcmp(getCodFis(&(p->val)), cod) == 0) {
                cliente temp;
                setCliente(&temp, &(p->val));
                return temp;
            }
            p=p->next;
        }
    }
    else printf("Lista vuota");
    return NULL_CLIENTE; //se non trovo nessuno ritorno NULL
}
cliente NewAbbonamento(listaCliente l) {
    cliente temp;
    char buffer_codfis[17];
    char buffer_nome[MAX_L];
    char buffer_cogn[MAX_L];
    char buffer_data[11];
    int abb;
    printf("\nBenvenuto! sei un nuovo cliente, lascia Cod Fiscale|Nome|Cognome|data di nascita| e quante settimane di abbonamento vuole fare!\n");
    scanf("%s",buffer_codfis);
    scanf("%s",buffer_nome);
    scanf("%s",buffer_cogn);
    scanf("%s",buffer_data);
    scanf("%d",&abb);

    setCodFis(&temp, buffer_codfis);
    setNome(&temp, buffer_nome);
    setCognome(&temp, buffer_cogn);
    setData(&temp, buffer_data);
    setAbbonamento(&temp, abb);

    l=consListaC(l,temp);
    updateFileAbb(l);
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
    struct node_c *p=l->testa;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            if (strcmp(getCodFis(&(p->val)), getCodFis(&c)) == 0) {
                setAbbonamento(&(p->val), 0);
                return 1;
            }
            p=p->next;
        }
    }
    return 0;
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
    struct node_c *p=l->testa;
    if (!emptyListaC(l)) {
        while (p!=NULL) {
            int abb = getAbbonamento(&(p->val));
            setAbbonamento(&(p->val), abb - 1);
            p=p->next;
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
    setCliente(&(nuovo->val), &c);
    nuovo->next=NULL;
    if (q->testa==NULL) q->testa=nuovo; //se è il primo elemento della coda diventa la testa
    else q->coda->next=nuovo; // Altrimenti, collega il nuovo nodo alla fine della coda
    q->coda=nuovo;  //il nuovo nodo diventa la nuova coda
    q->num_clienti++; //incremento dei clienti
    return 1;
}
cliente dequeue(codaCliente q) {
    if (q==NULL || q->num_clienti==0 ) return NULL_CLIENTE; //Se la coda è vuota ritorno null
    cliente ris;
    setCliente(&ris, &(q->testa->val));
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
    printf("%s\t%-10s\t%-10s\t%-10s\t%-5d\n",getCodFis(&c),getNome(&c),getCognome(&c),getData(&c),getAbbonamento(&c));
}

bool clienteNULL(cliente c) {
    if ((strcmp(c.cod_fis,"")==0) && (strcmp(c.nome,"")==0) && (strcmp(c.cogn,"")==0) && (strcmp(c.data,"")==0) && (c.abb==0)) return true;
    else return false;
}

void setCodFis(cliente* c, const char* cod) {
    strncpy(c->cod_fis, cod, 16);
    c->cod_fis[16] = '\0';
}

void setNome(cliente* c, const char* nome) {
    strncpy(c->nome, nome, MAX_L - 1);
    c->nome[MAX_L - 1] = '\0';
}

void setCognome(cliente* c, const char* cogn) {
    strncpy(c->cogn, cogn, MAX_L - 1);
    c->cogn[MAX_L - 1] = '\0';
}

void setData(cliente* c, const char* data) {
    strncpy(c->data, data, 10);
    c->data[10] = '\0';
}

void setAbbonamento(cliente* c, int abb) {
    c->abb = abb;
}
void setCliente(cliente* dest, const cliente* src) {
    setCodFis(dest, getCodFis(src));
    setNome(dest, getNome(src));
    setCognome(dest, getCognome(src));
    setData(dest, getData(src));
    setAbbonamento(dest, getAbbonamento(src));
}

const char* getCodFis(const cliente* c) {
    return c->cod_fis;
}

const char* getNome(const cliente* c) {
    return c->nome;
}

const char* getCognome(const cliente* c) {
    return c->cogn;
}

const char* getData(const cliente* c) {
    return c->data;
}

int getAbbonamento(const cliente* c) {
    return c->abb;
}
//-----------------FUNZIONI LEZIONI_H---------------------------------------------------------
void output_lezione(lezione lez) {
    printf("Lezione: %s | Ora: %d | Prenotati: %d/%d\n",
               getDesc(&lez), getOra(&lez), getPren(&lez),getMaxPren(&lez));
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
    if (l==NULL) {
        return NULL;
    }
    l->testa=NULL;
    return l;
}
int emptyListaL(listaLezioni l) {
    if (l==NULL) {
        return -1;      //se la lista non esiste restituisce -1
    }
    return l->testa==NULL; //se esiste ed e' vuota restituisce 1, 0 altrimenti
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
    FILE *f = fopen(file, "r");
    if (f==NULL) {
        perror("File non aperto");
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        lezione temp;
        char desc[MAX_L];
        int ora, pren, maxpren;
        if (sscanf(buffer, "%s %d %d %d",desc,&ora,&pren,&maxpren)== 4) {
            setDesc(&temp, desc);
            setOra(&temp, ora);
            setPren(&temp, pren);
            setMaxPren(&temp, maxpren);
        }
        l=consListaL(l,temp);
    }
    fclose(f); 
    return l;
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
        fprintf(f, "%s %d %d %d\n",getDesc(&(curr->val)),
                getOra(&(curr->val)),
                getPren(&(curr->val)),
                getMaxPren(&(curr->val)));
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
            if (strcmp(getDesc(&(curr->val)), lezioneScelta) == 0 && getOra(&(curr->val)) == oraScelta) {
                int pren = getPren(&(curr->val));
                int maxpren = getMaxPren(&(curr->val));
                printf("\nLa lezione selezionata ha %d/%d posti\n",pren,maxpren);
                if (disponibilitaLezione(curr->val)>0) {
                    printf("\nVuoi prenotare la lezione? si=1|no=0 :");
                    scanf("%d", &risposta);
                    if (risposta == 1) {
                        contLezioni[scelta-1]++;
                        setPren(&(curr->val), pren + 1);
                        printf("\nSei il %d^ cliente della lezione\n", getPren(&(curr->val)));
                        salvaListaLezioni(lezioni, nomefile);
                    return 1; //1 = prenotazione effettuata
                        }

                }

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
    return getMaxPren(&l) - getPren(&l);
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
            setPren(&(curr->val), 0);
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