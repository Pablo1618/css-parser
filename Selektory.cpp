#pragma once
#include "Selektory.h"

using namespace std;

void Selektory::dodajPoczatek(myString selektor) {
    NodeSelektora* nowy = new NodeSelektora;
    nowy->stringSelektor = selektor;
    nowy->poprzedni = NULL;
    nowy->nastepny = poczatek;
    if (poczatek != NULL)
        poczatek->poprzedni = nowy;
    poczatek = nowy;
    if (koniec == NULL)
        koniec = poczatek;
}

myString Selektory::getSelektorString(int indeks) const {
;    if (poczatek == NULL || indeks < 0) {
        return 0;
    }
    NodeSelektora* biezacy = poczatek;
    for (int i = 0; i < indeks; i++) {
        biezacy = biezacy->nastepny;
        if (biezacy == NULL) {
            return 0;
        }
    }
    return biezacy->stringSelektor;
}

void Selektory::dodajKoniec(myString selektor) {
    NodeSelektora* nowy = new NodeSelektora;
    nowy->stringSelektor = selektor;
    nowy->nastepny = NULL;
    if (koniec != NULL) {
        koniec->nastepny = nowy;
        nowy->poprzedni = koniec;
    }
    koniec = nowy;
    if (poczatek == NULL)
        poczatek = koniec;
}

void Selektory::wyswietlListe() const { //funkcja wylacznie do debugowania
    if (this == NULL) {
        cout << "Lista selektorow jest pusta";
        return;
    }
    NodeSelektora* biezacy = poczatek;
    while (biezacy != NULL) {
        cout << biezacy->stringSelektor.getString() << endl;
        biezacy = biezacy->nastepny;
    }
}

int Selektory::liczbaSelektorow() const {
    if (this == NULL || poczatek == NULL) {
        return 0;
    }
    int licznik = 0;
    NodeSelektora* biezacy = poczatek;
    while (biezacy != NULL) {
        licznik++;
        biezacy = biezacy->nastepny;
    }
    return licznik;
}

Selektory::~Selektory() {

    NodeSelektora* tymczasowy;
    while (poczatek != NULL) {
        tymczasowy = poczatek;
        poczatek = poczatek->nastepny;
        delete tymczasowy;
    }
    koniec = NULL;
}