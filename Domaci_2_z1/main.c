#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct racun {
    char naziv[20]; //naziv racuna u hexadekadnom obliku ali je string
    float pare; //koliko trenutno para ima na racunu
    struct racun *sled; //pokazivac koji pokazuje na sledeci clan liste
}Racun;


int ima_li_ga(char naslov[], Racun *head){ //funkcija proverava da li postoji racun vec napravljen u listi
    Racun *curr;
    for(curr = head; curr; curr = curr -> sled){
        if(strcmp(naslov, curr -> naziv) == 0){
            return 1;
        }
    }
    return 0;
}


void dodaj_pare(char naslov[], Racun *head, double dodatak){ //funkcija dodaje pare na racun
    Racun *curr;
    for(curr = head; curr; curr = curr -> sled){
        if(strcmp(naslov, curr -> naziv) == 0){
            curr -> pare += dodatak;
            return;
        }
    }
}


int oduzmi_pare(char naslov[], Racun *head, double manjak){ //funkcija oduzima pare sa racuna
    Racun *curr;
    for(curr = head; curr; curr = curr -> sled){
        if(strcmp(naslov, curr -> naziv) == 0){
            if(curr -> pare >= manjak){
                curr -> pare -= manjak;
                return 1;
            }else{
                return 0;
            }
        }
    }
}


void novi_racun(Racun **head, char naziv_r[], double novac) { //ima bolji nacin ali mrzi me da menjam
    Racun *novi = (Racun*)malloc(sizeof(Racun));
    strcpy(novi -> naziv, naziv_r);
    novi -> pare = novac;
    novi->sled = NULL;

    if (*head == NULL) { //ovo je ako je u pitanju prvi racun
        *head = novi;
    } else { //ovo je ako se dodaje novi raun na postojecu listu
        Racun *curr = *head;
        while (curr->sled != NULL) { //prebacuje pokazivace sve dok ne dodje do kraja
            curr = curr->sled;
        }
        curr->sled = novi; //da bi ovde umesto null postavio novi racun
    }
}


void zamena(char a[], char b[], float* broj1, float* broj2) { //menja dva racuna
    char temp[20];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);

    float tempbr = *broj1;
    *broj1 = *broj2;
    *broj2 = tempbr;
}


void sortiranje(Racun* head) { //sortira celu listu
    if (head == NULL || head->sled == NULL)
        return;

    int menjanje;
    Racun* last = NULL;

    for (Racun* i = head; i->sled != last; i = i->sled) {
        menjanje = 0;

        for (Racun* j = head; j->sled != last; j = j->sled) {
            if (strcmp(j->naziv, j->sled->naziv) > 0) {
                zamena(j->naziv, j->sled->naziv, &j->pare, &j->sled->pare);
                menjanje = 1;
            }
        }

        if (!menjanje){
            break;
        }
    }
}


void stampa(Racun *head, FILE *fajl) { //stampa u novi fajl listu
    Racun *curr = head;
    while (curr != NULL) {
        if(curr -> sled == NULL){
            fprintf(fajl, "A(%s) = %.2lf", curr -> naziv, curr -> pare);
        }else{
            fprintf(fajl, "A(%s) = %.2lf\n", curr -> naziv, curr -> pare);
        }
        curr = curr -> sled;
    }
}


void oslobadjanje(Racun **head) {
    Racun *curr = *head;
    Racun *temp = *head;
    while (curr != NULL) {
        temp = curr -> sled;
        free(curr);
        curr = temp;
    }
    *head = NULL;
}


int main(int argc, char *argv[]) //zadati argumenti u zadatku
{
    FILE *fajl_prvi = fopen(argv[1], "r"); //fajl sa kog se citaju tranzakcije

    if( fajl_prvi == NULL){
        printf("DAT_GRESKA");
        return 0;
    }

    FILE *fajl_drugi = fopen(argv[2], "w"); //fajl u kome se pisu odbijene tr i pare na svakom racunu

    char racun1[20], racun2[20]; //racun1 -> sa njega se oduzimaju pare ; racun2 -> racun na koji se dodaju pare
    double iznos = atof(argv[3]);
    double transakcija;

    Racun *head = NULL;

    while(fscanf(fajl_prvi, "\n%[^ ] -> %[^:]: %lf", &racun1, &racun2, &transakcija) == 3){
        if(ima_li_ga(racun1, head) == 0){
            novi_racun(&head, racun1, iznos);
        }
        if(ima_li_ga(racun2, head) == 0){
            novi_racun(&head, racun2, iznos);
        }
        if(oduzmi_pare(racun1, head, transakcija) == 1){
            dodaj_pare(racun2, head, transakcija);
        }else{
            fprintf(fajl_drugi, "T(%s -> %s) = %.2lf DENIED\n", racun1, racun2, transakcija);
        }
    }

    sortiranje(head);

    stampa(head, fajl_drugi);

    oslobadjanje(&head);

    fclose(fajl_prvi);
    fclose(fajl_drugi); //zatvaram fajlove
    return 0;
}
