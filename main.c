
#include"cliente_lista.h"

int main(void) {
    listaCliente l = newLista();
    l=LoadInizio(l);
    visualLista(l);
    return 0;
}