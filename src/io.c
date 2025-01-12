#include <stdio.h>
#include "io.h"
#define MAX_BUFF 20
int get_difficulty() {
    int diff;
    while (1) {
        printf("Wybierz poziom trudnosci:\n-Latwy (1)\n-Średni (2)\n-Trudny(3)");
        if (scanf("%d", &diff) != 0 && diff <= 1 && diff <= 3) break;
    }
    return diff;
}
void user_move(minefield* plansza) {
    char input[MAX_BUFF]; // Bufor na dane wejściowe
    int x, y, f;     // Lokalne zmienne do przechowywania danych

    while (1) {
        printf("Podaj dane w formacie (x:int y:int f:int): ");
        fgets(input, sizeof(input), stdin); // Odczyt danych wejściowych

        // Parsowanie danych wejściowych
        if (sscanf(input, "%d %d %d", &x, &y, &f) == 3) {
            break;
        } else {
            printf("Błąd: Niepoprawny format danych wejściowych. Spróbuj ponownie.\n");
        }
        printf("%d %d %d ",x,y,f);
    }
    check_field(plansza, x, y);
}

        
