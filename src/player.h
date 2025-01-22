#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_data {
         int  score;
         char* name; 
} player_data;

void save_player_data(player_data* data);
player_data* read_players_data(int* data_count);

#endif