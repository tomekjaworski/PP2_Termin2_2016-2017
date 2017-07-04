#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h> // isalpha
#include <string.h> // strtok

void clean(char* str)
{
	// W tekście pozostawiam tylko litery; pozostałe znaki zastępuję spacjami
	// to pozwala na łatwe usunięcie cyfr, przecinków i innych śmieci.
	// ponadto zamieniam duże litery na małe, bo w końcu "Początek" i "początek" jest tym samym słowem.
	// mogę użyć funkcji isalnum, ponieważ w pliku dwaTeksty.txt nie ma polskich liter, które nie są z zakresu A-Za-z
	for (int i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
		if (!isalnum(str[i]))
			str[i] = ' ';
	}
}

int calc_hash(const char* str)
{
	// najprościej, jak się da
	int hash = 0;
	while (*str)
		hash += *str++;

	return hash;
}

struct item_t {
	char word[100];
	int mark;
	int hash;
	struct item_t* pnext;
};

struct item_t* find_word(struct item_t* phead, const char* word)
{
	int hash = calc_hash(word);

	// szukaj po wartości skrótu
	while (phead != NULL)
	{
		if (phead->hash == hash) // skoro wartości skrótu się zgadzają, to możę teksty też?
			if (strcmp(phead->word, word) == 0)
				return phead; // tak - zwracamy element

		phead = phead->pnext;
	}

	// no cóż, nie udało się znaleźć słowa
	return NULL;
}

struct item_t* add_word(struct item_t* phead, const char* word)
{
	// przygotuj nowy element
	struct item_t* pnew = (struct item_t*)calloc(1, sizeof(item_t));
	assert(pnew != NULL);

	// wypełnij danymi
	strcpy(pnew->word, word);
	pnew->hash = calc_hash(word);

	// oraz dodaj na koniec
	if (phead == NULL)
		return pnew;

	// znajdź ostatni element listy słów
	struct item_t* plast = phead;
	while (plast->pnext != NULL)
		plast = plast->pnext;

	// dodaj element na końcu
	plast->pnext = pnew;

	return phead;
}


int main()
{
	FILE* f = fopen("m:\\.public_html\\pp2\\f7d34a\\dwaTeksty.txt", "r");
	assert(f != NULL);

	char l1[10000];
	char l2[10000];

	// wczytaj obie linie
	fgets(l1, sizeof(l1), f);
	fgets(l2, sizeof(l1), f);

	// usuń wszystko za wyjątkiem liter
	clean(l1);
	clean(l2);


	struct item_t* phead = NULL;

	// przetwarzaj tekst 1
	char* word = strtok(l1, " ");
	while (word != NULL)
	{
		struct item_t* pword = find_word(phead, word);
		if (pword == NULL) // dodaj tylko 
			phead = add_word(phead, word);

		word = strtok(NULL, " ");
	}

	// przetwarzaj tekst 2
	word = strtok(l2, " ");
	while (word != NULL)
	{
		struct item_t* pword = find_word(phead, word);
		if (pword != NULL)
		{
			// słowo było w tekscie 1, oznacz je
			pword->mark = 1;
		}
		word = strtok(NULL, " ");
	}

	// Teraz w liście phead znajdują się słowa z pliku dwaTeksty.txt bez duplikatów
	// a słowa, które są w obu plikach posiadają 1 w polu mark.
	// I tylko te słowa wyświetlamy
	printf("Lista slow wspolnych dla obu wierszy:\n");
	for (struct item_t* pword = phead; pword != NULL; pword = pword->pnext)
		if (pword->mark)
			printf("%s ", pword->word);

	// zwalnianie pamieci
	while (phead != NULL)
	{
		struct item_t* temp = phead;
		phead = phead->pnext;
		free(temp);
	}

    return 0;
}

