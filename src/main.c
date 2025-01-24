#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "minefield.h"
#include "scoreboard.h"
#include "player.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define CLRSCR() printf("\033[1;1H\033[2J");

int main(int argc, char** argv) {

    int c;
    char filename[64];
    int mode = 0;
    while((c = getopt(argc,argv,"f:")) != -1){
        
        switch (c){
        case 'f':
            strcpy(filename,optarg);
            mode = 1;
            break;
        case '?':
            printf("Nieznany argument: %s\n",optarg);
            break;
        default:
            break;
        }

        
    }

if(mode == 1){
    FILE* file = fopen(filename,"r");
    if(file == NULL) {
        printf("Nie udało się otworzyć pliku %s \n",filename);
        mode = 0;
    }
    else{
        printf("Pomyślnie otworzono plik %s \n",filename);
    }

}

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
    player_data current_player = (player_data) {.score = 0}; 
    
    move* moves = malloc(sizeof(move) * 100); // max 100 moves
    int current_move = 0;

    // first move
    display_minefield(plansza);
    current_move++;
    first_move(plansza,&moves[current_move]);
    minefield starting_minefield = *plansza; // save in memory if player wants to save to file

    

    while (1) // game loop
    {
        CLRSCR();
        display_minefield(plansza);
        display_current_score(plansza,difficulty);
        if(user_move(plansza,&moves[current_move])->rezultat == 2){
                
                player_datas = read_players_data(&player_data_count);
                if(player_datas == NULL){
                    player_datas = malloc(sizeof(player_data)); // allocate 1 struct for current player;
                }
            
                current_player.name = malloc(256);
                printf("=======================================\n\n Przegrałeś (odkryto bombe) :( \n\n");
                strcpy(current_player.name,get_player_name());
                current_player.score =  get_score(plansza,difficulty);
                update_player_data(current_player.name,current_player.score,player_datas,&player_data_count);
                display_whole_scoreboard(player_datas,player_data_count);
                save_player_datas(player_datas,player_data_count);

                free(plansza);
                break;
        }
        else{
                if(get_score(plansza,difficulty)/(difficulty%3) == plansza->x * plansza->y - plansza->ile_bomb){
        
                    player_datas = read_players_data(&player_data_count);
                    if(player_datas == NULL){
                        player_datas = malloc(sizeof(player_data)); // allocate 1 struct for current player;
                    }
        
                    current_player.name = malloc(256);
                    printf("=======================================\n\n Wygrałeś użytkowniku! \n\n");
                    strcpy(current_player.name,get_player_name());
                    current_player.score =  get_score(plansza,difficulty);
                    update_player_data(current_player.name,current_player.score,player_datas,&player_data_count);
                    display_whole_scoreboard(player_datas,player_data_count);
                    save_player_datas(player_datas,player_data_count);
                    free(plansza);
                    break;
                }
        }

           current_move++;
        
    }
    char response[20];
    printf("\nCzy chcesz zapisać tą rozgrywkę? TAK / NIE\n");
    scanf("%s", response);
    
    for (int i = 0; i < strlen(response); i++)
    {
        response[i] = tolower(response[i]);  // convert response to lower case
    }
    
    if(strcmp(response,"tak") == 0){
        printf("Zapisuje...\n");
        save_minefield(&starting_minefield,current_player.name,moves,current_move);
    }

}
