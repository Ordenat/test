#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Szachy {
private:
    char plansza[8][8];
     char aktualnyGracz; // B - biały, C - czarny

public:
    Szachy() {
        // Inicjalizacja generatora liczb losowych
        srand(time(0));

        // Inicjalizacja planszy - wypełnienie pustymi miejscami
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                plansza[i][j] = ' ';
            }
        }
        // Wypełnienie planszy losowymi pięcioma bierkami
        inicjalizujPlanszeLosowo();
        aktualnyGracz = 'B';
    }
     void zmienGracza() {
        // Zmiana gracza po każdym ruchu
        aktualnyGracz = (aktualnyGracz == 'B') ? 'C' : 'B';
    }
   void inicjalizujPlanszeLosowo() {
    // Bierki w szachach
    char bialeFigury[] = {'R', 'N', 'B', 'Q', 'K', 'P'};
    char czarneFigury[] = {'r', 'n', 'b', 'q', 'k', 'p'};

    // Mieszamy tablicę białych figur
    for (int i = 0; i < 6; i++) {
        int losowyIndeks = rand() % (6 - i) + i; // Losowanie od i do 5, z pominięciem już ustawionych figur
        swap(bialeFigury[i], bialeFigury[losowyIndeks]);
    }

    // Mieszamy tablicę czarnych figur
    for (int i = 0; i < 6; i++) {
        int losowyIndeks = rand() % (6 - i) + i; // Losowanie od i do 5, z pominięciem już ustawionych figur
        swap(czarneFigury[i], czarneFigury[losowyIndeks]);
    }

    // Ustawiamy jeden biały król
    int losowyWiersz = rand() % 8;
    int losowaKolumna = rand() % 8;
    while (plansza[losowyWiersz][losowaKolumna] != ' ') {
        losowyWiersz = rand() % 8;
        losowaKolumna = rand() % 8;
    }
    plansza[losowyWiersz][losowaKolumna] = 'K';

    // Ustawiamy jeden czarny król
    losowyWiersz = rand() % 8;
    losowaKolumna = rand() % 8;
    while (plansza[losowyWiersz][losowaKolumna] != ' ') {
        losowyWiersz = rand() % 8;
        losowaKolumna = rand() % 8;
    }
    plansza[losowyWiersz][losowaKolumna] = 'k';

    // Usuwamy króla z listy figur dla każdego koloru
    for (int i = 0; i < 6; i++) {
        if (bialeFigury[i] == 'K') {
            swap(bialeFigury[i], bialeFigury[5]); // Zamiana króla z ostatnią figurą
            break;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (czarneFigury[i] == 'k') {
            swap(czarneFigury[i], czarneFigury[5]); // Zamiana króla z ostatnią figurą
            break;
        }
    }

    // Wypełniamy planszę pozostałymi białymi figurami
    for (int i = 0; i < 5; i++) {
        losowyWiersz = rand() % 8;
        losowaKolumna = rand() % 8;
        while (plansza[losowyWiersz][losowaKolumna] != ' ') {
            losowyWiersz = rand() % 8;
            losowaKolumna = rand() % 8;
        }
        plansza[losowyWiersz][losowaKolumna] = bialeFigury[i];
    }

    // Wypełniamy planszę pozostałymi czarnymi figurami
    for (int i = 0; i < 5; i++) {
        losowyWiersz = rand() % 8;
        losowaKolumna = rand() % 8;
        while (plansza[losowyWiersz][losowaKolumna] != ' ') {
            losowyWiersz = rand() % 8;
            losowaKolumna = rand() % 8;
        }
        plansza[losowyWiersz][losowaKolumna] = czarneFigury[i];
    }
}
    void wyswietlPlansze() {
        cout << "    a   b   c   d   e   f   g   h" << endl;
        cout << "  +--------------------------------\n";
        for (int i = 0; i < 8; i++) {
            cout << 8 - i << " |";
            for (int j = 0; j < 8; j++) {
                cout << setw(2) << plansza[i][j] << " |";
               
            }
            cout << "\n  +--------------------------------\n";
        }
       
        cout << "Legenda:" << endl;
        cout << "r - wierza, n - skoczek, b - goniec, q - hetman, k - krol, p - pion" << endl;
        cout << "R, N, B, Q, K, P - białe odpowiedniki" << endl;
    }

   void wybierzPionek() {
        cout << "Aktualny gracz: " << ((aktualnyGracz == 'B') ? "Biały" : "Czarny") << endl;

        cout << "Podaj wspolrzedne bierki do wyboru (np. a2), lub wpisz 'koniec' aby zakończyć: ";
        string pozycja;
        cin >> pozycja;

        if (pozycja == "koniec") {
            cout << "Koniec gry. Do widzenia!" << endl;
            exit(0);  // lub inna odpowiednia akcja zakończenia programu
        }
    if (pozycja.length() != 2 || (pozycja[0] < 'a' || pozycja[0] > 'h') || (pozycja[1] < '1' || pozycja[1] > '8')) {
        cout << "Bledne wspolrzedne. Sprobuj ponownie." << endl;
        return;
    }

    int kolumna = pozycja[0] - 'a';
    int wiersz = '8' - pozycja[1];

    if (kolumna < 0 || kolumna >= 8 || wiersz < 0 || wiersz >= 8 || plansza[wiersz][kolumna] == ' ') {
        cout << "Brak pionka na podanej pozycji. Sprobuj ponownie." << endl;
        return;
    }

    char wybranaBierka = plansza[wiersz][kolumna];

    // Sprawdź, czy gracz wybiera białą bierkę, gdy jest jego kolej
    if ((aktualnyGracz == 'B' && (wybranaBierka >= 'a' && wybranaBierka <= 'z')) ||
        (aktualnyGracz == 'C' && (wybranaBierka >= 'A' && wybranaBierka <= 'Z'))) {
        cout << "Nie możesz wybrać bierki przeciwnego koloru. Sprobuj ponownie." << endl;
        return;
    }

    cout << "Wybrano pionka na pozycji " << pozycja << " (" << wybranaBierka << ")." << endl;

    // Sprawdź pola i bierki bite przez wybranego pionka
    sprawdzBicie(wiersz, kolumna);

    // Zmiana gracza po wykonaniu ruchu
    zmienGracza();
    

}

void sprawdzBicie(int wiersz, int kolumna) {
    // Sprawdź czy bierka to pionek
    if (plansza[wiersz][kolumna] == 'P' || plansza[wiersz][kolumna] == 'p') {
        // Sprawdź dla pionka
        sprawdzBiciePionka(wiersz, kolumna);
    } else if (plansza[wiersz][kolumna] == 'N' || plansza[wiersz][kolumna] == 'n') {
        // Sprawdź dla skoczka
        sprawdzBicieSkoczka(wiersz, kolumna);
    } else if (plansza[wiersz][kolumna] == 'R' || plansza[wiersz][kolumna] == 'r') {
        // Sprawdź dla wieży
        sprawdzBicieWiezy(wiersz, kolumna);
    } else if (plansza[wiersz][kolumna] == 'B' || plansza[wiersz][kolumna] == 'b') {
        // Sprawdź dla gońca
        sprawdzBicieGonca(wiersz, kolumna);
    } else if (plansza[wiersz][kolumna] == 'Q' || plansza[wiersz][kolumna] == 'q') {
        // Sprawdź dla hetmana
        sprawdzBicieHetmana(wiersz, kolumna);
    } else if (plansza[wiersz][kolumna] == 'K' || plansza[wiersz][kolumna] == 'k') {
        // Sprawdź dla króla
        sprawdzBicieKrola(wiersz, kolumna);
    } else {
        // Dla innych bierek (do zaimplementowania)
        cout << "Funkcja nie obsługuje jeszcze tej bierki." << endl;
    }
}
 void sprawdzBiciePionka(int wiersz, int kolumna) {
    char pionek = plansza[wiersz][kolumna];

    // Sprawdź czy to biały czy czarny pionek
    int kierunek = (pionek == 'P') ? -1 : 1;
    bool jestBicie = false; // Zmienna śledząca, czy jest jakiekolwiek bicie

    // Sprawdź możliwe ruchy dla pionka
    if (wiersz + kierunek >= 0 && wiersz + kierunek < 8) {
        // Sprawdź lewe pole
        if (kolumna - 1 >= 0) {
            char figuraLewo = plansza[wiersz + kierunek][kolumna - 1];
            if (figuraLewo != ' ' && ((pionek >= 'a' && pionek <= 'z' && figuraLewo >= 'A' && figuraLewo <= 'Z') || (pionek >= 'A' && pionek <= 'Z' && figuraLewo >= 'a' && figuraLewo <= 'z'))) {
                cout << "Bita figura na polu " << char(kolumna - 1 + 'a') << 8 - (wiersz + kierunek) << ": " << figuraLewo << endl;
                jestBicie = true;
            }
        }
        // Sprawdź prawe pole
        if (kolumna + 1 < 8) {
            char figuraPrawo = plansza[wiersz + kierunek][kolumna + 1];
            if (figuraPrawo != ' ' && ((pionek >= 'a' && pionek <= 'z' && figuraPrawo >= 'A' && figuraPrawo <= 'Z') || (pionek >= 'A' && pionek <= 'Z' && figuraPrawo >= 'a' && figuraPrawo <= 'z'))) {
                cout << "Bita figura na polu " << char(kolumna + 1 + 'a') << 8 - (wiersz + kierunek) << ": " << figuraPrawo << endl;
                jestBicie = true;
            }
        }
    }

    // Jeśli brak bić, wyświetl informację
    if (!jestBicie) {
        cout << "Brak możliwych bić dla wybranego pionka." << endl;
    }
}
void sprawdzBicieSkoczka(int wiersz, int kolumna) {
    char skoczek = plansza[wiersz][kolumna];
    bool jestBicie = false; // Zmienna śledząca, czy jest jakiekolwiek bicie

    // Sprawdź czy to biały czy czarny skoczek
    int kierunek = (skoczek == 'N') ? -1 : 1;

    // Możliwe ruchy skoczka w formie różnic w położeniu wiersza i kolumny
    int ruchy[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    // Sprawdź każdy możliwy ruch dla skoczka
    for (int i = 0; i < 8; ++i) {
        int nowyWiersz = wiersz + kierunek * ruchy[i][0];
        int nowaKolumna = kolumna + ruchy[i][1];

        // Sprawdź, czy nowe położenie mieści się na planszy
        if (nowyWiersz >= 0 && nowyWiersz < 8 && nowaKolumna >= 0 && nowaKolumna < 8) {
            // Sprawdź, czy na nowym położeniu znajduje się figura przeciwnego koloru
            char figuraNaPolu = plansza[nowyWiersz][nowaKolumna];
            if ((skoczek == 'N' && figuraNaPolu >= 'a' && figuraNaPolu <= 'z') || (skoczek == 'n' && figuraNaPolu >= 'A' && figuraNaPolu <= 'Z')) {
                cout << "Bita figura na polu " << char(nowaKolumna + 'a') << 8 - nowyWiersz << ": " << figuraNaPolu << endl;
                jestBicie = true;
            }
        }
    }

    // Jeśli brak bić, wyświetl informację
    if (!jestBicie) {
        cout << "Brak możliwych bić dla wybranego skoczka." << endl;
    }
}
void sprawdzBicieWiezy(int wiersz, int kolumna) {
    char wieza = plansza[wiersz][kolumna];
    bool jestBicie = false; // Zmienna śledząca, czy jest jakiekolwiek bicie

    // Sprawdź bicie w pionie (góra)
    for (int i = wiersz - 1; i >= 0; i--) {
        if (plansza[i][kolumna] != ' ') {
            if ((wieza == 'R' && plansza[i][kolumna] >= 'a' && plansza[i][kolumna] <= 'z') ||
                (wieza == 'r' && plansza[i][kolumna] >= 'A' && plansza[i][kolumna] <= 'Z')) {
                cout << "Bita figura na polu " << char(kolumna + 'a') << 8 - i << ": " << plansza[i][kolumna] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie w pionie (dół)
    for (int i = wiersz + 1; i < 8; i++) {
        if (plansza[i][kolumna] != ' ') {
            if ((wieza == 'R' && plansza[i][kolumna] >= 'a' && plansza[i][kolumna] <= 'z') ||
                (wieza == 'r' && plansza[i][kolumna] >= 'A' && plansza[i][kolumna] <= 'Z')) {
                cout << "Bita figura na polu " << char(kolumna + 'a') << 8 - i << ": " << plansza[i][kolumna] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie w poziomie (lewo)
    for (int j = kolumna - 1; j >= 0; j--) {
        if (plansza[wiersz][j] != ' ') {
            if ((wieza == 'R' && plansza[wiersz][j] >= 'a' && plansza[wiersz][j] <= 'z') ||
                (wieza == 'r' && plansza[wiersz][j] >= 'A' && plansza[wiersz][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - wiersz << ": " << plansza[wiersz][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie w poziomie (prawo)
    for (int j = kolumna + 1; j < 8; j++) {
        if (plansza[wiersz][j] != ' ') {
            if ((wieza == 'R' && plansza[wiersz][j] >= 'a' && plansza[wiersz][j] <= 'z') ||
                (wieza == 'r' && plansza[wiersz][j] >= 'A' && plansza[wiersz][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - wiersz << ": " << plansza[wiersz][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Jeśli brak bić, wyświetl informację
    if (!jestBicie) {
        cout << "Brak możliwych bić dla wybranej wieży." << endl;
    }
}
void sprawdzBicieGonca(int wiersz, int kolumna) {
    char goniec = plansza[wiersz][kolumna];
    bool jestBicie = false; // Zmienna śledząca, czy jest jakiekolwiek bicie

    // Sprawdź bicie po przekątnej w górę i w lewo
    for (int i = wiersz - 1, j = kolumna - 1; i >= 0 && j >= 0; i--, j--) {
        if (plansza[i][j] != ' ') {
            if ((goniec == 'B' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (goniec == 'b' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w górę i w prawo
    for (int i = wiersz - 1, j = kolumna + 1; i >= 0 && j < 8; i--, j++) {
        if (plansza[i][j] != ' ') {
            if ((goniec == 'B' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (goniec == 'b' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w dół i w lewo
    for (int i = wiersz + 1, j = kolumna - 1; i < 8 && j >= 0; i++, j--) {
        if (plansza[i][j] != ' ') {
            if ((goniec == 'B' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (goniec == 'b' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w dół i w prawo
    for (int i = wiersz + 1, j = kolumna + 1; i < 8 && j < 8; i++, j++) {
        if (plansza[i][j] != ' ') {
            if ((goniec == 'B' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (goniec == 'b' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
                jestBicie = true;
            }
            break;
        }
    }

    // Jeśli brak bić, wyświetl informację
    if (!jestBicie) {
        cout << "Brak możliwych bić dla wybranego gońca." << endl;
    }
}
void sprawdzBicieHetmana(int wiersz, int kolumna) {
    char hetman = plansza[wiersz][kolumna];

    // Sprawdź bicie po wierszu
    for (int j = 0; j < 8; j++) {
        if (j != kolumna && plansza[wiersz][j] != ' ') {
            if ((hetman == 'Q' && plansza[wiersz][j] >= 'a' && plansza[wiersz][j] <= 'z') ||
                (hetman == 'q' && plansza[wiersz][j] >= 'A' && plansza[wiersz][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - wiersz << ": " << plansza[wiersz][j] << endl;
            }
        }
    }

    // Sprawdź bicie po kolumnie
    for (int i = 0; i < 8; i++) {
        if (i != wiersz && plansza[i][kolumna] != ' ') {
            if ((hetman == 'Q' && plansza[i][kolumna] >= 'a' && plansza[i][kolumna] <= 'z') ||
                (hetman == 'q' && plansza[i][kolumna] >= 'A' && plansza[i][kolumna] <= 'Z')) {
                cout << "Bita figura na polu " << char(kolumna + 'a') << 8 - i << ": " << plansza[i][kolumna] << endl;
            }
        }
    }

    // Sprawdź bicie po przekątnej w górę i w lewo
    for (int i = wiersz - 1, j = kolumna - 1; i >= 0 && j >= 0; i--, j--) {
        if (plansza[i][j] != ' ') {
            if ((hetman == 'Q' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (hetman == 'q' && plansza[i][j] >= 'A' and plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w górę i w prawo
    for (int i = wiersz - 1, j = kolumna + 1; i >= 0 && j < 8; i--, j++) {
        if (plansza[i][j] != ' ') {
            if ((hetman == 'Q' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (hetman == 'q' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w dół i w lewo
    for (int i = wiersz + 1, j = kolumna - 1; i < 8 && j >= 0; i++, j--) {
        if (plansza[i][j] != ' ') {
            if ((hetman == 'Q' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (hetman == 'q' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
            }
            break;
        }
    }

    // Sprawdź bicie po przekątnej w dół i w prawo
    for (int i = wiersz + 1, j = kolumna + 1; i < 8 && j < 8; i++, j++) {
        if (plansza[i][j] != ' ') {
            if ((hetman == 'Q' && plansza[i][j] >= 'a' && plansza[i][j] <= 'z') ||
                (hetman == 'q' && plansza[i][j] >= 'A' && plansza[i][j] <= 'Z')) {
                cout << "Bita figura na polu " << char(j + 'a') << 8 - i << ": " << plansza[i][j] << endl;
            }
            break;
        }
    }
}
void sprawdzBicieKrola(int wiersz, int kolumna) {
    char krol = plansza[wiersz][kolumna];
    bool jestBicie = false; // Zmienna śledząca, czy jest jakiekolwiek bicie

    // Sprawdź oś X
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Pomijamy pole króla

            int nowyWiersz = wiersz + i;
            int nowaKolumna = kolumna + j;

            if (nowyWiersz >= 0 && nowyWiersz < 8 && nowaKolumna >= 0 && nowaKolumna < 8) {
                char figuraNaPolu = plansza[nowyWiersz][nowaKolumna];

                if ((krol == 'K' && figuraNaPolu >= 'a' && figuraNaPolu <= 'z') ||
                    (krol == 'k' && figuraNaPolu >= 'A' && figuraNaPolu <= 'Z')) {
                    cout << "Bita figura na polu " << char(nowaKolumna + 'a') << 8 - nowyWiersz << ": " << figuraNaPolu << endl;
                    jestBicie = true;
                }
            }
        }
    }

    // Jeśli brak bić, wyświetl informację
    if (!jestBicie) {
        cout << "Brak możliwych bić dla wybranego króla." << endl;
    }
}
};


int main() {
    Szachy szachy;
    szachy.wyswietlPlansze();

    while (true) {
        szachy.wybierzPionek();
    }

    return 0;
}



