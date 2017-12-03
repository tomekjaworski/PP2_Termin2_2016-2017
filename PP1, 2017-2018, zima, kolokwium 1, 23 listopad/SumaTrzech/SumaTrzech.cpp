#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>


int main()
{
	int i, j, values[20] = {};
	for (i = 0; i < 20; i++)
	{
		//values[i] = rand() % 100;
		printf("Podaj wartosc %d/20: ", i + 1);
		scanf("%d", &values[i]);
	}

	// wyświetl dane
	for (i = 0; i < 20; i++)
		printf("%d ", values[i]);
	printf("\n");

	// znajdź indeksy trzech najmniejszych i trzech największych
	int idmin[3]; // tablica trzech najmniejszych wartości, posortowanych rosnąco
	int idmax[3]; // tablica trzech największych wartości, posortowanych malejąco
	
	int nidmin = 0; // liczba elementów w tablicy idmin
	int nidmax = 0; // liczba elementów w tablicy idmax

	for (i = 0; i < 20; i++)
	{
		// MINIMUM
		// Znajdź pozycję (j) w liście zapamiętanych pozycji wartości najmniejszych idmin[],
		// która będzie mniejsza od wartości values[i].
		// Konstrukcja ta pozostawi w zmiennej j pozycję 0-2, jeśli w idmin[] jest wartość mniejsza od value[i]
		// lub wartość 3, jeśli mniejszej nie ma.
		// Warunek j < 3 && j < nidmin to inaczej j < min(3, nidmin) i oznacza:
		// "powtarzaj pętle tak długo, jak j < od 3 i nidmin"
		int j, k;
		for (j = 0; j < 3 && j < nidmin; j++)
			if (values[i] <= values[idmin[j]])
				break;

		// Wszystkie wartości większe należy przesunąć w prawo, aby zrobić mniejsce dla nowej - mniejszej.
		// Wartość j=3 będzie tutaj dopuszczalna - pętla nie wykona ani jednej iteracji.
		for (k = 2; k > j; k--)
			idmin[k] = idmin[k - 1];

		// Jeśli pierwsza pętla znalazła pozycję, to wstaw tam pozycję nowej, najmniejszej wartości
		if (j != 3)
		{
			idmin[k] = i;
			nidmin++; // zwiększ liczbę pozycji w tablicy idmin o 1
		}

		// MAKSIMUM - to samo, tylko inny operator porównania (jest >= zamiast <=)
		for (j = 0; j < 3 && j < nidmax; j++)
			if (values[i] >= values[idmax[j]])
				break;

		for (k = 2; k > j; k--)
			idmax[k] = idmax[k - 1];
		if (j != 3)
		{
			idmax[k] = i;
			nidmax++;
		}
	}

	// wyświelt wyniki:
	int sum_min = 0, sum_max = 0;

	printf("Wartosci najmniejsze: ");
	for (i = 0; i < 3; i++)
		printf("[%d]=%d ", idmin[i], (sum_min += values[idmin[i]], values[idmin[i]]));
	printf("Suma =%d\n", sum_min);

	printf("Wartosci najwieksze: ");
	for (i = 0; i < 3; i++)
		printf("[%d]=%d ", idmax[i], (sum_max += values[idmax[i]], values[idmax[i]]));
	printf("Suma =%d\n", sum_max);

	// w wywołaniu funkcji printf stosowane jest wyrażenie (,)

    return 0;
}

