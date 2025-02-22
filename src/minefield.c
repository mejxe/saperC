#include "minefield.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 1024
#define COLOR_1 "\x1b[2;30;46m"
#define COLOR_CLEAR "\x1b[0m"
/*
Metody zwiazane z polami i polem minowym, generowanie, liczenie bliskosci, aktualizowanie i wyswietlanie
*/

minefield* create_minefield(int x, int y, int ile_bomb) {
    minefield* plansza = (minefield*)malloc(sizeof(minefield));
    // inicjalizacja pustej planszy
    plansza->x = x;
    plansza->y = y;
    plansza->fields = malloc(x * sizeof(field));
    plansza->ile_bomb = ile_bomb;
    for (int i = 0; i < x; i++) {
        plansza->fields[i] = malloc(y * sizeof(field));
    } 
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            field* new_field = (field*) malloc(sizeof(field));
            new_field->bomb = 0;
            new_field->flag = 0;
            new_field->hidden = 1;
            new_field->bombs_near = 0;
            plansza->fields[i][j] = new_field;
        }
    }
    // losowanie bomb
    srand(time(NULL));
    
    for (int i = 0; i < ile_bomb; i++) {
        int x_random = rand()%x;
        int y_random = rand()%y;
        if (plansza->fields[x_random][y_random]->bomb) {
            i--;
            continue;
        };
        plansza->fields[x_random][y_random]->bomb = 1;
    }
    check_proximity(plansza);

    
    return plansza;
}
void display_minefield(minefield* plansza) {
    if (plansza == NULL) return;
     printf("   ");
    for (int i = 0; i < plansza->y; i++)
    {
        if(i < 10){
            printf("  %d",i);
        }
        else{
         printf(" %d",i);
        }
    }
     printf("\n");
    
    for (int i = 0; i < plansza->x; i++) {
        
        if(i < 10){
            printf("  %d",i);
        }
        else{
            printf(" %d",i);
        }
        
        for (int j = 0; j < plansza->y; j++) {
           

            if ( plansza->fields[i][j]->flag ) {
                printf ("%s 🚩%s",COLOR_1,COLOR_CLEAR);
            }
            else if ( plansza->fields[i][j]->hidden ) {
                printf ("  ■");
            }
            else {
                printf("\x1b[2;30;46m %d \x1b[0m", plansza->fields[i][j]->bombs_near);
            }
        }
        printf("\n");
    }
}
void check_proximity(minefield *plansza) {
    for ( int i = 0; i < plansza->x; i++ ) {
        for ( int j = 0; j < plansza->y; j++ ) {
            if (i < plansza->x-1 && plansza->fields[i+1][j]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (j < plansza->y-1 && plansza->fields[i][j+1]->bomb ) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (i < plansza->x-1 && j < plansza->y-1 && plansza->fields[i+1][j+1]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (i > 0 && plansza->fields[i-1][j]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (j > 0 && plansza->fields[i][j-1]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (i > 0 && j > 0 && plansza->fields[i-1][j-1]->bomb ) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (i < plansza->x-1 && j > 0 && plansza->fields[i+1][j-1]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
            if (i > 0 && j < plansza->y-1 && plansza->fields[i-1][j+1]->bomb) {
                plansza->fields[i][j]->bombs_near += 1;
            }
        }
    }
}
void reveal_field(minefield *plansza, int x, int y) {
    if (x < 0 || x >= plansza->x || y < 0 || y >= plansza->y) return;
    if ( plansza->fields[x][y]->bomb ) return;
    if( plansza->fields[x][y]->flag) return;
    if ( !plansza->fields[x][y]->hidden ) return;
    plansza->fields[x][y]->hidden = 0;
    plansza->fields[x][y]->flag = 0;
    if ( plansza->fields[x][y]->bombs_near>0 ) return;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr != 0 || dc != 0) { // Pomijamy bieżące pole
                reveal_field(plansza, x + dr, y + dc);
            }
        }
    }
}
int check_field(minefield* plansza, int x, int y) {
    if ( x > plansza->x || y > plansza->y ) return 1; // out ouf bounds
    if (plansza->fields[x][y]->bomb) return 2; // odkryta bomba
    reveal_field(plansza, x, y);
    return 0;
}

void put_flag(minefield* plansza, int x ,int y){
    if ( x > plansza->x || y > plansza->y ) return; // out ouf bounds
    if( !plansza->fields[x][y]->hidden) return;
    plansza->fields[x][y]->flag = 1; 
}
void first_move(minefield* plansza,move* ruch) {
    round_result* wynik = user_move(plansza,ruch);
    if (wynik->rezultat == 2) {
        while (check_field(plansza,wynik->ruch_x, wynik->ruch_y) == 2) {
            int x = plansza->x;
            int y = plansza->y;
            int ile_bomb = plansza->ile_bomb;
            free(plansza);
            plansza = create_minefield(x, y,ile_bomb);
        }
    }
}
minefield* read_minefield_from_file(FILE* plik) {
    if (plik == NULL) {
        printf("BŁĄD ODCZYTU");
        exit(1);
    }
    int x, y;
    char line[BUFSIZE];
    minefield* plansza = malloc(sizeof(*plansza));
    fscanf(plik, "%d %d", &x, &y);
    while(fgetc(plik) == '\n');

    // inicjalizacja pamięci
    plansza->fields = malloc(x*sizeof(field));
    for (int i = 0; i < x; i++) {
        plansza->fields[i] = malloc(y * sizeof(field));
    } 
    plansza->x = x;
    plansza->y = y;


    for (int i = 0; i < x; i++) {
        fgets(line, BUFSIZE, plik);
        if (strcmp(line, "TABLE_END") == 0) break;
        for (int j = 0; j < y; j++) {
            field* new_field = malloc(sizeof(*new_field));
            new_field->flag = 0;
            new_field->hidden = 1;
            new_field->bombs_near = 0;
            if (line[j] == '0') {
                new_field->bomb = 0;
            } else {
                new_field->bomb = 1;
            }
            plansza->fields[i][j] = new_field;
        }
    }
    check_proximity(plansza);
    fgets(line, BUFSIZE, plik);
    return plansza;
}

            






