#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_player_datas(player_data* datas,int data_count){
    if(data_count == 0) return;

    FILE* file = fopen("scores","w+");
    for (int i = 0; i < data_count; i++)
    {
        fprintf(file,"\n%s %d",datas[i].name,datas[i].score);
    }
    
    fclose(file);
}


player_data* read_players_data(int* data_count){
    
    FILE* file = fopen("scores","r");
    if(file == NULL) return NULL;
    char name[256];
    int score = 0;
    *data_count = 0;
    
    while(fscanf(file,"%s %d",name,&score) == 2){
        *data_count = *data_count + 1;
    }
    if(*data_count == 0) return NULL; 

    
    player_data* data = malloc(sizeof(player_data)*(*data_count + 1)); // +1 if need to add current player
  
    fseek(file,0,SEEK_SET); // reset fscanf


    for(int i =0 ; i< (*data_count); i++){
        fscanf(file,"%s %d",name,&score);
        data[i].score = score;
        data[i].name = (char*)malloc(256);
        strcpy(data[i].name,name);
        
    }
   fclose(file);
   return data;

}

void update_player_data(char* player_name,int score, player_data* player_datas,int* data_count){
    int playerIndex = -1;
    for (int  i = 0; i < *data_count; i++)
    {
        if(strcmp(player_datas[i].name,player_name) == 0){
            playerIndex = i;
        }
    }
    if(playerIndex > -1){
        if(player_datas[playerIndex].score < score){
        player_datas[playerIndex].score = score;
        }
    }else{
        (*data_count)++;
        player_datas[*data_count-1].score = score;
        player_datas[*data_count-1].name = malloc(256);
        strcpy(player_datas[*data_count-1].name,player_name);
    }

    
}

