#ifndef MINEFIELD_H
#define MINEFIELD_H



typedef struct {
    int hidden; // 0|1 - false|true
    int bombs_near; // liczba bomb
    int bomb; // 0|1 
    int flag; // 0|1
} field;

typedef struct {
    int x; // liczba kolumn
    int y; // liczba wierszy
    field *** fields; // tablica dwuwymiarowa zawierajaca pola
    int ile_bomb;
} minefield;

typedef struct {
    int mode; // 0 = reveal  1 = flag
    int x;
    int y;
} move;

minefield* create_minefield(int x, int y, int ile_bomb);
void display_minefield(minefield* plansza);
void check_proximity(minefield* plansza);
void reveal_field(minefield* plansza, int x, int y);
int check_field(minefield* plansza, int x, int y);
void put_flag(minefield* plansza, int x ,int y);
void first_move(minefield* plansza,move* ruch); 
#endif
