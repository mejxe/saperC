
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "minefield.h"
#include "player.h"
void display_current_score(minefield* plansza,int difficulty);
void display_whole_scoreboard(player_data* player_datas,int count);
int get_score(minefield* plansza,int difficulty);

#endif