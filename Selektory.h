#pragma once
#include "myString.h"
#include <iostream>

using namespace std;

struct NodeSelektora {
    myString stringSelektor;
    NodeSelektora* poprzedni;
    NodeSelektora* nastepny;
};

class Selektory {
public:
    NodeSelektora* poczatek;
    NodeSelektora* koniec;
    Selektory() { poczatek = NULL; koniec = NULL; }
    void dodajPoczatek(myString selektor);
    void dodajKoniec(myString selektor);
    void wyswietlListe() const;
    int liczbaSelektorow() const;
    myString getSelektorString(int indeks) const;
    ~Selektory();
};

