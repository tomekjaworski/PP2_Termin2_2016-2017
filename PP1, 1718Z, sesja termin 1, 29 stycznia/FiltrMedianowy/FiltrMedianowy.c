// FiltrMedianowy.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// limit oraz własny typ danych IMAGE, będący tablicą NMAX x NMAX elementów typu int
#define NMAX 100
typedef int IMAGE[NMAX][NMAX];

void show(const IMAGE arr, int N)
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
			printf("%4d", arr[r][c]);
		printf("\n");
	}
	printf("\n");

}

void swap(int tab[], int p1, int p2)
{
	int temp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = temp;
}

void sort(int tab[], int n)
{
	int modified = 0;
	do {
		modified = 0;
		for (int i = 0; i < n - 1; i++)
		{
			if (tab[i] > tab[i + 1])
			{
				swap(tab, i, i + 1);
				modified = 1;
			}
		}
	} while (modified);
}

int median(const int data[], int N)
{
	int data2[NMAX];

	// parametr data jest const - nie można go modyfikować jego zawartości
	// zatem przed sortowaniem w miejscu należy wykonać kopię danych
	memcpy(data2, data, N * sizeof(int));
	sort(data2, N);

	// w zależności od parametru N wyznacz wartość srodkkową posortowanej tablicy data
	// lub średnią dwóch wartości, leżących najbliżej środka
	if (N % 2 == 1)
		return data2[N / 2];
	return (data2[N / 2] + data2[N / 2 - 1]) / 2;
}

// główna funkcja filtrująca, generująca obraz output na podstawie obrazu input
void filter(const IMAGE input, IMAGE output, int N)
{
	// wyczyść obraz docelowy
	memset(output, 0, sizeof(IMAGE));

	// przechodź przez wszystkie punkty (x=1..N-1, y=1..N-1)
	for (int c = 1; c < N - 1; c++)
		for (int r = 1; r < N - 1; r++)
		{
			// dla każdego położenia (r,c) okna filtra wygeneruj tablicę 9 elementów,
			// czytając je od lewej do prawej i z góry na dół
			int idx = 0, tab[9];
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					tab[idx++] = input[r + i][c + j];

			// do obrazu wyjściowego zapisz medianę z tablicy 9 elementów
			output[r][c] = median(tab, 9);
		}
}

int main()
{
	int N;
	IMAGE input, output;

#if 0
	// losowanie
	N = 8;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			input[i][j] = rand() % 128;

#else
	// wczytywanie od użytkownika
	printf("Podaj wielkosc N obrazu: ");
	int ret = scanf("%d", &N);
	if (ret != 1 || N < 3 || N > 100)
	{
		printf("Niepoprawne dane (N)\n");
		return 1;
	}

	// wczytaj właściwy obraz 
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			int value;
			int ret = scanf("%d", &value);
			if (ret != 1 || value < 0 || value > 255)
			{
				printf("Niepoprawne dane (punkty)\n");
				return 1;
			}
			input[r][c] = value;
		}
#endif

	// wyświetl obraz
	show(input, N);

	// wygeneruj obraz output poprzez filtrację obrazu input
	filter(input, output, N);

	// wyświetl obraz output
	show(output, N);


    return 0;
}

