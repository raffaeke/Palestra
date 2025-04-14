#include <stdio.h>
#include "cliente.h"
#include"cliente_lista.h"

int main(void) {
    listaCliente l = newLista();
    l=LoadInizio(l);
    visualLista(l);
    printf("\nCi sono %d iscritti\n",sizeLista(l));
    cliente c=trovaCliente(l,"rfde");
    if (!clienteNULL(c)){
        printf("\nErrore, nessun cliente trovato");
    }
    else output_cliente(c);
    return 0;
}