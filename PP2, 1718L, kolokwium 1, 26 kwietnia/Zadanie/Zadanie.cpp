// Zadanie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>

struct set_t
{
	int data[100];
	int count;
	int capacity;
};


void set_print(const set_t* pset)
{
	if (!pset)
		return;

	printf("Zbior (%d elementow / %d pojemosci / %.2f zajetosci)\n",
		pset->count, pset->capacity, 100.0f * (float)pset->count / (float)pset->capacity);
	printf("Liczby: [");
	for (int i = 0; i < pset->count; i++)
		printf(i == 0 ? "%d" : ", %d", pset->data[i]);
	printf("]\n");
}

enum set_store_mode_t {
	ssm_binary,
	ssm_text
};

int set_store(const set_t* pset, const char* filename, enum set_store_mode_t mode)
{
	if (!pset || !filename)
		return -1;

	FILE* f = fopen(filename, mode == ssm_text ? "w" : "wb");
	if (!f)
		return -2;

	if (mode == ssm_binary)
		fwrite(pset, sizeof(struct set_t), 1, f);
	else
	{
		fprintf(f, "%d %d\n", pset->capacity, pset->count);
		for (int i = 0; i < pset->count; i++)
			fprintf(f, "%d ", pset->data[i]);
		fprintf(f, "\n");
	}
	
	fclose(f);
	return 0;
}

int set_load(set_t* pset, const char* filename, enum set_store_mode_t mode)
{
	struct set_t s;
	if (!pset || !filename)
		return -1;

	FILE* f = fopen(filename, mode == ssm_text ? "r" : "rb");
	if (!f)
		return -2;

	if (mode == ssm_binary)
	{
		if (fread(&s, sizeof(struct set_t), 1, f) != 1)
		{
			fclose(f);
			return -3;
		}
	} else
	{
		int cap, count;
		if (fscanf(f, "%d %d", &cap, &count) != 2)
		{
			fclose(f);
			return -3;
		}
		if (cap < 0 || count < 0 || cap > 100 || count > 100 || count > cap)
		{
			fclose(f);
			return -3;
		}

		s.capacity = cap;
		s.count = count;
		for (int i = 0; i < s.count; i++)
			if (fscanf(f, "%d", &s.data[i]) != 1)
			{
				fclose(f);
				return -3;
			}
	}

	fclose(f);

	// sprawdź unikalność
	for (int i = 0; i < s.count; i++)
		for (int j = 0; j < s.count; j++)
			if (s.data[i] == s.data[j] && i != j)
				return -3;
	// przerzuć wczytane dane pod wskaźnik
	memcpy(pset, &s, sizeof(struct set_t));
	return 0;
}

// ############################################################################################################
// ############################################################################################################
// ############################################################################################################
// ############################################################################################################
// ############################################################################################################


struct set_t* set_init(struct set_t* pset, int capacity)
{
	if (pset == NULL)
		return NULL;
	if (capacity < 0 || capacity > 100)
		return NULL;

	memset(pset, 0, sizeof(struct set_t));
	pset->capacity = capacity;
	return pset;
}
int set_get_count(const struct set_t* pset)
{
	if (!pset)
		return -1;
	return pset->count;
}
int set_get_capacity(const struct set_t* pset)
{
	if (!pset)
		return -1;
	return pset->capacity;
}

int set_has(const struct set_t* pset, int value)
{
	if (!pset)
		return -1;

	for (int i = 0; i < pset->count; i++)
		if (pset->data[i] == value)
			return i;
	return -2;
}

int set_append(struct set_t* pset, int value)
{
	if (!pset)
		return -1;
	if (pset->count == pset->capacity)
		return -2;

	if (set_has(pset, value) >= 0)
		return -3;

	pset->data[pset->count++] = value;
	return 0;
}

int set_is_full(const struct set_t* pset)
{
	if (!pset)
		return -1;

	return pset->capacity == pset->count;
}

int set_compare(const struct set_t* s1, const struct set_t* s2)
{
	if (!s1 || !s2)
		return -1;
	if (s1->count != s2->count)
		return -2;
	for (int i = 0; i < s1->count; i++)
		if (s1->data[i] != s2->data[i])
			return -2;
	return 0;
}

int set_clear(struct set_t* pset)
{
	if (!pset)
		return -1;

	pset->count = 0;
	return 0;
}

struct set_t* set_copy_full(struct set_t* pdest, const struct set_t* psource)
{
	if (!pdest || !psource)
		return NULL;

	memcpy(pdest, psource, sizeof(struct set_t));
	return pdest;
}

int set_copy_data(struct set_t* pdest, const struct set_t* psource)
{
	if (!pdest || !psource)
		return -1;

	if (pdest->capacity < psource->count)
		return -2;

	memcpy(pdest->data, psource->data, sizeof(int) * psource->count);
	pdest->count = psource->count;
	return 0;
}




void store(const char* fname, const char* data)
{
	FILE* f = fopen(fname, "w");
	assert(f);
	fprintf(f, data);
	fclose(f);
}

int main()
{
	struct set_t s1, s2, s3, s4;
	// sprawdzanie funkcji set_init
	assert(set_init(NULL, 0) == NULL);
	assert(set_init(&s1, -1) == NULL);
	assert(set_init(&s1, 101) == NULL);
	assert(set_init(&s1, 0) == &s1);
	assert(set_init(&s1, 10) == &s1);

	// spradzanie funkcji set_get_count
	assert(set_get_count(NULL) == -1);
	set_init(&s1, 10);
	set_init(&s2, 50);
	assert(set_get_count(&s1) == 0 && set_get_count(&s2) == 0);

	// sprawdzanie funkcji set_get_capacity
	assert(set_get_capacity(NULL) == -1);
	assert(set_get_capacity(&s1) == 10 && set_get_capacity(&s2) == 50);

	set_init(&s1, 5);
	set_init(&s2, 5);

	// sprwdzanie funkcji set_append oraz set_has
	assert(set_has(NULL, 123) == -1);
	assert(set_append(NULL, 456) == -1);

	assert(set_has(&s1, 123) == -2); // brak elementu
	assert(set_append(&s1, 123) == 0); // dodanie ok
	assert(set_has(&s1, 123) == 0); // element na pozycji 0

	assert(set_append(&s1, 123) == -3); // powtórka; operacja przerwana
	assert(set_has(&s1, 123) == 0); // element na pozycji 0

	assert(set_append(&s1, 124) == 0); // dodanie ok
	assert(set_append(&s1, 125) == 0); // dodanie ok

	assert(set_has(&s1, 124) == 1); // element na pozycji 1
	assert(set_has(&s1, 125) == 2); // element na pozycji 2

	assert(set_get_count(&s1) == 3); // trzy elemety w zbiorze

	// sprawdzenie limitów
	assert(set_is_full(NULL) == -1);
	assert(set_is_full(&s1) == 0); // nie jest pełny

	assert(set_append(&s1, 200) == 0); // dodanie ok
	assert(set_append(&s1, 300) == 0); // dodanie ok
	assert(set_get_count(&s1) == set_get_capacity(&s1)); // pięć elementów
	assert(set_is_full(&s1) == 1); // jest pełny

	// czyszczenie zbioru
	assert(set_clear(NULL) == -1);
	assert(set_clear(&s1) == 0);
	assert(set_get_count(&s1) == 0 && set_get_capacity(&s1) == 5); // kasowane są tylko dane

	for (int i = 0; i < 5; i++)
		set_append(&s1, i + 1);

	// test kopiowania pełnego
	set_init(&s2, 30);
	assert(set_copy_full(NULL, NULL) == NULL);
	assert(set_copy_full(&s2, NULL) == NULL);
	assert(set_copy_full(NULL, &s1) == NULL);
	assert(set_copy_full(&s2, &s1) == &s2); // wykonaj kopiowanie

	assert(set_get_count(&s1) == set_get_count(&s2)); // po kopiowaniu pełnym: ta sama liczba elementów
	assert(set_get_capacity(&s1) == set_get_capacity(&s2)); // po kopiowaniu pełnym: ta sama pojemność

	printf("Ocena 3.0\n");

	// test kopiowania danych
	set_init(&s3, 4);
	assert(set_copy_data(NULL, NULL) == -1);
	assert(set_copy_data(&s3, NULL) == -1);
	assert(set_copy_data(NULL, &s1) == -1);
	assert(set_copy_data(&s3, &s1) == -2); // s2 ma za małą pojemność

	set_init(&s3, 6);
	assert(set_copy_data(&s3, &s1) == 0); // wykonaj kopiowanie danych
	assert(set_get_capacity(&s3) == 6); // pojemność nie ulega zmianie
	assert(set_get_count(&s3) == 5);  // liczba elementów sięzgadza z s1

	// test porównywania
	assert(set_compare(NULL, NULL) == -1);
	assert(set_compare(&s1, NULL) == -1);
	assert(set_compare(NULL, &s1) == -1);
	assert(set_compare(&s1, &s2) == 0);
	assert(set_compare(&s1, &s3) == 0);
	assert(set_compare(&s2, &s3) == 0);

	printf("Ocena 3.5\n");
	
	set_init(&s4, 6);
	assert(set_compare(&s2, &s4) == -2);

	// zapis  tekstowy
	assert(set_store(NULL, NULL, ssm_text) == -1);
	assert(set_store(&s1, NULL, ssm_text) == -1);
	assert(set_store(NULL, "plik.txt", ssm_text) == -1);
	assert(set_store(&s1, "M*A*S*H.txt", ssm_text) == -2); // nie można utworzyć pliku
	
	assert(set_store(&s1, "s1.txt", ssm_text) == 0); // zapis ok
	assert(set_store(&s3, "s3.txt", ssm_text) == 0); // zapis ok


	// wczytywanie - format tekstowy
	struct set_t s1t, s3t;
	set_init(&s1t, 20);
	set_init(&s3t, 20);

	assert(set_load(NULL, NULL, ssm_text) == -1);
	assert(set_load(&s1, NULL, ssm_text) == -1);
	assert(set_load(NULL, "plik.txt", ssm_text) == -1);
	assert(set_load(&s1t, "plik_ktorego_nie_bylo.txt", ssm_text) == -2); // brak pliku

	assert(set_load(&s1t, "s1.txt", ssm_text) == 0); // odczyt ok
	assert(set_load(&s3t, "s3.txt", ssm_text) == 0); // odczyt ok

	// sprawdczenie, czy to co się wczytało, jest ok
	assert(set_get_capacity(&s1) == set_get_capacity(&s1t)); // pojemności się zgadzają
	assert(set_get_capacity(&s3) == set_get_capacity(&s3t)); // pojemności się zgadzają

	assert(set_compare(&s1, &s1t) == 0); // dane też
	assert(set_compare(&s3, &s3t) == 0); // dane też

	printf("Ocena 4.0\n");

	// zapis binarny
	assert(set_store(NULL, NULL, ssm_binary) == -1);
	assert(set_store(&s1, NULL, ssm_binary) == -1);
	assert(set_store(NULL, "plik.bin", ssm_binary) == -1);
	assert(set_store(&s1, "M*A*S*H.bin", ssm_binary) == -2); // nie można utworzyć pliku

	assert(set_store(&s1, "s1.bin", ssm_binary) == 0); // zapis ok
	assert(set_store(&s3, "s3.bin", ssm_binary) == 0); // zapis ok

	// wczytywanie - format binarny
	struct set_t s1b, s3b;
	set_init(&s1b, 20);
	set_init(&s3b, 20);

	assert(set_load(NULL, NULL, ssm_binary) == -1);
	assert(set_load(&s1, NULL, ssm_binary) == -1);
	assert(set_load(NULL, "plik.bin", ssm_binary) == -1);
	assert(set_load(&s1b, "plik_ktorego_nie_bylo.bin", ssm_binary) == -2); // brak pliku

	assert(set_load(&s1b, "s1.bin", ssm_binary) == 0); // odczyt ok
	assert(set_load(&s3b, "s3.bin", ssm_binary) == 0); // odczyt ok

	// sprawdczenie, czy to co się wczytało, jest ok
	assert(set_get_capacity(&s1) == set_get_capacity(&s1b)); // pojemności się zgadzają
	assert(set_get_capacity(&s3) == set_get_capacity(&s3b)); // pojemności się zgadzają

	assert(set_compare(&s1, &s1b) == 0); // dane też
	assert(set_compare(&s3, &s3b) == 0); // dane też

	printf("Ocena 4.5\n");

	// próba wczytywania plików binarnych jako tekstowe i odwrotnie
	struct set_t s;
	assert(set_load(&s, "s1.bin", ssm_text) == -3); // blad formatu
	assert(set_load(&s, "s3.bin", ssm_text) == -3); // blad formatu
	assert(set_load(&s, "s1.txt", ssm_binary) == -3); // blad formatu
	assert(set_load(&s, "s3.txt", ssm_binary) == -3); // blad formatu

	store("dummy.txt", "6 5 4 3 2 1 0");
	assert(set_load(&s, "dummy.txt", ssm_text) == 0); // ok
	assert(set_get_capacity(&s) == 6 && set_get_count(&s) == 5); // czy podstawowe informacje się zgadzają?

	// dodatkowy test wczytywania tekstowego:
	struct set_t sold;
	store("dummy.txt", "9 7 41 42 43 44 45 46 47");
	assert(set_load(&s, "dummy.txt", ssm_text) == 0); // ok
	set_copy_full(&sold, &s); // kopia całego s do sold

	store("dummy.txt", "1000");
	assert(set_load(&s, "dummy.txt", ssm_text) == -3); // blad formatu
	store("dummy.txt", "50");
	assert(set_load(&s, "dummy.txt", ssm_text) == -3); // blad formatu
	store("dummy.txt", "50 50");
	assert(set_load(&s, "dummy.txt", ssm_text) == -3); // blad formatu
	store("dummy.txt", "50 1000");
	assert(set_load(&s, "dummy.txt", ssm_text) == -3); // blad formatu
	store("dummy.txt", "5 5 1 2 2 3 4");
	assert(set_load(&s, "dummy.txt", ssm_text) == -3); // bład formatu; liczby nie są unikalne

	assert(set_compare(&s, &sold) == 0);	// funkcja set_load nie może uszkadzać s,
											// jeśli nie da się do niego wczytać danych z pliku

	set_print(&s);

	printf("Ocena 5.0. Gratulacje!\n");

	return 0;
}

