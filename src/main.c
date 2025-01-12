#include <stdio.h>
#include <stdlib.h>
#include "io.h"
    
int main() {
    int x, y, f;
    minefield* plansza = create_minefield(5, 5, 3);
    display_minefield(plansza);
    user_move(plansza);
    display_minefield(plansza);
    free(plansza);
}
