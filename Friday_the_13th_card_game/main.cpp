#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;
int i_am, active_player, active_round;
int n, k, g, gv, o, e, r; //liczba graczy, kociolkow, zielonych, wartosci ziel, innych, explosion, rundy
//int equals[100]; //wartosc kolejnych niezielonych kart
char draft[50];
int end_ofround = 0;
int resistance[20][6];
int resistance2[20][7];
int ilosckart[20];

//do generowania gry
struct cards {
        char color[15];
        int value;
};
//do generowania gry
int GiveRandom(int a) {
        return  (rand() % a);

}

//struktury kart hand, deck, pile
struct hand_cards {
        int owner;
        char color[15];
        int col;
        int value;
};

struct deck_cards {
        int owner;
        char color[15];
        int col;
        int value;
};

struct pile_cards {
        int owner;
        char color[15];
        int col;
        int value;
};

struct P
{
        int b; //kolor
        int c; //wartosc
};

int count(char count[30]) { //szukanie liczby w tablibcy
        int a = 0;
        for (int i = 0; i < 30; i++) {
                if (((count[i] > 47) && (count[i] < 58)) && ((count[i + 1] <= 47) || (count[i + 1] >= 58)) && ((count[i + 2] <= 47) || (count[i + 2] >= 58))) {
                        a = (count[i] - 48);
                        break;
                }
                if (((count[i] > 47) && (count[i] < 58)) && ((count[i + 1] > 47) && (count[i + 1] < 58)) && ((count[i + 2] <= 47) || (count[i + 2] >= 58))) {
                        a = (10 * (count[i] - 48) + (count[i + 1] - 48));
                        break;
                }
                if (((count[i] > 47) && (count[i] < 58)) && ((count[i + 1] > 47) && (count[i + 1] < 58)) && ((count[i + 2] > 47) && (count[i + 3] < 58))) {
                        a = (100 * (count[i] - 48) + 10 * (count[i + 1] - 48) + (count[i + 2] - 48));
                        break;
                }
        }
        return a;
}

P find() { //szukanie kolorow
        int a;
        int b;
        int c;
        int br = 0;
        for (int i = 0; i < 45; i++) {
                if (((draft[i] > 47) && (draft[i] < 58)) && ((draft[i + 1] <= 47) || (draft[i + 1] >= 58))) {
                        a = (draft[i] - 48);
                        break;
                }
                if (((draft[i] > 47) && (draft[i] < 58)) && ((draft[i + 1] > 47) && (draft[i + 1] < 58))) {
                        a = (10 * (draft[i] - 48) + (draft[i + 1] - 48));
                        break;
                }
        }
        for (int i = 0; i < 45; i++) {
                if ((draft[i] == 'b') && (draft[i + 1] == 'l') && (draft[i + 2] == 'u') && (draft[i + 3] == 'e')) {
                        b = 0;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'r') && (draft[i + 1] == 'e') && (draft[i + 2] == 'd')) {
                        b = 1;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'v') && (draft[i + 1] == 'i') && (draft[i + 2] == 'o') && (draft[i + 3] == 'l') && (draft[i + 4] == 'e') && (draft[i + 5] == 't')) {
                        b = 2;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'w') && (draft[i + 1] == 'h') && (draft[i + 2] == 'i') && (draft[i + 3] == 't') && (draft[i + 4] == 'e')) {
                        b = 3;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'y') && (draft[i + 1] == 'e') && (draft[i + 2] == 'l') && (draft[i + 3] == 'l') && (draft[i + 4] == 'o') && (draft[i + 5] == 'w')) {
                        b = 4;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'b') && (draft[i + 1] == 'l') && (draft[i + 2] == 'a') && (draft[i + 3] == 'c') && (draft[i + 4] == 'k')) {
                        b = 5;
                        c = a;
                        br = 1;
                        break;
                }
                if ((draft[i] == 'g') && (draft[i + 1] == 'r') && (draft[i + 2] == 'e') && (draft[i + 3] == 'e') && (draft[i + 4] == 'n')) {
                        b = 6;
                        c = a;
                        br = 1;
                        break;
                }
        }
        if (br == 0) {
                b = -1;
                c = -1;
        }
        return { b, c };
}


int read_draft(int i) { //szukanie liczby w tablicy
        int a = 0;
        for (i; i < 45; i++) {
                if (((draft[i] > 47) && (draft[i] < 58)) && ((draft[i + 1] <= 47) || (draft[i + 1] >= 58))) {
                        a = (draft[i] - 48);
                        break;
                }
                if (((draft[i] > 47) && (draft[i] < 58)) && ((draft[i + 1] > 47) && (draft[i + 1] < 58))) {
                        a = (10 * (draft[i] - 48) + (draft[i + 1] - 48));
                        break;
                }
                if (((draft[i] > 47) && (draft[i] < 58)) && ((draft[i + 1] > 47) && (draft[i + 1] < 58)) && ((draft[i + 2] > 47) && (draft[i + 3] < 58))) {
                        a = (100 * (draft[i] - 48) + 10 * (draft[i + 1] - 48) + (draft[i + 2] - 48));
                        break;
                }
        }
        for (i = 0; i < 50; i++) {
                draft[i] = NULL;
        }
        return a;
}

int main() { //gracz
        cout << "Ktorym jestem graczem" << endl;
        cin >> i_am;
        hand_cards hand[300];
        deck_cards deck[300];
        pile_cards pile[300];
        FILE* pFile;
        for (int f = 1; f > 0; f++) {
                pFile = fopen("file.txt", "r");
                fgets(draft, 50, pFile);
                active_player = read_draft(0);
                if (active_player == i_am) { // jezeli gram to wczytuje cały plik
                        fgets(draft, 50, pFile);
                        active_round = read_draft(0);
                        fgets(draft, 50, pFile);
                        n = read_draft(0);
                        fgets(draft, 50, pFile);
                        r = read_draft(0);
                        fgets(draft, 50, pFile);
                        e = read_draft(0);
                        fgets(draft, 50, pFile);
                        int j = 0;
                        int g = 0;
                        for (int i = 1; i <= n; i++) {
                                for (int z = 0; z < 100; z++) {
                                        fgets(draft, 50, pFile);
                                        P p = find();
                                        if (p.c == -1) {
                                                break;
                                        }
                                        else {
                                                if (p.b == 0) {
                                                        hand[j] = {
                                                                i,
                                                                "blue",
                                                                0,
                                                                p.c,
                                                        };
                                                }
                                                if (p.b == 1) {
                                                        hand[j] = {
                                                                i,
                                                                "red",
                                                                1,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 2) {
                                                        hand[j] = {
                                                                i,
                                                                "violet",
                                                                2,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 3) {
                                                        hand[j] = {
                                                                i,
                                                                "white",
                                                                3,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 4) {
                                                        hand[j] = {
                                                                i,
                                                                "yellow",
                                                                4,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 5) {
                                                        hand[j] = {
                                                                i,
                                                                "black",
                                                                5,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 6) {
                                                        hand[j] = {
                                                                i,
                                                                "green",
                                                                6,
                                                                p.c
                                                        };
                                                }
                                                j++;
                                                for (int m = 0; m < 50; m++) {
                                                        draft[m] = NULL;
                                                }
                                        }
                                }
                                for (int z = 0; z < 100; z++) {
                                        fgets(draft, 50, pFile);
                                        P p = find();
                                        if (p.c == -1) {
                                                break;
                                        }
                                        else {
                                                if (p.b == 0) {
                                                        deck[g] = {
                                                                i,
                                                                "blue",
                                                                0,
                                                                p.c,
                                                        };
                                                        resistance[i][0]++;
                                                }
                                                if (p.b == 1) {
                                                        deck[g] = {
                                                                i,
                                                                "red",
                                                                1,
                                                                p.c
                                                        };
                                                        resistance[i][1]++;
                                                }
                                                if (p.b == 2) {
                                                        deck[g] = {
                                                                i,
                                                                "violet",
                                                                2,
                                                                p.c
                                                        };
                                                        resistance[i][2]++;
                                                }
                                                if (p.b == 3) {
                                                        deck[g] = {
                                                                i,
                                                                "white",
                                                                3,
                                                                p.c
                                                        };
                                                        resistance[i][3]++;
                                                }
                                                if (p.b == 4) {
                                                        deck[g] = {
                                                                i,
                                                                "yellow",
                                                                4,
                                                                p.c
                                                        };
                                                        resistance[i][4]++;
                                                }
                                                if (p.b == 5) {
                                                        deck[g] = {
                                                                i,
                                                                "black",
                                                                5,
                                                                p.c
                                                        };
                                                        resistance[i][5]++;
                                                }
                                                if (p.b == 6) {
                                                        deck[g] = {
                                                                i,
                                                                "green",
                                                                6,
                                                                p.c
                                                        };
                                                }
                                                g++;
                                                for (int m = 0; m < 50; m++) {
                                                        draft[m] = NULL;
                                                }
                                        }
                                }
                        }
                        j = 0;
                        int stosy = 0;
                        int cdx = 0;
                        for (int i = 1; i <= 6; i++) {
                                if (draft[0] == '0') {
                                        break;
                                }
                                stosy++;
                                for (int z = 0; z < 100; z++) {
                                        fgets(draft, 50, pFile);
                                        P p = find();
                                        if (p.c == -1) {
                                                break;
                                        }
                                        else {
                                                if (p.b == 0) {
                                                        pile[j] = {
                                                                i,
                                                                "blue",
                                                                0,
                                                                p.c,
                                                        };
                                                }
                                                if (p.b == 1) {
                                                        pile[j] = {
                                                                i,
                                                                "red",
                                                                1,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 2) {
                                                        pile[j] = {
                                                                i,
                                                                "violet",
                                                                2,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 3) {
                                                        pile[j] = {
                                                                i,
                                                                "white",
                                                                3,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 4) {
                                                        pile[j] = {
                                                                i,
                                                                "yellow",
                                                                4,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 5) {
                                                        pile[j] = {
                                                                i,
                                                                "black",
                                                                5,
                                                                p.c
                                                        };
                                                }
                                                if (p.b == 6) {
                                                        pile[j] = {
                                                                i,
                                                                "green",
                                                                6,
                                                                p.c
                                                        };
                                                }
                                                j++;
                                        }
                                }
                        }// koniec wczytywania danych z pliku
                        fclose(pFile);
                        //sprawdzenie czy ilosc kart na rekach się zgadza
                        int y = 0;
                        for (int t = 1; t <= n; t++) {
                                while (hand[y].owner == t) {
                                        ilosckart[t]++;
                                        y++;
                                }
                        }
                        for (int t = 2; t <= n; t++) {
                                if (((ilosckart[1] - ilosckart[t]) > 1) || ((ilosckart[1] - ilosckart[t]) < -1)) {
                                        cout << "The number of players cards on hand is wrong" << endl;
                                        return 0;
                                }
                        }
                        y = 0;
                        gv = 0;
                        while (hand[y].owner != 0) {
                                if (hand[y].col == 6) {
                                        if ((gv != 0) && (hand[y].value != gv)) {
                                                cout << "The value of green cards is wrong" << endl;
                                                return 0;
                                        }
                                        else (gv = hand[y].value);
                                }
                                y++;
                        }
                        y = 0;
                        while (deck[y].owner != 0) {
                                if (deck[y].col == 6) {
                                        if ((gv != 0) && (deck[y].value != gv)) {
                                                cout << "The value of green cards is wrong" << endl;
                                                return 0;
                                        }
                                        else (gv = deck[y].value);
                                }
                                y++;
                        }
                        y = 0;
                        while (pile[y].owner != 0) {
                                if (pile[y].col == 6) {
                                        if ((gv != 0) && (pile[y].value != gv)) {
                                                cout << "The value of green cards is wrong" << endl;
                                                return 0;
                                        }
                                        else (gv = pile[y].value);
                                }
                                y++;
                        }
                        // przeliczanie kart i wykonanie całego ruchu
                        int boom = 0;
                        int chosen_pile = 0, chosen_card; //stos i karta używane w trakcie posuniecia gracza
                        int o = 0, p, z = 0;
                        int done = 0;
                        int b;
                        for (int i = 1; i <= n; i++) {
                                if (i == active_player) {
                                        for (int r = 1; r <= stosy; r++) {
                                                if (done == 0) {
                                                        b = 0;
                                                        int check = 1;
                                                        while (hand[b].owner != i) {
                                                                b++;
                                                                if (hand[b].owner == i) {
                                                                        int f = (b + 1);
                                                                        while (hand[f].owner == i) {
                                                                                if (hand[b].value > hand[f].value) {
                                                                                        b = f;
                                                                                }
                                                                                f++;
                                                                        }
                                                                }
                                                                if (hand[b].owner == 0) {
                                                                        break;
                                                                }
                                                        }
                                                        p = b;
                                                        int br = 0;
                                                        while (pile[o].owner == r) {
                                                                if ((pile[o].col != hand[p].col) && (pile[o].col != 6) && (hand[p].col != 6)) {
                                                                        check = 0;
                                                                        br = 1;
                                                                }
                                                                else if (br == 0) {
                                                                        check = 1;
                                                                }
                                                                z = o;
                                                                o++;
                                                        }
                                                        if (done == 0) {
                                                                if (check == 1) {
                                                                        int suma = 0;
                                                                        while (pile[z].owner == r) {
                                                                                suma += pile[z].value;
                                                                                z--;
                                                                        }
                                                                        suma += hand[p].value;
                                                                        chosen_card = p;
                                                                        chosen_pile = r;
                                                                        if (suma > e) {
                                                                                boom = 1;
                                                                        }
                                                                        done = 1;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        if (chosen_pile == 0) {
                                end_ofround = 1;
                        }
                        if (end_ofround == 1) {
                                if (active_round == r) {
                                        int sum[21];
                                        pFile = fopen("file2.txt", "w+");
                                        for (int i = 1; i <= r; i++) {
                                                for (int j = 1; j <= n; j++) {
                                                        fgets(draft, 50, pFile);
                                                        sum[j] += read_draft(15);
                                                }
                                        }
                                        fprintf(pFile, "Koniec rozgrywki\n");
                                        for (int j = 1; j <= n; j++) {
                                                fprintf(pFile, "Wynik gracza %d = %d\n", j, sum[j]);
                                        }
                                        fclose(pFile);
                                }
                                else {
                                        pFile = fopen("file2.txt", "w+");
                                        for (int i = 0; i < 6; i++) {
                                                int br = 0;
                                                for (int j = 1; j <= n; j++) {
                                                        if (resistance[j][i] != NULL) {
                                                                br = 0;
                                                                break;
                                                        }
                                                        else {
                                                                br = 1;
                                                        }
                                                }
                                                if (br == 1) {
                                                        break;
                                                }
                                                int m = 1;
                                                for (int j = 2; j <= n; j++) {
                                                        if (resistance[m][i] < resistance[j][i]) {
                                                                m = j;
                                                        }
                                                }
                                                for (int j = 1; j <= n; j++) {
                                                        if (m == j) {
                                                                j++;
                                                        }
                                                        if (resistance[m][i] == resistance[j][i]) {
                                                                m = 0;
                                                                break;
                                                        }
                                                }
                                                if (resistance[m][i] != 0) {
                                                        for (int z = 0; z < 100; z++) {
                                                                if (deck[z].col == i) {
                                                                        resistance2[m][i] = 1;
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                        int j = 0;
                                        for (int i = 1; i <= n; i++) {
                                                int sum = 0;
                                                while (deck[j].owner == i) {
                                                        if (resistance2[i][deck[j].col] == 1) {
                                                                sum += 0;
                                                        }
                                                        else if (deck[j].col == 6) {
                                                                sum += 2;
                                                        }
                                                        else {
                                                                sum += 1;
                                                        }
                                                        j++;
                                                }
                                                fprintf(pFile, "Wynik gracza %d = %d\n", i, sum);
                                        }
                                        fclose(pFile);
                                        cards tab[1000];
                                        int i = 0;
                                        while (deck[i].owner != NULL) {
                                                if (deck[i].col == 0) {
                                                        tab[i] =
                                                        {
                                                                "blue",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 1) {
                                                        tab[i] =
                                                        {
                                                                "red",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 2) {
                                                        tab[i] =
                                                        {
                                                                "violet",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 3) {
                                                        tab[i] =
                                                        {
                                                                "white",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 4) {
                                                        tab[i] =
                                                        {
                                                                "yellow",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 5) {
                                                        tab[i] =
                                                        {
                                                                "black",
                                                                deck[i].value
                                                        };
                                                }
                                                if (deck[i].col == 6) {
                                                        tab[i] =
                                                        {
                                                                "green",
                                                                deck[i].value
                                                        };
                                                }
                                                i++;
                                        }
                                        j = 0;
                                        while (pile[j].owner != NULL) {
                                                if (pile[j].col == 0) {
                                                        tab[i] =
                                                        {
                                                                "blue",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 1) {
                                                        tab[i] =
                                                        {
                                                                "red",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 2) {
                                                        tab[i] =
                                                        {
                                                                "violet",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 3) {
                                                        tab[i] =
                                                        {
                                                                "white",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 4) {
                                                        tab[i] =
                                                        {
                                                                "yellow",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 5) {
                                                        tab[i] =
                                                        {
                                                                "black",
                                                                pile[j].value
                                                        };
                                                }
                                                if (pile[j].col == 6) {
                                                        tab[i] =
                                                        {
                                                                "green",
                                                                pile[j].value
                                                        };
                                                }
                                                i++;
                                                j++;
                                        }
                                        srand(time(NULL));
                                        int ilosc = 0;
                                        while (pile[ilosc].owner != NULL) {
                                                ilosc++;
                                        }
                                        int m = 0;
                                        while (deck[m].owner != NULL) {
                                                ilosc++;
                                                m++;
                                        }
                                        for (int j = 1; j < (ilosc - 1); j++) {
                                                for (int i = 0; i < 1000; i++) {
                                                        int b = GiveRandom((ilosc - j));
                                                        tab[900] = tab[b];
                                                        tab[b] = tab[b + j];
                                                        tab[b + j] = tab[900];
                                                }
                                        }
                                        pFile = fopen("file.txt", "w");
                                        fputs("active player = 1\n", pFile);
                                        fprintf(pFile, "active round = %d\n", (active_round + 1));
                                        fprintf(pFile, "players number = %d\n", n);
                                        fprintf(pFile, "rounds number = %d\n", r);
                                        fprintf(pFile, "explosion threshold = %d\n", e);
                                        for (int i = 1; i <= n; i++) {
                                                fprintf(pFile, "%d player hand cards: \n", i);
                                                for (int j = i; j < ilosc; j += n) {
                                                        fprintf(pFile, "%d %s \n", tab[j].value, tab[j].color);
                                                }
                                                fprintf(pFile, "%d player deck cards: \n", i);
                                        }
                                        for (int i = 1; i <= stosy; i++) {
                                                fprintf(pFile, "%d pile cards: \n", i);
                                        }
                                        fclose(pFile);
                                }
                        }
                        else {  // wypisywanie stanu całej gry
                                pFile = fopen("file.txt", "w");
                                if (active_player == n) {
                                        fputs("active player = 1\n", pFile);
                                }
                                else {
                                        fprintf(pFile, "active player = %d\n", (1 + active_player));
                                }
                                fprintf(pFile, "active round = %d\n", active_round);
                                fprintf(pFile, "players number = %d\n", n);
                                fprintf(pFile, "rounds number = %d\n", r);
                                fprintf(pFile, "explosion threshold = %d\n", e);
                                j = 0;
                                g = 0;
                                for (int i = 1; i <= n; i++) {
                                        fprintf(pFile, "%d player hand cards: \n", i);
                                        while (hand[j].owner == i) {
                                                if (j == chosen_card) {
                                                        j++;
                                                }
                                                else {
                                                        fprintf(pFile, "%d %s \n", hand[j].value, hand[j].color);
                                                        j++;
                                                }
                                        }
                                        fprintf(pFile, "%d player deck cards: \n", i);
                                        while (deck[g].owner == i) {
                                                fprintf(pFile, "%d %s \n", deck[g].value, deck[g].color);
                                                g++;
                                        }
                                        if ((boom == 1) && (i == active_player)) {
                                                for (int z = 0; z < 150; z++) {
                                                        if (pile[z].owner == chosen_pile) {
                                                                while (pile[z].owner == chosen_pile) {
                                                                        fprintf(pFile, "%d %s \n", pile[z].value, pile[z].color);
                                                                        z++;
                                                                }
                                                                fprintf(pFile, "%d %s \n", hand[b].value, hand[b].color);
                                                                break;
                                                        }
                                                }
                                        }
                                }
                                j = 0;
                                for (int i = 1; i <= stosy; i++) {
                                        fprintf(pFile, "%d pile cards: \n", i);
                                        while (pile[j].owner == i) {
                                                if ((i == chosen_pile) && (boom == 1)) {
                                                        j++;
                                                }
                                                else {
                                                        fprintf(pFile, "%d %s \n", pile[j].value, pile[j].color);
                                                        j++;
                                                }
                                        }
                                        if ((i == chosen_pile) && (boom == 0)) {
                                                fprintf(pFile, "%d %s \n", hand[chosen_card].value, hand[chosen_card].color);
                                        }
                                }
                                fputs("0\n", pFile);
                                fclose(pFile);
                        }
                }
                else {
                        fclose(pFile);
                        Sleep(10);
                }
        }
}
