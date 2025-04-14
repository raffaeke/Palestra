#include "cliente.h"
#include "cliente_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
const cliente NULL_CLIENTE = {"","","","", 0};
struct node {
    cliente val;
    struct node *next;
};
struct ListaCliente {
    struct node *testa;
};
#define NOMEFILE "abbonati.txt"
listaCliente newLista() {
    listaCliente l=malloc(sizeof(struct ListaCliente));
    if(l!=NULL) l->testa=NULL;
    return l;
}
int emptyLista(listaCliente l) {
    return l->testa==NULL;
}

listaCliente consLista(listaCliente l, const cliente c) {
    struct node *nuovo = malloc(sizeof(struct node));
    if (nuovo!=NULL) {
        nuovo->val=c;
        nuovo->next=l->testa;
        l->testa=nuovo;
    }
    return l;
}

listaCliente LoadInizio(listaCliente l) {
    cliente temp;
    bool flag=false;
    FILE *f = fopen(NOMEFILE, "r");
    if (f==NULL) {
        perror("File non aperto");
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "%s %s %s %s %d", temp.cod_fis, temp.nome, temp.cogn, temp.data, &temp.abb);
        if (temp.abb>0)l = consLista(l, temp);
        else {
            flag=true;
        }
    }
    fclose(f);
    if (flag) {
        Updatefile(l);
    }
    return l;
}

void visualLista(listaCliente l) {
    const struct node *p=l->testa;
    if (!emptyLista(l)) {
       while (p!=NULL) {
           output_cliente(p->val);
           p=p->next;
       }
    }
    else printf("Lista vuota");

}
listaCliente rimuoviCliente(listaCliente l) {
    struct node *corr=l->testa; //nodo corrente
    struct node *prec=NULL; //puntatore al nodo precedente
    while (corr!=NULL) {
        if (corr->val.abb<=0) {
            if (prec==NULL) l->testa=corr->next;
            else prec->next=corr->next;
            free(corr);
            return l;
        }
        prec=corr;
        corr=corr->next;
    }
    return l;
}
void Updatefile(listaCliente l) {
    FILE *f = fopen(NOMEFILE, "w");
    struct node *p=l->testa;
    if (f==NULL) {perror("File non aperto");}
    if (!emptyLista(l)) {
        while (p!=NULL) {
        fprintf(f,"%s %s %s %s %d\n",p->val.cod_fis,p->val.nome,p->val.cogn,p->val.data,p->val.abb);
        p=p->next;
        }
    }
    fclose(f);
}
int sizeLista(listaCliente l) {
    struct node *p=l->testa;
    int cont=0;
    if (!emptyLista(l)) {
        while (p!=NULL) {
            cont++;
            p=p->next;
        }
    }
    return cont;
}
//-----------------FUNZIONI CLIENTE_H -------------------------------------------------
void output_cliente(cliente c) {
    printf("%s\t%-10s\t%-10s\t%-10s\t%-5d\n",c.cod_fis,c.nome,c.cogn,c.data,c.abb);
}
cliente input_cliente(char cod[],char n[],char c[],char d[], const int a) {
    cliente temp;
    strcpy(temp.cod_fis,cod);
    strcpy(temp.nome,n);
    strcpy(temp.cogn,c);
    strcpy(temp.data,d);
    temp.abb=a;
    return temp;
}