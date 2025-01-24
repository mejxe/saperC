#include <stdio.h>
#include "io.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "minefield.h"

#define MAX_BUFF 32

void clear_buff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
int get_difficulty() {
    int diff;
    while (1) {
        printf("Wybierz poziom trudnosci:\n-Latwy (1)\n-Średni (2)\n-Trudny(3)\n-Własny(4)\n");
        if (scanf("%d", &diff) == 1 && diff >= 1 && diff <= 4) break;

    clear_buff();
    }
    clear_buff();
    return diff;
}
round_result* user_move(minefield* plansza,move* ruch) {
    char input[MAX_BUFF]; // Bufor na dane wejściowe
    int x, y;        // Lokalne zmienne do przechowywania danych
    char place_mode; // tryb reveal lub flag
    round_result* round_result = malloc(sizeof(*round_result));
    while (1) {
        printf("Podaj dane w formacie (place_mode:char x:int y:int): ");
        fgets(input, sizeof(input), stdin); // Odczyt danych wejściowych

        // Parsowanie danych wejściowych
        if ((sscanf(input, "%c %d %d", &place_mode, &y, &x) == 3) && x>=0 && x<plansza->x && y>=0 && y<plansza->y && (place_mode == 'f' || place_mode == 'r') ) {
            break;
        }
        printf("Błąd: Niepoprawny format danych wejściowych. Spróbuj ponownie.\n");
        input[strcspn(input, "\n")] = '\0';
    }
    round_result->ruch_x = x;
    round_result->ruch_y = y;
    if(place_mode == 'f'){
        ruch->mode = 1;
        put_flag(plansza,x,y);
    }
    else if(place_mode == 'r'){
        ruch->mode = 0;
        round_result->rezultat = check_field(plansza, x, y);
    }
    ruch->x = x;
    ruch->y = y;
    return round_result;
}

char* get_player_name(){
    char* name = malloc(MAX_BUFF);
    while(1){
        printf("Podaj swoją nazwe\n");
        if(scanf("%s",name) == 1){
            clear_buff();
            return name;
            break;
        }
        clear_buff();
    }
}
custom_map* get_custom_map_data() {
    int x, y, ile_bomb;
    while (1) {
        printf("Podaj ilość wierszy: ");
        if (scanf("%d", &x) == 1) {
            break;
        }
        clear_buff();
    }
    while (1) {
        printf("Podaj ilość kolumn: ");
        if (scanf("%d", &y) == 1) {
            break;
        }
        clear_buff();
    }
    while (1) {
        printf("Podaj ilość bomb: ");
        if (scanf("%d", &ile_bomb) == 1 && ile_bomb<x*y) {
            clear_buff();
            break;
        }
        printf("Zły format lub za dużo bomb jak na taki rozmiar planszy.\n");
        clear_buff();
    }
    custom_map* dane = malloc(sizeof(custom_map));
    dane->x = x;
    dane->y = y;
    dane->ile_bomb = ile_bomb;
    return dane;
} 

void save_minefield(minefield* plansza,char* player_name, move* moves,int move_count){
    srand(time(NULL));
    char random[8];
    sprintf(random,"%d",rand() % (1000-0) + 0); //range 0 - 1000
    char filebase[] = "zapis_";

    char* filename = malloc(strlen(filebase) + strlen(player_name) + strlen(random) + 1 );
    strcpy(filename,filebase);
    strcat(filename,player_name);
    strcat(filename,random);
    printf("Nazwa pliku: %s\n",filename);

    FILE* file = fopen(filename,"w+");
    for (int x = 0; x < plansza->x; x++)
    {
        for (int y = 0; y < plansza->y; y++)
        {
            if(plansza->fields[x][y]->bomb == 1){
                 fprintf(file,"%c",'B');
            }
            else {
                 fprintf(file,"%c",'0');
            }
        }
         fprintf(file,"\n");
    }
    fprintf(file,"TABLE_END\n");
    fprintf(file, "\n");
    for (int i = 0; i < move_count; i++)
    {
        fprintf(file,"%d %d %d \n",moves[i].x, moves[i].y,moves[i].mode);

    }
    
    
   



    fclose(file);

}


        
