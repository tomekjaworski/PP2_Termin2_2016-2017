#include <stdio.h> // printf, fgets
#include <string.h> // strlen
#include <ctype.h> // isalpha
#include <stdlib.h> // rand, srand
#include <time.h> // time

int main(void)
{
	srand(time(NULL));
	
	char text[101];
	int words[50]; /* w tekście o długości 100 znaków może wystąpić maks 50 słów (wszystkie jednoznakowe)*/

	printf("Podaj tekst:");
	fgets(text, sizeof(text), stdin);

	// usuń znak nowej linii, dodawany przez fgets
	text[strlen(text) - 1] = '\x0';

	// znajdź pozycje słów
	int i, len = strlen(text);
	char ch = ' ';
	int word_counter = 0; // licznik słów
	for (i = 0; i < len; i++)
	{
		if (!isalpha(ch) && isalpha(text[i])) // czy znalazłem pierwszą literę jakiegoś słowa?
			words[word_counter++] = i; // zachowaj pozycję pierwszej litery słowa
		if (isalpha(ch) && !isalpha(text[i])) // czy znalazłęm pierwszy znak po jakimś słowie?
			text[i] = '\x0'; // tak, wstaw tam znacznik końca tekstu
		ch = text[i]; // zapamiętaj znak bieżący w tej iteracji jako znak poprzedni w następnej iteracji
	}


	/*
		W tej chwili nasz przykładowy tekst:
		[  Ala   ma kota    a kot ma ale\0] będzie wyglądał tak:
		[  Ala\0  ma\0kota\0   a\0kot\0ma\0ale\0]
	*/

	// wyświetl słowa w postaci niezmienionej (dla testów)
	printf("TEST: ");
	int j;
	for (i = 0; i < word_counter; i++)
	{
		for (j = 0; text[words[i] + j]; j++)
			printf("%c", text[words[i] + j]);
		printf(" ");
	}
	printf("\n");

	// generuj właściwą odpowiedź (10 przypadków)
	int k;

	for (k = 0; k < 10; k++)
	{
		// losuj dwa rózne słowa:
		// Losuj dwie pozycje słów do zamiany.
		// Jeśli wydanie ta sama liczba (to samo słowo), to powtórz całość
		// Jeśli w tekście jest tylko jedno słowo, to samo losowanie nie ma sensu ponieważ idx1 i idx2 siłą rzeczy muszą być takie same
		int idx1, idx2;
		do {
			idx1 = rand() % word_counter;
			idx2 = rand() % word_counter;
		} while (idx1 == idx2 && word_counter > 1);

		// zamień dwa losowe słowa miejscami
		int temp = words[idx1];
		words[idx1] = words[idx2];
		words[idx2] = temp;

		// wyświetl nową wersję
		printf("WERSJA %02d: ", k);
		int j;
		for (i = 0; i < word_counter; i++)
		{
			for (j = 0; text[words[i] + j]; j++)
				printf("%c", text[words[i] + j]);
			printf(" ");
		}
		printf("\n");
	}

}