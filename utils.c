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

void visualListaC(listaCliente l) {
    const struct node_c *p=l->testa; //puntatore alla testa della lista
    if (!emptyListaC(l)) { //controllo se la lista è vuota
       while (p!=NULL) { //finché il puntatore non arriva alla fine della lista
           output_cliente(p->val); //stampo i dati del nodo
           p=p->next; //Avanzo di nodo
       }
    }
    else printf("Lista vuota");

}

listaCliente rimuoviAbbonamenti(listaCliente l) {
    struct node_c *corr=l->testa; //nodo corrente
    struct node_c *prec=NULL; //puntatore al nodo precedente
    printf("Lista di clienti cancellati per ABBONAMENTO SCADUTO o ABBONAMENTO ANNULLATO\n");
    while (corr!=NULL) { //finché il puntatore non arriva alla fine della lista
        if (corr->val.abb<=0) { //se l abbonamento è minore o uguale a 0
            output_cliente(corr->val); //stampo i dati del cliente
            if (prec==NULL) l->testa=corr->next; //Il nodo da eliminare è in testa
            else prec->next=corr->next; //Salta il nodo da eliminare collegando il precedente al successivo
            free(corr); //Libera lo spazio del nodo corrente
            return l;
        }
        prec=corr; //Il precedente prende il valore del nodo corrente
        corr=corr->next; //il nodo corrente avanza
    }
    return l;
}
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
    printf("\n%s\t%-5d\n",lez.desc,lez.ora);
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
listaLezioni consListaL(listaLezioni l,lezione lez) {
    struct node_l *nuovo=malloc(sizeof(struct node_l)); //Alloca lo spazio per un nuovo nodo
    if (nuovo!=NULL) {//controllo sulla malloc
        nuovo->val=lez;//assegno il valore al nodo
        nuovo->next=l->testa; //lo collego alla lista
        l->testa=nuovo;//diventa la testa della lista
    }
    return l;
}
listaLezioni loadListaL(listaLezioni l,char file[]) {
    FILE *f = fopen(file, "r"); //apro il file in lettura
    if (f==NULL) { //controllo sull aperuta del file
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