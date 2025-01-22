#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_player_data(player_data* data){
    FILE* file = fopen("scores","ab+");
    fprintf(file,"\n%s %d",data->name,data->score);
    fclose(file);
}


player_data* read_players_data(int* data_count){
    
    FILE* file = fopen("scores","r");
    if(file == NULL) return NULL;
    char name[256];
    int score = 0;
    *data_count = 0;
    
    while(fscanf(file,"%s %d",name,&score) == 2){
        if(name == NULL) continue;
        *data_count = *data_count + 1;
    }
    if(*data_count == 0) return NULL; 

    
    printf("Data count: %d\n",*data_count);
    player_data* data = malloc(sizeof(player_data)*(*data_count));
  
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

