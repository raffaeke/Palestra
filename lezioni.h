#ifndef LEZIONI_H
#define LEZIONI_H
#define MAX_L 30
#define lunedi "lunedi.txt"
#define martedi "martedi.txt"
#define mercoledi "mercoledi.txt"
#define giovedi "giovedi.txt"
#define venerdi "venerdi.txt"
#define sabato "sabato.txt"

typedef struct {
    char desc[MAX_L]; //Nome corso
    int ora;  //Ora di inizio
    int pren; //posti prenotati
    int maxpren; //numero massimo di posti
}lezione;

void output_lezione(lezione);

//get
const char* getDesc(const lezione*);
int getOra(const lezione*);
int getPren(const lezione*);
int getMaxPren(const lezione*);

// Set
void setDesc(lezione*, const char*);
void setOra(lezione*, int);
void setPren(lezione*, int);
void setMaxPren(lezione*, int);
#endif //LEZIONI_H
