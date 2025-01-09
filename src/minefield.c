#include "minefield.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
Metody zwiazane z polami i polem minowym, generowanie, liczenie bliskosci, aktualizowanie i wyswietlanie
*/

minefield* create_minefield(int x, int y, int ile_bomb) {
    minefield* plansza = malloc(sizeof(minefield));
    // inicjalizacja pustej planszy
    plansza->x = x;
    plansza->y = y;
    plansza->fields = malloc(x * sizeof(field *));
    for (int i = 0; i < x; i++) {
        plansza->fields[i] = malloc(y * sizeof(field));
    } 
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            field new_field;
            new_field.bomb = 0;
            new_field.flag = 0;
            new_field.hidden = 1;
            new_field.bombs_near = 0;
            plansza->fields[i][y] = new_field;
        }
    }
    // losowanie bomb
    srand(time(NULL));
    for (int i = 0; i < ile_bomb; i++) {
        plansza->fields[rand()%x][rand()%y].bomb = 1;
    }
    // TODO: funkcja obliczajaca bombs_near

    
    return plansza;
}
void display_minefield(minefield* plansza) {
    if (plansza == NULL) return;
    for (int i = 0; i < plansza->x; i++) {
        for (int j = 0; j < plansza->y; j++) {
            printf("  %d", plansza->fields[i][j].bomb);
        }
        printf("\n");
    }
}
