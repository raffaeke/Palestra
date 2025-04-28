#ifndef LEZIONI_H
#define LEZIONI_H
#define MAX_L 30
typedef struct {
    char desc[MAX_L]; //Nome corso
    int ora;  //Ora di inizio
    int pren; //posti prenotati
    int maxpren; //numero massimo di posti
}lezione;

lezione input_lezione(char[],int,int,int);
void output_lezione(lezione);
#endif //LEZIONI_H
