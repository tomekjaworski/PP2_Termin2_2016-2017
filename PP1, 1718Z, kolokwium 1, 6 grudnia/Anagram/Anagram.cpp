#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
/*
Treścią zadania był następujący blok liczb:
78 97 112 105 115 122 32 112 114 111 103 114 97 109 44 32
107 116 111 114 121 32 100 108 97 32 116 101 107 115 116 117
32 112 111 100 97 110 101 103 111 32 122 32 107 108 97 119
105 97 116 117 114 121 44 32 119 121 115 119 105 101 116 108
105 32 106 101 103 111 32 97 110 97 103 114 97 109 46 65 65
65 13 10 65 110 97 103 114 97 109 32 110 97 108 101 122 121
32 103 101 110 101 114 111 119 97 99 32 119 121 108 97 99
122 110 105 101 32 110 97 32 112 111 122 105 111 109 105 101
32 115 108 111 119 32 40 91 93 32 91 93 32 91 93 41 46 0

Jest to tekst ASCIIZ w języku C, przedstawiony w postaci kodów ASCII poszczególnych znaków.
Cechy charakterystyczne (omawiane na wykładzie): 
- wartości całkowite dodatnie, z zakresu 32-126
- ostatni kod == 0 (terminator tekstów w języku C)
*/

int main()
{
	// Aby wyświetlić treść, należy powyższy blok kodów wyświetlić jako znaki a nie liczby całkowite.
	// W tym celu należy spacje zastąpić przecinkami oraz dodać elementy składniowe deklaracji
	// tablicy typu char języka C:
	char blok_kodow[] = {
		78,97,112,105,115,122,32,112,114,111,103,114,97,109,44,32,
		107,116,111,114,121,32,100,108,97,32,116,101,107,115,116,117,
		32,112,111,100,97,110,101,103,111,32,122,32,107,108,97,119,
		105,97,116,117,114,121,44,32,119,121,115,119,105,101,116,108,
		105,32,106,101,103,111,32,97,110,97,103,114,97,109,46,65,65,
		65,13,10,65,110,97,103,114,97,109,32,110,97,108,101,122,121,
		32,103,101,110,101,114,111,119,97,99,32,119,121,108,97,99,
		122,110,105,101,32,110,97,32,112,111,122,105,111,109,105,101,
		32,115,108,111,119,32,40,91,93,32,91,93,32,91,93,41,46,0
	};

	// wyświetlenie (### JEDNA LINIA ###)
	printf("Tresc zadania: %s\n", blok_kodow);

	/*
	Treść wyświetlana:
	Tresc zadania: Napisz program, ktory dla tekstu podanego z klawiatury,
	wyswietli jego anagram.AAA
	Anagram nalezy generowac wylacznie na poziomie slow ([] [] []).

	"AAA" - sekwencja trzech kodów 65, widoczna w bloku;
	"([] [] [])" - trzy punktu za zadanie Anagram
	*/

	// ANAGRAM:
	srand(time(0));

	char tekst[100];
	printf("\nPodaj tekst: ");
	fgets(tekst, sizeof(tekst), stdin);

	printf("Wpisany tekst: %s\n", tekst);

	char prev_char = ' ';
	int i, j, k;
	for (i = 0; i < strlen(tekst) + 1; i++)
	{
		// czy i-ty znak to pierwszy znak słowa?
		if (!isalpha(prev_char) && isalpha(tekst[i]))
		{
			// znajdź koniec słowa
			for (j = i; j < strlen(tekst) + 1; j++)
				if (!isalpha(tekst[j]))
					break;

			// i jest indeksem pierwszej litery słowa
			// j jest indeksem pierwszego znaku po ostatniej litery słowa
			// j-i jest długością słowa
			printf("slowo: %d-%d\n", i, j);

			// wykonaj pięć zamian liter w słowie (5 to tylko przykład)
			for (k = 0; k < 5; k++)
			{
				// losuj pozycje w słowie (a i b) tak długo, aż a będzie różne od b
				int a, b;
				do {
					// Losuj wartości z zakresu <i; j), czyli zmienne a i b mogą
					// przyjąć jedynie poprawne indeksy liter w danym słowie
					a = i + rand() % (j - i);
					b = i + rand() % (j - i);
				} while (a == b);

				// zamień miejscami dwie litery
				char temp = tekst[a];
				tekst[a] = tekst[b];
				tekst[b] = temp;
			}
		}

		prev_char = tekst[i];
	}

	printf("Wynik: %s\n", tekst);

	return 0;
}

