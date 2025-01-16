#include "scoreboard.h"
#include <stdio.h>
void display_scoreboard(minefield* plansza,int* difficulty){
    int score = 0;
    for ( int x = 0; x < plansza->x; x++)
    {
        for (int y = 0; y < plansza->y; y++)
        {
            if(!plansza->fields[x][y]->hidden){
                score++;
            }
        }
        
    }
    score *= *difficulty;

    printf("\nWynik: %d  Poziom trudności: %d\n",score,*difficulty );

    
}