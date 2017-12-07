#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i, tab[4];

	for (int i = 0; i < 4; i++)
	{
		// pobierz wartość
		printf("Podaj liczbe z zakresu <-100; 100>: ");
		scanf("%d", &tab[i]);

		// sprawdź, czy jest w zakresie -100 - 100
		if (tab[i] < -100 || tab[i] > 100)
		{
			printf("Blad danych; uruchom program ponownie!\n");
			return 1;
		}
	}

	// wyświetl w kolejności wprowadzania
	printf("Dane wprowadzone: ");
	for (i = 0; i < 4; i++)
		printf("%d %s", tab[i], i == 3 ? "\n" : "");

	// wyznacz średnią, min i max:
	int min = tab[0], max = tab[0], avg = 0;
	for (i = 0; i < 4; i++)
	{
		min = tab[i] < min ? tab[i] : min;
		max = tab[i] > max ? tab[i] : max;
		avg += tab[i];
	}
	printf("Minimum: %d\n", min);
	printf("Maksimum: %d\n", max);
	printf("Srednia: %.2f\n", avg / 4.0f);

	// wyświetl liczby w kolejności rosnącej:
	// na zajęciach nie było jeszcze sortowania, więc wyświetlanie BEZ sortownia
	for (i = 0; i < 4; i++)
	{
		// znjdź minimum w postaci indeksu elementu o najmniejszej wartości
		int j, imin = 0;
		for (j = 0; j < 4; j++)
			imin = tab[j] < tab[imin] ? j : imin;

		// wyświetl element (jego wartość)
		printf("%d ", tab[imin]);

		// Zastąp wartość imin-tego elementu wartością większą, niż dopuszczalny zakres danych (1000)
		// Dzięki temu w następnej iteracji element ten nie będzie już wybierany.
		// W końcu 1000 nie może się pojawić w danych wejsciowych :)
		tab[imin] = 1000;
	}

	printf("\n");
	
	return 0;
}

