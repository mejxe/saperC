#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_data {
         int  score;
         char* name; 
} player_data;

void save_player_datas(player_data* datas,int data_count);
player_data* read_players_data(int* data_count);
void update_player_data(char* player_name,int score, player_data* player_datas,int* data_count);


#endif