#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct elem {
    int broj;
    struct elem *sled;
} Elem;

int duz(Elem *lst){
    Elem *tek;
    int n = 0;
    for(tek = lst; tek; tek = tek -> sled){
        n++;
    }
    return n;
}
void main(){
    Elem *head = malloc(sizeof(Elem));
    head -> broj = 45;
    head -> sled = NULL;
    int b = duz(head);
    printf("%d", b);
    return 0;
}


