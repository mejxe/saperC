#include <stdio.h>
#include "io.h"
#include <string.h>
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
void user_move(minefield* plansza) {
    char input[MAX_BUFF]; // Bufor na dane wejściowe
    int x, y, f;     // Lokalne zmienne do przechowywania danych

    while (1) {
        printf("Podaj dane w formacie (x:int y:int f:int): ");
        fgets(input, sizeof(input), stdin); // Odczyt danych wejściowych

        // Parsowanie danych wejściowych
        if ((sscanf(input, "%d %d %d", &x, &y, &f) == 3) && x>=0 && x<plansza->x && y>=0 && y<plansza->y && f>=0 && f<2 ) {
            break;
        }
        printf("Błąd: Niepoprawny format danych wejściowych. Spróbuj ponownie.\n");
        input[strcspn(input, "\n")] = '\0';
    }
    check_field(plansza, x, y);
}

        
