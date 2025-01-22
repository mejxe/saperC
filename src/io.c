#include <stdio.h>
#include "io.h"
#include <string.h>
#include <stdlib.h>

#define MAX_BUFF 20
void clear_buff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
int get_difficulty() {
    int diff;
    while (1) {
        printf("Wybierz poziom trudnosci:\n-Latwy (1)\n-Średni (2)\n-Trudny(3)\n");
        if (scanf("%d", &diff) == 1 && diff >= 1 && diff <= 3) break;
    }
    clear_buff();
    return diff;
}
int user_move(minefield* plansza) {
    char input[MAX_BUFF]; // Bufor na dane wejściowe
    int x, y;        // Lokalne zmienne do przechowywania danych
    char place_mode; // tryb reveal lub flag
    int round_result = 0;
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
    if(place_mode == 'f'){
        put_flag(plansza,x,y);
    }
    else if(place_mode == 'r'){
        round_result = check_field(plansza, x, y);
    }
    return round_result;
}

char* get_player_name(){
    char* name = malloc(MAX_BUFF);
    while(1){
        printf("Podaj swoją nazwe\n");
        if(scanf("%s",name) == 1){
            return name;
            break;
        }
    }
}

        
