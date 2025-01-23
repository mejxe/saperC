#ifndef IO_H
#define IO_H

#include "minefield.h"
#include "player.h"

typedef struct {
    int ruch_x;
    int ruch_y;
    int rezultat;
} round_result;
typedef struct {
    int x;
    int y;
    int ile_bomb;
} custom_map;

round_result* user_move(minefield* plansza); 
int get_difficulty(); 
char* get_player_name();
custom_map* get_custom_map_data();

#endif
