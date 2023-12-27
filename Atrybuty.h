#pragma once
#include "myString.h"
#include <iostream>

using namespace std;

struct NodeAtrybutu {
    myString stringKlucz;
    myString stringWartosc;
    NodeAtrybutu* poprzedni;
    NodeAtrybutu* nastepny;
};

class Atrybuty {
    NodeAtrybutu* poczatek;
    NodeAtrybutu* koniec;
public:
    Atrybuty() { poczatek = NULL; koniec = NULL; }
    ~Atrybuty();
    void dodajKoniec(myString klucz, myString wartosc);
    int liczbaAtrybutow() const;
    myString getKluczString(int indeks) const;
    myString getWartoscString(int indeks) const;
    int szukajDuplikatu(myString nazwa) const;
    void zastapDuplikat(int indeksDuplikatu, myString nowyKlucz, myString nowaWartosc);
    NodeAtrybutu* getPoczatek() const;
    NodeAtrybutu* getKoniec() const;
    void setPoczatek(NodeAtrybutu* nowyPoczatek);
    void setKoniec(NodeAtrybutu* nowyKoniec);

    void wyswietlListe() const; //funkcja wylacznie do debugowania
};

