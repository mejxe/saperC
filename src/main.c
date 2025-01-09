#include <stdio.h>
#include <stdlib.h>
#include "minefield.h"
    
int main() {
    printf("/// SAPER /// \n");
    minefield* plansza = create_minefield(5, 5, 3);
    display_minefield(plansza);
    free(plansza);
}
