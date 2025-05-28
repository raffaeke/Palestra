#include<stdio.h>
#include"cliente_lista.h"
#include <stdlib.h>
#include <time.h>
#include "cliente_coda.h"
#include "lista_lezioni.h"
/*Test della gestione degli abbonamenti e della verifica della validità. */
int main(void) {
    listaCliente l=newListaC();
    l=LoadInizio(l);
    cliente c={"ABCDEFGHI","NOME","COGNOME","00/00/0000", 0};
    l=consListaC(l,c);
    visualizzaListaC(l);
    l=rimuoviAbbonamenti(l);
    visualizzaListaC(l);
}
