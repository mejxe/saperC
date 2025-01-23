#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "minefield.h"
#include "scoreboard.h"
#include "player.h"
#include <string.h>

#define CLRSCR() printf("\e[1;1H\e[2J");

int main() {
    minefield* plansza;
    int difficulty = get_difficulty();
    switch (difficulty) {
        case 1: {
                    printf("Wybrano Łatwy\n");
                    plansza = create_minefield(9, 9, 10);
                    break;
                }
        case 2: {
                    printf("Wybrano Średni\n");
                    plansza = create_minefield(16, 16, 30);
                    break;
                }
        case 3: {
                    printf("Wybrano Trudny\n");
                    plansza = create_minefield(16, 30, 99);
                    break;
                }
        case 4: {
                    printf("Wybrano Własną mapę\n");
                    custom_map* result = get_custom_map_data();
                    plansza = create_minefield(result->x, result->y, result->ile_bomb);
                    break;
                }

    }

    


    int player_data_count = 0;
    player_data* player_datas;
   
    
    // first move
    display_minefield(plansza);
    first_move(plansza);
    
    while (1) // game loop
    {
        CLRSCR();
        printf("\n🐀");
        display_minefield(plansza);
        if(user_move(plansza)->rezultat == 2){
                
                player_datas = read_players_data(&player_data_count);
                if(player_datas == NULL){
                    player_datas = malloc(sizeof(player_data)); // allocate 1 struct for current player;
                }
                player_data current_player = (player_data) {.score = 0}; 
                current_player.name = malloc(256);
                printf("n=======================================\n\n Przegrałeś (odkryto bombe) :( \n\n");
                strcpy(current_player.name,get_player_name());
                current_player.score =  get_score(plansza,difficulty);
                update_player_data(current_player.name,current_player.score,player_datas,&player_data_count);
                display_whole_scoreboard(player_datas,player_data_count);
                save_player_datas(player_datas,player_data_count);

                free(plansza);
                break;
        }
        else{
                display_current_score(plansza,difficulty);
        }


        
    }
    \
}
