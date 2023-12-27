#pragma once
#include "myString.h"
#include "Selektory.h"
#include "Atrybuty.h"
#include <iostream>

//liczba Node'ow sekcji w tablicy
#define T 8

using namespace std;

struct NodeSekcji {

    Selektory* selektory;
    Atrybuty* atrybuty;
    char sekcjaGlobalna;
};
    
struct blok {
    NodeSekcji tablicaSekcji[T];
    int ileZajetych;
    blok* poprzedni;
    blok* nastepny;
};


    
struct Sekcje {

    blok* pierwszy;
    blok* ostatni;
    int liczbaSekcji = 0;
    int liczbaBlokow = 0;

    Sekcje() { pierwszy = NULL; ostatni = NULL; liczbaSekcji = 0; }

    myString getNazwaSelektora(int numerSekcji, int numerSelektora);
    myString getWartoscAtrybutu(int numerSekcji, int indeksAtrybutu);
    myString getNazwaAtrybutu(int numerSekcji, int indeksAtrybutu);
    myString znajdzWartoscAtrybutuSelektora(myString nazwaAtrybutu, myString nazwaSelektora) const;
    int znajdzAtrybutNazwa(int numerSekcji, myString nazwa);
    NodeSekcji* idzDoSekcji(int numerSekcji);

    bool czySekcjaGlobalna(int numerSekcji);
    bool usunSekcje(int numerSekcji);
    bool usunAtrybutSekcji(int numerSekcji, int indeksAtrybutu);
    void dodajKoniec(Selektory* selektory);
    void dodajKoniec(Atrybuty* globalneAtrybuty);
    void dodajAtrybutyDoOstatniej(Atrybuty* atrybuty);

    int ileSekcji() const;
    int ileAtrybutow(int numerSekcji);
    int ileSelektorow(int numerSekcji);
    int liczAtrybutyNazwa(myString nazwa) const;
    int liczSelektoryNazwa(myString nazwa) const;
};

