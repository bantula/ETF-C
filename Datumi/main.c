#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Sastaviti na jeziku C program za određivanje
narednog datuma u odnosu na zadati dan.
Program treba da čita datume i da ispisuje
rezultate sve dok za jednu od komponenata
datuma ne pročita nulu. */

int main()
{
    int dan, mes, god, d;

    while(1){
        printf ("Danas? ");
        scanf ("%d%d%d", &dan, &mes, &god);
        if (dan==0 || mes==0 || god==0) break;

        /* Broj dana u tekucem mesecu: */
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                d = 31; break;
            case 4: case 6: case 9: case 11:
                d = 30; break;
            case 2:
                d = 28 + (god%4==0 && god%100!=0 || god%400==0); break;
        }

        if (dan < d) dan++;
        else {
            dan = 1;
            if (mes < 12) mes++;
            else { mes = 1; god++; }
        }
        printf ("Sutra= %2.2d. %2.2d. %d.\n\n",dan,mes,god);

    }

    return 0;
}
