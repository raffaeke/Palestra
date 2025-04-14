#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct{
    char cod_fis[17];
    char nome[30];
    char cogn[30];
    char data[11];// 00/00/0000
    int abb;
}cliente;
extern const cliente NULL_CLIENTE;

cliente input_cliente(char[],char[],char[],char[],int); //Prende come parametri i valori per riempiere la struct ciente e restituisce una variabile cliente con quei dati al suo interno
void output_cliente(cliente);//Stampa il contenuto della struct


#endif // CLIENTE_H
