
typedef struct {
    int hidden; // 0|1 - false|true
    int bombs_near; // liczba bomb
    int bomb; // 0|1 
    int flag; // 0|1
} field;

typedef struct {
    int x; // liczba kolumn
    int y; // liczba wierszy
    field ** fields; // tablica dwuwymiarowa zawierajaca pola
} minefield;

minefield* create_minefield(int x, int y, int ile_bomb);
void display_minefield(minefield* plansza);
