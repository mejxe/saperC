#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_data {
         int  score;
         char* name; 
} player_data;

void save_player_data(player_data* data);
void read_players_data(player_data** data, int* data_count);

#endif