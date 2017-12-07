#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int tab[20], i;
	//srand(time(0));

	// pobierz od użytkownika 20 liczb całkowitych
	printf("Podaj 20 liczb calkowitych:\n");
	for (i = 0; i < 20; i++)
	{
		printf("Podaj liczbe %d/20: ", i + 1);
		scanf("%d", &tab[i]);
		//tab[i] = rand() % 10;
	}

	// policz średnią
	float avg = 0;
	for (i = 0; i < 20; i++)
		avg += tab[i];
	avg /= 20.0f;

	printf("Wartosc srednia: %.2f\n", avg);

	// znajdź trzy liczby
	int a, b, c; // zmienne a, b, c będą wykorzystane do iteracji przes wszystkie możliwe kombinacje indeksów (2 sumie 20^3)
	int i1 = 0, i2 = 1, i3 = 2; // indeksy trójki elementó, których suma jest najbliższa średniej

	// trzy pętle pozwolą wyszukać każdą możliwą trójkę (a, b, c) z wartościami poszczególnych elementów 0-19
	// w sumie 20^3 trójek
	for (a = 0; a < 20; a++)
		for (b = 0; b < 20; b++)
			for (c = 0; c < 20; c++)
			{
				// interesuje nas tylko taka kombinacja trójki indeksów
				// aby nie było w nich powtórzeń
				if (a == b || a == c || b == c)
					continue; // są powtórki, pomijamy ten przypadek

				// policz sume a,b,c oraz i1,i2,i3
				float suma1 = tab[a] + tab[b] + tab[c]; // suma trzech bieżących elementów
				float suma2 = tab[i1] + tab[i2] + tab[i3]; // suma trzech najlepszych (do tej pory) elementów

				// sprawdź, czy kombinacja a,b,c daje mniejszą różnicę modulo względem śrdniej
				if (fabs(suma1 - avg) < fabs(suma2 - avg))
				{
					// tak! zapamiętaj a, b i c
					i1 = a;
					i2 = b;
					i3 = c;
				}
			}

	printf("tab[%d] = %d\n", i1, tab[i1]);
	printf("tab[%d] = %d\n", i2, tab[i2]);
	printf("tab[%d] = %d\n", i3, tab[i3]);

    return 0;
}

