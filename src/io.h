#ifndef IO_H
#define IO_H

#include "minefield.h"
#include "player.h"

typedef struct {
    int ruch_x;
    int ruch_y;
    int rezultat;
} round_result;

round_result* user_move(minefield* plansza); 
int get_difficulty(); 
char* get_player_name();

#endif
