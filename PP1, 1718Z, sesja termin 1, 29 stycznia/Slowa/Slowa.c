// Slowa.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void generate_word_rec(const char letters[], int N, int positions[], int n)
{
	if (N == n)
	{
		// Liczba pozycji w tablicy positions jest równa liczbie znaków, a więc mamy pełne słowo.
		// Tutaj wyświetlamy wygenerowany tekst.

		for (int i = 0; i < n; i++)
			printf("%c", letters[positions[i]]);
		printf("\n");

		// Ponadto warunek ten jest również warunkiem brzegowym rekurencji.
		// Skoro mamy kompletne słowo z N==n znaków to nie ma już z czego budować dalej; kończmy rekurencję.
		return;
	}

	// szukamy pierwszej pozycji tablicy letters, która nie znajduje się jeszcze w tablicy positions
	for (int i = 0; i < N; i++)
	{
		int in_use = 0;
		for (int j = 0; j < n; j++)
			if (positions[j] == i)
			{
				// tak, ita pozycja (ity znak) jest już cześcią napisu; nie możemy go powtórzyć
				in_use = 1;
				break;
			}

		// ale jeśli i-ty znak nie jest cześcią napisu, to dodajemy go na końcu i resztę wykonujemy rekurencyjnie
		if (!in_use)
		{
				// i-ta pozycja (i-ty znak z letters) nie jest cześcią naszego napisu; możemy go wykorzystać
				positions[n] = i;
				generate_word_rec(letters, N, positions, n + 1);
		}
	}
}

int main()
{
	char letters[20];
	int N;

	printf("Podaj ciag liter/znakow: ");
	fgets(letters, sizeof(letters), stdin);

	N = strlen(letters); // do N zapisz długość tekstu
	if (N > 0 && letters[N - 1] == '\n')
	{
		// jeśli tekst jest nie pusty oraz ostatnim znakiem jest \n (normalna sytuacja dla fgets)
		// to usuń ostatni znak
		letters[N - 1] = '\x0';
		N--;
	}

	// W zadaniu mowa jest o niepowtarzaniu pozycji a nie samych znaków.
	// Powoduje to, że dla wejściowych liter "abc" oraz "aba"
	// generowane są następujące teksty: abc acb bac bca cba cab
	//                             oraz: aba aab baa baa aba aab
	// Aby uniknąć problemów, tekst należy zapisywać nie jako ciąg znaków
	// ale jako ciąg pozycji z tablicy letters. Wtedy pozycje są unikalne ale znaki już nie muszą.

	int text[20]; // tyle samo elementów co tablica znaków!!

	// zaczynamy od pustego ciągu pozycji (0 elementów)
	generate_word_rec(letters, N, text, 0);

    return 0;
}

