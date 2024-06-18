//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 4.2
// Dodawanie duøych liczb przy wykorzystaniu struktury stosu w postaci wskaünikowej
//
//  WCY21IX4S0  Miksiewicz Pawel
//============================================================================

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//DEKLARACJA PODSTAWOWEJ LISTY
struct Lista 
{
    int data;
    struct Lista* nastepny;
};

//FUNKCJA KTORA DODAJE LICZBY NA POCZATEK LISTY (STOSU - W TYM ZADANIU)
void DodajNaPoczatek(struct Lista** poczatek, int nowy)
{
    struct Lista* nowa_lista = (struct Lista*) malloc(sizeof(struct Lista));
    nowa_lista->data = nowy;
    nowa_lista->nastepny = (*poczatek);
    (*poczatek) = nowa_lista;
}

//WYPISANIE DO KONSOLI CALEJ LISTY
void Wypisz(struct Lista* Lista)
{
    while (Lista != NULL)// DO MOMENTU KIEDY LISTA NIE BEDZIE NULLEM (NULL - PUSTA) WYPISZE WSZYSKIE ELEMENTY
    {
        cout << Lista->data;
        Lista = Lista->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
    }
    cout << endl;
}
 
//DEKLARACJA LISTY KTORA JEST ODWROCENIEM PODSTAWOWEJ LISTY
struct Lista* OdwrocLista(struct Lista* list)
{
    struct Lista *poprzedni = NULL;
    struct Lista *obecny = list;
    struct Lista *nastepny = NULL;
    
    while (obecny != NULL) 
	{
        nastepny = obecny->nastepny;
        obecny->nastepny = poprzedni;
        poprzedni = obecny;
        obecny = nastepny;
    }
    return poprzedni;
}

//DEKLARACJA LISTY KTORA WYKONA DODAWANIE DWOCH LIST I UTWORZY NOWA LISTE
struct Lista* PolaczListy(Lista* PierwszaLista, Lista* DrugaLista)
{
    PierwszaLista = OdwrocLista(PierwszaLista);
    DrugaLista = OdwrocLista(DrugaLista);
 
    int licznik = 0;
    struct Lista *poczatek = NULL;
    struct Lista *poprzedni = NULL;
    struct Lista* suma = NULL;
    
    while (PierwszaLista != NULL || DrugaLista != NULL || licznik == 1)
    {
        int liczba = licznik;
        if (PierwszaLista)
        {
        	liczba = liczba + PierwszaLista->data;	
		}
        if (DrugaLista)
        {
        	liczba = liczba + DrugaLista->data;
		}
		
        licznik = liczba / 10;
        liczba = liczba % 10;
        
        struct Lista* NowaLista = (struct Lista*) malloc(sizeof(struct Lista)); //DEKLARACJA PAMIECI NOWE STRUKTURY
        NowaLista->data = liczba;
        NowaLista->nastepny = suma;
        suma = NowaLista;
 
        if (PierwszaLista)
        {
            PierwszaLista = PierwszaLista->nastepny;	
		}
        if (DrugaLista)
        {
        	DrugaLista = DrugaLista->nastepny;
		}
    }
 
    return suma;
}
 
int main()
{
	//DEKLARACJA NASZYCH 2 LIST KTORE ODPOWIADAJA ZA CALA LICZBE WPISANA
    struct Lista* PierwszaLista = NULL;
    struct Lista* DrugaLista = NULL;
 
	//WPISANIE ZMIENNYCH
 	int PierwszaLiczba, DrugaLiczba;
 	cout << "Podaj pierwsza liczbe" << endl;
 	cin >> PierwszaLiczba;
 	cout << "Podaj druga liczbe" << endl;
 	cin >> DrugaLiczba;
 	cout << endl;
 	
 	int zero1 = PierwszaLiczba;
 	int zero2 = DrugaLiczba;
 	//RODZIELANIE INTA BY MOC DODAC GO ROZLOZYC NA POJEDYNCZE LICZBY, NP 123, RODZIELI GO NA 3 I DODA DO LISTY, POTEM 2 I DODA, NA KONIEC 1 I DODA
 	while(PierwszaLiczba != 0)
 	{
 	int modulo1 = PierwszaLiczba % 10;
 	DodajNaPoczatek(&PierwszaLista, modulo1);
 	PierwszaLiczba /= 10;
	}
 	
 	while(DrugaLiczba != 0)
 	{
 	int modulo2 = DrugaLiczba % 10;
 	DodajNaPoczatek(&DrugaLista, modulo2);
 	DrugaLiczba /= 10;
	}
	
	//WYPISANIE ZMIENNYCH
	cout << "Dodawanie" << endl;
	if(zero1 == 0)
	{
		cout << "0" << endl;
	}
	else
	{
		Wypisz(PierwszaLista);	
	}
	
 	cout << "+";
 	if(zero2 == 0)
 	{
 		cout << "0" << endl;	
	}
	else 
	{
		Wypisz(DrugaLista);	
	}
	
	//WYNIK DZIALANIA
 	cout<<"--------" << endl;
    struct Lista* wynik = PolaczListy(PierwszaLista, DrugaLista);
    if(wynik == 0)
    {
    	cout << "0" << endl;
	}
	else
	{
    	Wypisz(wynik);	
	}
 
    return 0;
}
