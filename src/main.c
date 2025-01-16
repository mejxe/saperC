#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "scoreboard.h"
    
int main() {
    //int x, y, f; useless?
    minefield* plansza;
    int difficulty = get_difficulty();
    switch (difficulty) {
        case 1: {
        printf("Wybrano Łatwy\n");
        plansza = create_minefield(9, 9, 10);
        break;
                }
        case 2: {
        printf("Wybrano Średni\n");
        plansza = create_minefield(16, 16, 30);
        break;
                }
        case 3: {
        printf("Wybrano Trudny\n");
        plansza = create_minefield(16, 30, 99);
        break;
                }
    }
    
    while (1) // game loop
    {
        display_minefield(plansza);
        if(user_move(plansza) == 2){
                free(plansza);
                printf("\n=======================================\n\n Przegrałeś (odkryto bombe) :( \n\n");
                break;
        }
        else{
                display_scoreboard(plansza,&difficulty);
        }
        
    }
    
}
