#ifndef LISTA_LEZIONI_H
#define LISTA_LEZIONI_H
#include "lezioni.h"

typedef struct ListaLezioni* listaLezioni;

listaLezioni newListaL(); //Crea la lista

int emptyListaL(listaLezioni);//Verifica se la lista è vuota

listaLezioni consListaL(listaLezioni,lezione);//Aggiunge in coda la lezione passata come parametro

/*  loadListaL: Legge il file e carica il contenuto nella lista
*
*   Precondizione: file deve essere il nome corretto del file da aprire
*   e avere il formato corretto dei dati mentre la lista l deve essere inizializzata.

    Postcondizione: La lista verrà riempita con tutte le lezioni scritte nel file.
 */
listaLezioni loadListaL(listaLezioni,char[]);

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
 */
int prenotaLezione(listaLezioni,char[],int[]);

/*  mostraLezioniDisponibili: visualizza l'elenco delle lezioni
 *
*   Precondizione:la lista deve contenere almeno una lezione.
*
    Postcondizione: vengono stampate a schermo tutte le lezioni.

 */
void mostraLezioniDisponibili(listaLezioni);

/*  disponibilitaLezione: controlla quanti posti ci sono in una lezione
*   Precondizione: lez deve essere correttamente riempito e
*   quindi lez.pren deve essere minore di lez.maxpren.
*
    Postcondizione: la funzione restituisce il numero di posti disponibili.

 */
int disponibilitaLezione(lezione);

/*  salvaListaLezioni: salva il contenuto della lista in un file
*   Precondizione: la lista l deve essere valida e caricata,
*   file deve essere il nome del file da aprire.
*
    Postcondizione: tutte le lezioni presenti nella lista vengono scritte nel file.

 */
void salvaListaLezioni(listaLezioni,char[]);

/*  resetFile: inizializzo il numero di prenotazioni di ogni lezione
*   Precondizione: le macro sui file devono essere corrette.
*
    Postcondizione: a tutti i file dal lunedi al sabato verrà
    impostato il campo pren a 0.

 */
void resetFile();

void freeListaL(listaLezioni); //libera la memoria occupata dalla lista
#endif //LISTA_LEZIONI_H
