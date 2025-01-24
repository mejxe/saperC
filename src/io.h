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


round_result* user_move(minefield* plansza,move* ruch);
int get_difficulty(); 
char* get_player_name();
custom_map* get_custom_map_data();
void save_minefield(minefield* plansza,char* player_name,move* moves, int move_count, int difficulty);
int* display_move_from_file(minefield* plansza, FILE* plik);
void print_summary(minefield* plansza,int good_moves, int difficulty);
#endif
