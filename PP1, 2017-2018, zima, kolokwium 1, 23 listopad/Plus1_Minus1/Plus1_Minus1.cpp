#include <stdio.h>
#include <string.h> // strlen
#include <ctype.h> // isdigit


int main()
{
	char text[210];
	char temp[210];

	printf("Podaj wartosc z zakresu <1; 10^200>: ");
	fgets(text, sizeof(text), stdin);

	/*
		Określenie zakresów danych dla 10^N:
		N=1: 10     (2   +1)	+1 dla terminatora ASCIIZ
		N=2: 100    (3   +1)
		N=200: ...  (1+N +1)
	*/

	int i, len = strlen(text) - 1;
	// sprawdź długość
	if (len > 201)
	{
		printf("Blad w danych wejsciowych!\n");
		return 1;
	}
	
	// sprawdź, czy dane wejściowe są poprawne - czy wszystkie znaki to cyfry
	for (i = 0; i < len; i++)
		if (!isdigit(text[i]))
		{
			printf("Blad w danych wejsciowych!\n");
			return 1;
		}

	// *********************
	// dodawanie 1
	int carry = 1;	// przeniesienie z poprzedniej pozycji; skoro dodajemy 1, to możemy to zrobić ustawiając "sztuczne" przeniesienie
					// z pozycji "nieistniejącej" - przed cyfrą jedności
	int j = 0;		// zmienna j odpowiada za nawigowanie po tablicy wynikowej
	for (i = len - 1; i >= 0; i--)
	{
		int new_digit = text[i] + carry; // dodanie przeniesienia z poprzedniej pozycji 
		if (new_digit > '9')
		{
			// jeśli suma będzie wiekszą od 9 (czyli 10) to przenieś +1 na następną pozycję a na bieżącą wpisz 0
			new_digit = '0';
			carry = 1;
		}
		else
			carry = 0; // jeśli nowa cyfra będzie z zakresu 1-9 to nie ma przeniesienia
		temp[j++] = new_digit; // konwersja liczby na znak ascii
	}
	if (carry) // jeśli skończyliśmy przetwarzać dane uzytkownika i mamy przeniesienie, to wstaw je na początek
		temp[j++] = '1';

	// wyświetl tablicę temp od końca
	j--;
	for (; j >= 0; j--)
		printf("%c", temp[j]);
	printf("\n");

	// *************************
	// -1
	carry = -1;
	j = 0;
	for (i = len - 1; i >= 0; i--)
	{
		int new_digit = text[i] + carry;
		if (new_digit < '0')
		{
			carry = -1;
			new_digit = '9';
		}
		else
			carry = 0;
		temp[j++] = new_digit;
	}

	// wyświetl tablicę temp od końca
	j--;
	for (; j >= 0; j--)
		printf("%c", temp[j]);
	printf("\n");


	return 0;
}

