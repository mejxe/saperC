#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "minefield.h"
#include "scoreboard.h"
#include "player.h"
#include <string.h>

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

    player_data data = (player_data) {.score = 0}; 
    data.name = malloc(20);
    strcpy(data.name,get_player_name());

    save_player_data(&data);

    int player_data_count = 0;
    player_data* player_datas = read_players_data(&player_data_count);

    for (int i = 0; i < player_data_count; i++){ 
        printf("%s: %d\n",player_datas[i].name,player_datas[i].score);
    }
    
    // first move
    display_minefield(plansza);
    first_move(plansza);
    
    while (1) // game loop
    {
        display_minefield(plansza);
        if(user_move(plansza)->rezultat == 2){
                free(plansza);
                printf("\n=======================================\n\n Przegrałeś (odkryto bombe) :( \n\n");
                break;
        }
        else{
                display_scoreboard(plansza,&difficulty);
        }
        
    }
    
}
