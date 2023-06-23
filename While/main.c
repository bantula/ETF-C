#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Sastaviti program na programskom jeziku C za
određivanje broja velikih slova, malih slova i
cifara u tekstu koji se iz proizvoljnog broja redova
učitava preko glavne ulazne jedinice.
Tekst se završava znakom za kraj datoteke. */

int main()
{
    int znak, velika = 0, mala = 0, brojevi = 0;
    while((znak = getchar()) != EOF)
    {
        velika += isupper(znak)? 1:0;
        mala += islower(znak)? 1:0;
        brojevi += isdigit(znak)? 1:0;
    }
    printf("%d %d %d", velika, mala, brojevi);
return 0;
}
