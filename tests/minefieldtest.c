#include "../src/minefield.h"

int main() {
    minefield* plansza = create_minefield(10, 10, 5);
    display_minefield(plansza); // powinno wyświetlać plansze 10x10
    check_field(plansza, 5, 5); // powinno odkryć
    return 0;
}

