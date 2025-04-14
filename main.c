#include"cliente.h"
#include"cliente_lista.h"
//
// Created by Raffaele on 12/04/2025.
//
int main(void) {
    listaCliente l = newLista();
    l=LoadInizio(l);
    visualLista(l);
    return 0;
}