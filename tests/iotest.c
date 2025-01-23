#include "../src/io.h"
#include "../src/minefield.h"
#include <stdio.h>

void custom_board_test() {
    printf("Custom Map Test\n");
    custom_map* info = get_custom_map_data();
    minefield* plansza = create_minefield(info->x, info->y, info->ile_bomb);
    display_minefield(plansza);
}
int main() {
    minefield* plansza;
    plansza->x = 10;
    plansza->y = 10;
    printf("get_difficulty test\n");
    printf("poziom trudnosci: %d\n", get_difficulty());
    printf("get_name test\n");
    printf("nazwa: %s\n", get_player_name());
    printf("\n\n\n");
    custom_board_test();
    return 0;
}

