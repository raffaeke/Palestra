#ifndef CLIENTE_LISTA_H
#define CLIENTE_LISTA_H
#include "cliente.h"
#define NOMEFILE "abbonati.txt"
typedef struct ListaCliente* listaCliente;

listaCliente newListaC(); //Crea una nuova lista

int emptyListaC(listaCliente); //verifica se la lista e' vuota

void visualizzaListaC(listaCliente); //visualizza la lista

listaCliente consListaC(listaCliente,cliente); //Aggiunge il cliente passato nei parametri in testa alla lista

/*      loadInizio: carica i dati degli abbonati dal file
 *     Precondizione: la lista deve essere possibilmente vuota,
      inoltre deve esistere un file definito come "NOMEFILE".

     Postcondizione: restituisce una lista contenente tutti gli
     abbonati con abbonamento maggiore di 0 letti dal file.*/
listaCliente LoadInizio(listaCliente);

/*      trovaCliente: trova un cliente nella lista.
 *       Precondizione: la lista deve contenere dei clienti,
        o eventualmente essere vuota. Cod è una stringa che
        contiene il codice fiscale da ricercare.

         Postcondizione: se esiste un cliente nella lista con
         quel codice fiscale lo restituisce. Se invece non viene
         trovato, restituiamo NULLCLIENTE.*/
cliente trovaCliente(listaCliente,char[]); //trova il cliente tramite cod fiscale

/*  rimuoviAbbonamenti: rimuove chi ha l abbonamento scaduto o annullato.
 *  Precondizione: la lista deve contenere dei clienti,
 *  o eventualmente essere vuota.
 *
 *  Postcondizione: restituisce una lista contenente tutti gli
 *  abbonati con abbonamento maggiore di 0 letti dal file.
 *
 */
listaCliente rimuoviAbbonamenti(listaCliente);

int sizeListaC(listaCliente); //SI USA PER IL REPORT

/*    updateFileAbb: Scrive su file solo chi ha abb>0.
*    Precondizione: la lista deve contenere tutti gli abbonati
*    validi, deve essere definita una macro "NOMEFILE".

     Postcondizione:Il file passato verrà riempito da capo con
     gli elementi della lista.
 */
void updateFileAbb(listaCliente);

/*      updateSettimanale: ogni settimana passata diminuisce
 *      di 1 l abbonamento dei clienti.
 *
*       Precondizione:La lista l è correttamente riempita,
*       anche se può essere vuota.
        Postcondizione: a ogni cliente viene decrementato di 1 l'abbonamento.
 */
listaCliente updateSettimanale(listaCliente);

cliente NewAbbonamento(listaCliente); //Richiede i dati personali all utente per creare un abbonamento a suo nome

/*  RinnovaAbbonamento: rinnova l abbonamento di un cliente.
*  Precondizione:la lista deve essere caricata,
*  cliente c non deve essere NULL,
*  r deve essere maggiore di 0
*
    Postcondizione: Incrementa le settimane di abbonamento
    del cliente passato di r settimane
 */
int RinnovaAbbonamento(listaCliente,cliente, int);

/*  AnnullaAbbonamento: annulla l abbonamento di un cliente.
*  Precondizione: la lista può contenere 0 o più nodi,
*  la struttura cliente passata deve essere valida.
*
    Postcondizione: al cliente passato viene settato il
    campo abbonamento a 0, restituisce 1 se è andata a buon
    fine la funzione, 0 altrimenti.
 */
int annullaAbbonamento(listaCliente,cliente);

void freeListaC(listaCliente); //Libera la memoria occupata dalla lista
#endif //CLIENTE_LISTA_H
