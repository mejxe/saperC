#include <stdio.h>
#include <stdlib.h>
#include "io.h"
    
int main() {
    int x, y, f;
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
    
    
    display_minefield(plansza);
    user_move(plansza);
    display_minefield(plansza);
    free(plansza);
}
