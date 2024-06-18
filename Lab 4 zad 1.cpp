//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 4.1
// Odwrotna Notacja Polska
//
//  WCY21IX4S0  Miksiewicz Pawel
//============================================================================

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

//DEKLARACJA PODSTAWOWEJ LISTY
struct Lista
{
  char data;
  struct Lista *nastepny;
};

//OKRESLENIE PRIORYTETU NADAWANIU ZNAKOM
int Priorytet(char c)
{ 
	if (c == '/' || c == '*' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

//FUNKCJA KTORA DODAJE LICZBY NA POCZATEK LISTY (STOSU - W TYM ZADANIU), ODPOWIEDNIK FUNKCJI W STOSIE STOS.PUSH()
void DodajNaPoczatek(struct Lista** poczatek, char nowy)
{
    struct Lista* nowa_lista = (struct Lista*) malloc(sizeof(struct Lista));
    nowa_lista->data = nowy;
    nowa_lista->nastepny = (*poczatek);
    (*poczatek) = nowa_lista;
}

//FUNKCJA NA USUWANIE "PIERWSZEGO ELEMENTU", CZYLI WIERZCHOLKA, ODPOWIEDNIK FUNKCJI W STOSIE STOS.POP()
void POP(struct Lista** poczatek)
{
    struct Lista *nc;
    if (poczatek == NULL || *poczatek == NULL)
    {
        return;
    }
    nc = *poczatek;
    *poczatek=(*poczatek)->nastepny;
    free(nc);
}

//FUNKCJA SPRAWDZAJACA CZY STRUKTURA JEST PUSTA, ODPOWIEDNIK FUNKCJI W STOSIE STOS.EMPTY()
int CzyPusta(struct Lista* Lista)
{
	if (Lista == NULL) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

//FUNKCJA ZWRACA WIERZCHOLEK STOSU, WLASNORECZNIE NAPISANA FUNKCJA STOS.TOP()
char TOP(struct Lista* Lista)
{
    return Lista->data;
}

//FUNKCJA NA LICZENIE ONP - ODWROCONA NOTACJA POLSKA
void ONP(string tekst)
{
	struct Lista* dana = NULL;
	int l = tekst.length();	
	string wynik;
		
	
	for(int i=0; i<l; i++)
	{	
		if ((tekst[i] >= 'a' && tekst[i] <= 'z') || (tekst[i] >= 'A' && tekst[i] <= 'Z') || (tekst[i] >= '0' && tekst[i] <= '9'))
		{
			wynik += tekst[i];
		}
		else if(tekst[i] == '(')
		{
			DodajNaPoczatek(&dana,'(');
		}
		else if(tekst[i] == ')')
		{
			while(TOP(dana) != '(')
			{
				char c = TOP(dana);
				wynik += c;
				POP(&dana);
			}
			if(TOP(dana) == '(')
			{
				char c = TOP(dana);
				POP(&dana);
			}
		}
		else 
		{
			while(CzyPusta(dana) == 0 && Priorytet(tekst[i]) <= Priorytet(TOP(dana)))
			{
			char c = TOP(dana);
			wynik += c;
			POP(&dana);
			}
		DodajNaPoczatek(&dana,tekst[i]);
		}
	}
	
	while (CzyPusta(dana) == 0)
	{
		char c = TOP(dana);
		wynik += c;
		POP(&dana);
	}
	cout << wynik;
}

//MAIN, WYLOWANIE FUNKCJI
int main()
{
	cout << "Podaj wyrazenie do przeksztalcenia go na ONP" << endl;
	string wyrazenie;
	cin >> wyrazenie;
	
	cout << "Wynik" << endl;
	ONP(wyrazenie);
	
return 0;
}
