#include "scoreboard.h"
#include <stdio.h>
#include "player.h"
#include <stdlib.h>

int get_score(minefield* plansza,int difficulty){
     int score = 0;
    for ( int x = 0; x < plansza->x; x++)
    {
        for (int y = 0; y < plansza->y; y++)
        {
            if(!plansza->fields[x][y]->hidden){
                score++;
            }
        }
        
    }
    score *= difficulty == 4? 1 : difficulty;
    return score;
}

void display_current_score(minefield* plansza,int difficulty){
   

    printf("\nWynik: %d  Poziom trudności: %d\n",get_score(plansza,difficulty),difficulty );
    
    
}

int compare_score(const void* arg1, const void* arg2){
    player_data* player1 = (player_data*)arg1;
    player_data* player2 = (player_data*)arg2;
    return (player2->score - player1->score);
}

void display_whole_scoreboard(player_data* player_datas,int count){
    qsort(player_datas,count,sizeof(player_data),compare_score);
    printf("\n🔥 𝐓𝐎𝐏 𝐆𝐑𝐀𝐂𝐙𝐄 🔥\n");
    printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    for (int i = 0; i < 5; i++)
    {
        if(i >= count){
            printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
            return;
        }

        printf("┇ %d. %s: %d \n",i+1,player_datas[i].name,player_datas[i].score);
    }
    printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");

}


