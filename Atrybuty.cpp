#pragma once
#include "Atrybuty.h"

using namespace std;


NodeAtrybutu* Atrybuty::getPoczatek() const {
    return poczatek;
}

NodeAtrybutu* Atrybuty::getKoniec() const {
    return koniec;
}

void Atrybuty::setPoczatek(NodeAtrybutu* nowyPoczatek) {
    poczatek = nowyPoczatek;
}

void Atrybuty::setKoniec(NodeAtrybutu* nowyKoniec) {
    koniec = nowyKoniec;
}

int Atrybuty::szukajDuplikatu(myString nazwa) const{
    if (poczatek == NULL) {
        return -1;
    }
    int indeksDuplikatu = 0;
    NodeAtrybutu* biezacy = poczatek;
    while (biezacy != NULL) {
        if (biezacy->stringKlucz == nazwa) {
            return indeksDuplikatu;
        }
        indeksDuplikatu++;
        biezacy = biezacy->nastepny;
    }
    return -1;
}

void Atrybuty::zastapDuplikat(int indeksDuplikatu,myString nowyKlucz,myString nowaWartosc) {
    NodeAtrybutu* biezacy = poczatek;

    for (int i = 0; i < indeksDuplikatu; i++) { //idziemy do odpowiedniego atrybutu
        biezacy = biezacy->nastepny;
    }

    biezacy->stringKlucz = nowyKlucz;
    biezacy->stringWartosc = nowaWartosc;
}

void Atrybuty::dodajKoniec(myString klucz, myString wartosc) {
    NodeAtrybutu* nowy = new NodeAtrybutu;
    nowy->stringKlucz = klucz;
    nowy->stringWartosc = wartosc;
    nowy->nastepny = NULL;
    if (koniec != NULL) {
        koniec->nastepny = nowy;
        nowy->poprzedni = koniec;
    }
    koniec = nowy;
    if (poczatek == NULL)
        poczatek = koniec;
}

void Atrybuty::wyswietlListe() const { //funkcja wylacznie do debugowania
    if (poczatek == NULL) {
        cout << "Lista atrybutow jest pusta";
        return;
    }
    NodeAtrybutu* biezacy = poczatek;
    while (biezacy != NULL) {
        cout << "KLUCZ:" << biezacy->stringKlucz.getString() << " WARTOSC:" << biezacy->stringWartosc.getString() << endl;
        biezacy = biezacy->nastepny;
    }
}

int Atrybuty::liczbaAtrybutow() const {
    if (this == NULL || poczatek == NULL) {
        return 0;
    }
    int licznik = 0;
    NodeAtrybutu* biezacy = poczatek;
    while (biezacy != NULL) {
        licznik++;
        biezacy = biezacy->nastepny;
    }
    return licznik;
}

myString Atrybuty::getKluczString(int indeks) const {
    if (poczatek == NULL || indeks < 0) {
        return 0;
    }
    NodeAtrybutu* biezacy = poczatek;
    for (int i = 0; i < indeks; i++) {
        biezacy = biezacy->nastepny;
        if (biezacy == NULL) {
            return 0;
        }
    }
    return biezacy->stringKlucz;
}

myString Atrybuty::getWartoscString(int indeks) const {
    if (poczatek == NULL || indeks < 0) {
        return 0;
    }
    NodeAtrybutu* biezacy = poczatek;
    for (int i = 0; i < indeks; i++) {
        biezacy = biezacy->nastepny;
        if (biezacy == NULL) {
            return 0;
        }
    }
    return biezacy->stringWartosc;
}

Atrybuty::~Atrybuty() {
    NodeAtrybutu* tymczasowy;
    while (poczatek != NULL) {
        tymczasowy = poczatek;
        poczatek = poczatek->nastepny;
        delete tymczasowy;
    }
    koniec = NULL;
}