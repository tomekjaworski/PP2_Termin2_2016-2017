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
	int idmin[3] = { 0, 1, 2 };
	int idmax[3] = { 3, 4, 5 };

	for (i = 0; i < 20; i++)
	{
		// sprawdź, czy i-ta wartość z tablicy values jest mniejsza którejkolwiek z wartości, do których indeksy są przechowywane w tablicy idmin?
		for (j = 0; j < 3; j++)
			if (values[i] < values[idmin[j]])
			{
				idmin[j] = i;
				break;
			}

		// to samo dla wartości maksymalnych
		for (j = 0; j < 3; j++)
			if (values[i] > values[idmax[j]])
			{
				idmax[j] = i;
				break;
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

