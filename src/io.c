#include <stdio.h>
#include "io.h"
#include <string.h>
#include <stdlib.h>

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
    }
    clear_buff();
    return diff;
}
round_result* user_move(minefield* plansza) {
    char input[MAX_BUFF]; // Bufor na dane wejściowe
    int x, y;        // Lokalne zmienne do przechowywania danych
    char place_mode; // tryb reveal lub flag
    round_result* round_result = malloc(sizeof(*round_result));
    while (1) {
        printf("Podaj dane w formacie (place_mode:char x:int y:int): ");
        fgets(input, sizeof(input), stdin); // Odczyt danych wejściowych

        // Parsowanie danych wejściowych
        if ((sscanf(input, "%c %d %d", &place_mode, &x, &y) == 3) && x>=0 && x<plansza->x && y>=0 && y<plansza->y && (place_mode == 'f' || place_mode == 'r') ) {
            break;
        }
        printf("Błąd: Niepoprawny format danych wejściowych. Spróbuj ponownie.\n");
        input[strcspn(input, "\n")] = '\0';
    }
    round_result->ruch_x = x;
    round_result->ruch_y = y;
    if(place_mode == 'f'){
        put_flag(plansza,x,y);
    }
    else if(place_mode == 'r'){
        round_result->rezultat = check_field(plansza, x, y);
    }
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
    }
}
custom_map* get_custom_map_data() {
    int x, y, ile_bomb;
    while (1) {
        printf("Podaj ilość wierszy: ");
        if (scanf("%d", &x) == 1) break;
    }
    while (1) {
        printf("Podaj ilość kolumn: ");
        if (scanf("%d", &y) == 1) break;
    }
    while (1) {
        printf("Podaj ilość bomb: ");
        if (scanf("%d", &ile_bomb) == 1 && ile_bomb<x*y) break;
        printf("Zły format/Za dużo bomb jak na taki rozmiar planszy\n");
    }
    custom_map* dane = malloc(sizeof(custom_map));
    dane->x = x;
    dane->y = y;
    dane->ile_bomb = ile_bomb;
    return dane;
}

        
