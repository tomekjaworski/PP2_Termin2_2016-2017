#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower

struct client_t {
	char* name;
	char* surname;
	char* phone;

	// teksty do wykorzystania na potrzeby wyszukiwania i sortowania
	char *lowered_name_surname; // imię i nazwisko małymi literami
	char *lowered_surename; // samo nazwisko małymi literami
};

struct list_t {
	struct client_t* pclient;
	struct list_t* pnext; // następny element
	struct list_t* pprev; // poprzedni element
};

enum SORT_ORDER {
	SO_DESC, // malejące z-a
	SO_ASC, // rosnące a-z
};

// podstawowe funkcje do obsługi struktury client_t
client_t* client_create(const char* name, const char* surname, const char* phone);
void client_free(struct client_t* pclient);
void client_print(const client_t* pclient);

// podstawowe funkcje do obsługi listy
struct list_t* list_add_end(struct list_t* proot, struct client_t* pclient);
void list_free(struct list_t* proot);
void list_show(const list_t* proot);
int list_count(const list_t* proot);

// funkcje do usuwnia
struct list_t* list_delete_by_index(struct list_t* proot, int index);
struct list_t* list_delete_by_name(struct list_t* proot, const char* str);
struct list_t* list_delete(struct list_t* proot, struct list_t* item);

// funkcje do wyszukiwania/pobierani
struct list_t* list_get_item_by_index(struct list_t* proot, int index);
struct list_t* list_get_item_by_name(struct list_t* proot, const char* str);

// sortowanie
struct list_t* list_sort(struct list_t* proot, enum SORT_ORDER order);


//
// ######################
//

client_t* client_create(const char* name, const char* surname, const char* phone)
{
	// przygotuj strukturę przechwoującą dane klienta
	client_t* pclient = (client_t*)malloc(sizeof(client_t));
	assert(pclient != NULL);

	// wypełnij strukturę danymi, przekazanymi w parametrze
	pclient->name = strdup(name);
	pclient->surname = strdup(surname);
	pclient->phone = strdup(phone);
	assert(pclient->name != NULL && pclient->surname != NULL && pclient->phone != NULL);

	// przygotowanie dodatkowych wersji imienia i nazwiska;
	// mozemy oczywiscie tego nie robic, ale potem robi sie bałągan w kodzie, bo i tak trzeba mieć te informacji
	assert(strlen(name) + strlen(surname) < 1000);
	char buffer[1024];
	strcpy(buffer, name);
	strcat(buffer, " ");
	strcat(buffer, surname);

	pclient->lowered_name_surname = strdup(buffer);
	pclient->lowered_surename = strdup(surname);

	for (int i = 0; pclient->lowered_name_surname[i]; i++)
		pclient->lowered_name_surname[i] = tolower(pclient->lowered_name_surname[i]);
	for (int i = 0; pclient->lowered_surename[i]; i++)
		pclient->lowered_surename[i] = tolower(pclient->lowered_surename[i]);

	return pclient;
}

void client_free(struct client_t* pclient)
{
	free(pclient->name);
	free(pclient->surname);
	free(pclient->phone);
	free(pclient->lowered_name_surname);
	free(pclient->lowered_surename);
	free(pclient);
}

void client_print(const client_t* pclient)
{
	assert(pclient != NULL);
	printf("%15s %15s %15s", pclient->name, pclient->surname, pclient->phone);
}

//
// ######################
//

struct list_t* list_add_end(struct list_t* proot, struct client_t* pclient)
{
	// przygotuj nowy element do wstawienia do listy
	struct list_t* pnew = (struct list_t*)calloc(1, sizeof(struct list_t));
	assert(pnew != NULL);

	// wstaw wskaźnik do danych
	pnew->pclient = pclient;

	// czy lista jet pusta?
	if (proot == NULL)
		return pnew; // tak, nowy element będzie pierwszym i ostatnim elementem listy

	// nie, nie jest pusta; znajdź ostatni element
	struct list_t* plast = proot;
	while (plast->pnext != NULL)
		plast = plast->pnext;

	// i podepnij nowy element na kocu listy
	pnew->pprev = plast;
	plast->pnext = pnew;

	// zwróć starą głowę listy
	return proot;
}

void list_show(const list_t* proot)
{
	printf("Zawartosc bazy:\n");
	int i;
	for (i = 1; proot != NULL; proot = proot->pnext, i++)
	{
		printf("%2d ", i);
		client_print(proot->pclient);
		printf("\n");
	}

	printf("Liczba kontaktow w bazie: %d\n\n", i - 1);
}

void list_free(struct list_t* proot)
{
	// Nie ma sensu pisania oddzielnego kodu do zwalniania całej listy, skoro w zadaniu ma być usuwanie
	// elementu na podstawie pozycji. Można zatem usuwać pierwszy element z listy tak długo, aż lista nie zostanie wyczyszczona
	while (proot != NULL)
		proot = list_delete_by_index(proot, 0);
}

int list_count(const list_t* proot)
{
	int count = 0;
	for (; proot != NULL; proot = proot->pnext)
		count++;

	return count;
}

//
// ######################
//

struct list_t* list_delete_by_index(struct list_t* proot, int index)
{
	// pobierz element z listy proot z pozycji index
	struct list_t* pitem = list_get_item_by_index(proot, index);

	// usuń ten element i ewentulanie zwróć nową głowę listy, jeśli modyfikacja głowy była konieczna
	return list_delete(proot, pitem);
}

struct list_t* list_delete_by_name(struct list_t* proot, const char* str)
{
	// pobierz element z listy proot, któego imie lub nazwisko będzie zawierało napis str
	struct list_t* pitem = list_get_item_by_name(proot, str);

	// usuń ten element i ewentulanie zwróć nową głowę listy, jeśli modyfikacja głowy była konieczna
	return list_delete(proot, pitem);
}

struct list_t* list_delete(struct list_t* proot, struct list_t* item)
{
	// czy cokolwiek chcę usunąć? (dzieki temu funkcje delete_by_name oraz delete_by_index będą nieco krótsze)
	if (item == NULL)
		return proot; 
	
	// zwalniamy dane klienta
	client_free(item->pclient);

	// czy zwalniam element, który jeste jedynym elementem listy?
	if (proot == item && proot->pnext == NULL)
	{
		free(item);
		return NULL;
	}

	// czy zwalniam pierwszy element, ale są inne w liście?
	if (proot == item)
	{
		proot = item->pnext;
		proot->pprev = NULL;
		free(item);
		return proot;
	}

	// czy zwalniam element ze środka? 
	// test dla pprev nie jest tutaj konieczny ze względu na wcześniejsze warunki
	// ale dla czytelności zostawiam
	if (item->pnext != NULL && item->pprev != NULL)
	{
		// podmień wskaźniki w następnym i poprzednim względem item
		item->pnext->pprev = item->pprev;
		item->pprev->pnext = item->pnext;

		free(item);
		return proot;
	}

	// tutaj zostanie ostatnia możliwość - usuwamy element z końca listy;
	// jeśli nie jesteśmy pewni poprawności, można dodać następujące asserta:
	assert(item->pnext == NULL && item->pprev != NULL);

	client_free(item->pclient);
	item->pprev->pnext = NULL;
	free(item);

	return proot;
}

//
// ######################
//


struct list_t* list_get_item_by_index(struct list_t* proot, int index)
{
	// czy indeks mieści się w zakresie?
	if (index < 0 || index >= list_count(proot))
		return NULL;

	// liczymy
	int i = 0;
	for (;; proot = proot->pnext, i++)
		if (i == index)
			return proot; // ok, element się odliczył

	// tutaj nigdy się nie znajdziemy, ale dla spokoju kompilatora wstawiam return
	return NULL;
}

struct list_t* list_get_item_by_name(struct list_t* proot, const char* str)
{
	// pomniejsz litery w str; dzięki temu A będzie równe a
	char str_lowered[1000];
	strncpy(str_lowered, str, sizeof(str_lowered));
	for (int i = 0; str_lowered[i]; i++)
		str_lowered[i] = tolower(str_lowered[i]);

	for (; proot != NULL; proot = proot->pnext)
		// czy tekst str_lowered występuje w lowered_name_surname?
		if (strstr(proot->pclient->lowered_name_surname, str_lowered) != NULL)
			return proot; // tak - zwracamy element listy

	// niestety, nie znaleźliśmy tego tekstu
	return NULL;
}


struct list_t* list_sort(struct list_t* proot, enum SORT_ORDER order)
{
	// no dobrze - sortowanie... z tym najwięcej osób miało problemy
	// ale wbrew pozorom to jest akurat proste do zrobienia, ponieważ: 
	// 1) mam list_count czyli informację o liczbie elementów
	// 2) mam list_get_item_by_index czyli możliwość pobrania n-tego elementu
	// a zatem.. lecimy po bandzie - sortowanie bąbelkowe :)

	int dirty;
	do {
		dirty = 0;
		for (int i = 0; i < list_count(proot) - 1; i++)
		{
			struct list_t* l1 = list_get_item_by_index(proot, i);
			struct list_t* l2 = list_get_item_by_index(proot, i + 1);

			// czy wykonujemy zamianę?
			if (strcmp(l1->pclient->surname, l2->pclient->surname) > 0 && order == SO_ASC ||
				strcmp(l1->pclient->surname, l2->pclient->surname) < 0 && order == SO_DESC)
			{
				struct client_t* temp = l1->pclient;
				l1->pclient = l2->pclient;
				l2->pclient = temp;

				dirty = 1;
			}

		}
	} while (dirty);

	// 
	return proot;
}


int main()
{
	struct list_t* plist = NULL;

	plist = list_add_end(plist, client_create("Hanna","Makowska","555111001"));
	plist = list_add_end(plist, client_create("Edyta","Koziel","555111002"));
	plist = list_add_end(plist, client_create("Agata","Karpinska","555111003"));
	plist = list_add_end(plist, client_create("Stanislaw","Krajewski","555111004"));
	plist = list_add_end(plist, client_create("Michal", "Kazmierczak", "555111005"));
	plist = list_add_end(plist, client_create("Szymon", "Marek", "555111006"));
	plist = list_add_end(plist, client_create("Konstanty", "Brzozowski", "555111007"));
	plist = list_add_end(plist, client_create("Karolina", "Sobolewska", "555111008"));
	plist = list_add_end(plist, client_create("Tomasz", "Jaworski", "555111009"));
	plist = list_add_end(plist, client_create("Klaudia", "Wojcik", "555111010"));
	plist = list_add_end(plist, client_create("Marta", "Golebiowska", "555111011"));
	plist = list_add_end(plist, client_create("Martyna", "Kozak", "555111012"));
	plist = list_add_end(plist, client_create("Katarzyna", "Zielinska", "555111013"));
	plist = list_add_end(plist, client_create("Weronika", "Blaszczyk", "555111014"));
	plist = list_add_end(plist, client_create("Mikolaj", "Malecki", "555111015"));
	plist = list_add_end(plist, client_create("Dominika", "Lukasik", "555111016"));
	plist = list_add_end(plist, client_create("Iga", "Kopec", "555111017"));
	plist = list_add_end(plist, client_create("Diana", "Marcinkowska", "555111018"));
	plist = list_add_end(plist, client_create("Weronika", "Kedzierska", "555111019"));
	plist = list_add_end(plist, client_create("Gabriela", "Witkowska", "555111020"));

	// cała lista
	list_show(plist);

	// usunięcie pozycji 7
	plist = list_delete_by_index(plist, 7);
	list_show(plist);

	// usunięcie Igi (imie) oraz Kozaka (nazwisko) z ignorowaniem wielkości liter
	plist = list_delete_by_name(plist, "igA");
	plist = list_delete_by_name(plist, "KoZAk");
	list_show(plist);

	// znajdowanie kontaktu po nazwisku/imieniu przy ignorowaniu wielości liter
	struct list_t* pitem = list_get_item_by_name(plist, "jAWoRSki");
	client_print(pitem->pclient);
	printf("\n");

	// sortowanie kontaktów
	plist = list_sort(plist, SO_ASC);
	list_show(plist);


	// zwalniamy całą pamięć
	list_free(plist);
    return 0;
}

