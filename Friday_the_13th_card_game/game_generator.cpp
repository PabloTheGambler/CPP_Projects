include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n; //liczba graczy
int k; //liczba kociolkow bez zielonych
int g; //ilosc zielonych karty
int gv; //wartosc zielonych
int o; //liczba innych kart
int e; // wartosc explosion
int r; // liczba rund
int equals[100]; //wartosc kolejnych niezielonych kart

struct cards {
	char color[15];
	int value;
};

int GiveRandom(int a) {
	return  (rand() % a);

}

int main() {
	cout << "Wpisz: liczba graczy, kociolkow. zielonych, wartosc zielonych, liczba innych, explosion, liczbe rund ";
	cin >> n >> k >> g >> gv >> o >> e >> r;
	cards tab[300];
	for (int i = 0; i < g; i++) {
		tab[i] =
		{
			"green",
			gv
		};
	}
	cout << "Wpisz wartoÅci innych kart: ";
	for (int i = 0; i < o; i++) {
		cin >> equals[i];
	}
	if (k > 0) {
		for (int i = 0; i < o; i++) {
			tab[(i + g)] =
			{
				"blue",
				equals[i]
			};
		}
	}
	if (k > 1) {
		for (int i = 0; i < o; i++) {
			tab[(i + g + o)] =
			{
				"red",
				equals[i]
			};
		}
	}
	if (k > 2) {
		for (int i = 0; i < o; i++) {
			tab[(i + g + o + o)] =
			{
				"violet",
				equals[i]
			};
		}
	}
	if (k > 3) {
		for (int i = 1; i < o; i++) {
			tab[(i + g + o + o + o)] =
			{
				"yellow",
				equals[i]
			};
		}
	}
	if (k > 4) {
		for (int i = 0; i < o; i++) {
			tab[(i + g + o + o + o + o)] =
			{
				"white",
				equals[i]
			};
		}
	}
	if (k > 5) {
		for (int i = 0; i < o; i++) {
			tab[(i + g + o + o + o + o + o)] =
			{
				"black",
				equals[i]
			};
		}
	}
	srand(time(NULL));

	for (int j = 1; j < (k*o +g - 1); j++) {
		for (int i = 0; i < 1000; i++) {
			int b = GiveRandom((k * o + g - j));
			tab[200] = tab[b];
			tab[b] = tab[b + j];
			tab[b + j] = tab[200];
		}
	}
	FILE* pFile;
	pFile = fopen("file.txt", "w");
	fputs("active player = 1\n", pFile);
	fputs("active round = 1\n", pFile);
	fprintf(pFile, "players number = %d\n", n);
	fprintf(pFile, "rounds number = %d\n", r);
	fprintf(pFile, "explosion threshold = %d\n", e);
	for (int i = 1; i <= n; i++) {
		fprintf(pFile, "%d player hand cards: \n", i);
		for (int j = (i-1); j < (k * o + g); j += n) {
			fprintf(pFile, "%d %s \n", tab[j].value, tab[j].color);
		}
		fprintf(pFile, "%d player deck cards: \n", i);
	}
	for (int i = 1; i <= k; i++) {
		fprintf(pFile, "%d pile cards: \n", i);
	}
	fputs("0\n", pFile);
	fclose(pFile);
}
