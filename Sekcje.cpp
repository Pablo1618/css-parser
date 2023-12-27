#pragma once
#include "Sekcje.h"

//liczba Node'ow sekcji w tablicy
#define T 8

using namespace std;

bool Sekcje::usunSekcje(int numerSekcji) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return false;
    }

    int indeksSekcjiBloku = 0;
    int minieteSekcje = 0;
    blok* biezacy = pierwszy;
    for (int i = 0; i < liczbaBlokow; i++) {
        minieteSekcje += biezacy->ileZajetych;
        if (minieteSekcje >= numerSekcji) {
            minieteSekcje -= biezacy->ileZajetych;
            indeksSekcjiBloku = numerSekcji - minieteSekcje - 1;
            biezacy->ileZajetych--;
            break;
        }
        biezacy = biezacy->nastepny;
    }

        for (int i = indeksSekcjiBloku; i < biezacy->ileZajetych; i++) {
            biezacy->tablicaSekcji[i] = biezacy->tablicaSekcji[i + 1];
        }

    liczbaSekcji--;

    if (biezacy->ileZajetych == 0) {
        if (liczbaBlokow == 1) { //jedyny blok
            
            delete[] biezacy;
            liczbaBlokow--;
            return true;
        }
        else if (liczbaBlokow > 1 && biezacy != pierwszy && biezacy != ostatni) { //blok gdzies w srodku
            biezacy->nastepny->poprzedni = biezacy->poprzedni;
            biezacy->poprzedni->nastepny = biezacy->nastepny;
        }
        else if (liczbaBlokow > 1 && biezacy == pierwszy) { //pierwszy blok
            pierwszy = biezacy->nastepny;
        }
        else if (liczbaBlokow > 1 && biezacy == ostatni) { //ostatni blok
            ostatni->poprzedni->nastepny = NULL;
            ostatni = ostatni->poprzedni;
        }

        delete[] biezacy;
        liczbaBlokow--;
        return true;
    }

    return true;
}

void Sekcje::dodajKoniec(Selektory* selektory) {
    //dodaj zwykla sekcje (nieglobalna)

    if (liczbaSekcji == 0) { //pierwszy blok
        blok* nowyBlok = new blok;
        liczbaBlokow++;
        pierwszy = nowyBlok;
        ostatni = nowyBlok;
        nowyBlok->tablicaSekcji[0].selektory = selektory;
        nowyBlok->tablicaSekcji[0].sekcjaGlobalna = false;
        liczbaSekcji++;
        nowyBlok->ileZajetych = 1;
        return;
    }
    else if(ostatni->ileZajetych < T) { //dodanie sekcji do istniejacego bloku
        blok* biezacy = ostatni;
        for (int i = 0; i < liczbaBlokow; i++) {
            if (biezacy->ileZajetych < T) {
                biezacy->tablicaSekcji[biezacy->ileZajetych].selektory = selektory;
                biezacy->tablicaSekcji[biezacy->ileZajetych].sekcjaGlobalna = false;
                biezacy->ileZajetych++;
                liczbaSekcji++;
                return;
            }
            biezacy = biezacy->poprzedni;
        }
    }
    else{ //tworzenie nowego bloku, bo wszystkie sa zapelnione
        blok* nowyBlok = new blok;
        liczbaBlokow++;
        nowyBlok->tablicaSekcji[0].selektory = selektory;
        nowyBlok->tablicaSekcji[0].sekcjaGlobalna = false;
        nowyBlok->poprzedni = ostatni;
        ostatni->nastepny = nowyBlok;
        ostatni = nowyBlok;
        liczbaSekcji++;
        nowyBlok->ileZajetych = 1;
        return;
    }
}

void Sekcje::dodajKoniec(Atrybuty* globalneAtrybuty) {
    //dodajemy sekcje bez selektorow (sekcja globalna)

    if (liczbaSekcji == 0) { //pierwszy blok
        blok* nowyBlok = new blok;
        liczbaBlokow++;
        pierwszy = nowyBlok;
        ostatni = nowyBlok;
        nowyBlok->tablicaSekcji[0].atrybuty = globalneAtrybuty;
        nowyBlok->tablicaSekcji[0].sekcjaGlobalna = true;
        liczbaSekcji++;
        nowyBlok->ileZajetych = 1;
        return;
    }
    else if (ostatni->ileZajetych < T) { //dodanie sekcji do istniejacego bloku
        blok* biezacy = ostatni;
        for (int i = 0; i < liczbaBlokow; i++) {
            if (biezacy->ileZajetych < T) {
                biezacy->tablicaSekcji[biezacy->ileZajetych].atrybuty = globalneAtrybuty;
                biezacy->tablicaSekcji[biezacy->ileZajetych].sekcjaGlobalna = true;
                biezacy->ileZajetych++;
                liczbaSekcji++;
                return;
            }
            biezacy = biezacy->poprzedni;
        }
    }
    else { //tworzenie nowego bloku, bo wszystkie sa zapelnione
        blok* nowyBlok = new blok;
        liczbaBlokow++;
        nowyBlok->tablicaSekcji[0].atrybuty = globalneAtrybuty;
        nowyBlok->tablicaSekcji[0].sekcjaGlobalna = true;
        nowyBlok->poprzedni = ostatni;
        ostatni->nastepny = nowyBlok;
        ostatni = nowyBlok;
        liczbaSekcji++;
        nowyBlok->ileZajetych = 1;
        return;
    }
}

bool Sekcje::czySekcjaGlobalna(int numerSekcji) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return false;
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);
    return sekcja->sekcjaGlobalna; //true albo false
}

void Sekcje::dodajAtrybutyDoOstatniej(Atrybuty* atrybuty) {

    blok* biezacy = ostatni;
    biezacy->tablicaSekcji[biezacy->ileZajetych - 1].atrybuty = atrybuty;

}

NodeSekcji* Sekcje::idzDoSekcji(int numerSekcji) {
    int minieteSekcje = 0;
    blok* biezacy = pierwszy;
    for (int i = 0; i < liczbaBlokow; i++) {
        minieteSekcje += biezacy->ileZajetych;
        if (minieteSekcje >= numerSekcji) {
            minieteSekcje -= biezacy->ileZajetych;
            int indeksSekcjiBloku = numerSekcji - minieteSekcje - 1;
            return &(biezacy->tablicaSekcji[indeksSekcjiBloku]);
        }
        biezacy = biezacy->nastepny;
    }
    return NULL;
}

int Sekcje::ileAtrybutow(int numerSekcji) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return -1;
    }
    
    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);
    return sekcja->atrybuty->liczbaAtrybutow();
}

int Sekcje::ileSelektorow(int numerSekcji) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return -1; //sekcja o takim indeksie nie istnieje
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);

    return sekcja->selektory->liczbaSelektorow();
}

myString Sekcje::getNazwaSelektora(int numerSekcji, int numerSelektora){

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);

    return sekcja->selektory->getSelektorString(numerSelektora - 1); //robimy -1, bo getSelektoraString przyjmuje indeks (iteracja od 0), a nie numer
}

myString Sekcje::getWartoscAtrybutu(int numerSekcji, int indeksAtrybutu) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return NULL; //sekcja o takim indeksie nie istnieje
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);

    return sekcja->atrybuty->getWartoscString(indeksAtrybutu);

}

int Sekcje::liczAtrybutyNazwa(myString nazwa) const {

    int liczba = 0;

    blok* biezacy = pierwszy;

    for (int i = 0; i < liczbaBlokow; i++) { //iteracja przez bloki

        for (int j = 0; j < biezacy->ileZajetych ; j++) { //iteracja przez tablice w bloku (sekcje)

            for (int g = 0; g < biezacy->tablicaSekcji[j].atrybuty->liczbaAtrybutow(); g++) { //iteracja przez liste atrybutow

                if (biezacy->tablicaSekcji[j].atrybuty->getKluczString(g) == nazwa) {
                liczba++;
                }
            }
        }
        biezacy = biezacy->nastepny;
    }
    return liczba;
}

int Sekcje::liczSelektoryNazwa(myString nazwa) const {
    int liczba = 0;

    if (pierwszy == NULL) {
        return 0;
    }

    blok* biezacy = pierwszy;

    for (int i = 0; i < liczbaBlokow; i++) { //iteracja przez bloki

        for (int j = 0; j < biezacy->ileZajetych ; j++) { //iteracja przez tablice w bloku (sekcje)

            if (biezacy->tablicaSekcji[j].sekcjaGlobalna == false) {
                for (int g = 0; g < biezacy->tablicaSekcji[j].selektory->liczbaSelektorow(); g++) {

                    if (biezacy->tablicaSekcji[j].selektory->getSelektorString(g) == nazwa) {
                        liczba++;
                        break;
                    }
                }
            }
        }
        biezacy = biezacy->nastepny;
    }
    return liczba;
}

//z, E, n – wypisz wartoœæ atrybutu o nazwie n dla selektora z, w przypadku wielu wyst¹pieñ selektora z bierzemy ostatnie.W przypadku braku pomiñ;
myString Sekcje::znajdzWartoscAtrybutuSelektora(myString nazwaAtrybutu, myString nazwaSelektora) const {

    char n[] = { 'X' };
    myString nieZnalezionoString = n;
    blok* biezacy = ostatni;

    if (biezacy == NULL) {
        return nieZnalezionoString;
    }

    for (int i = 0; i < liczbaBlokow; i++) { //iteracja przez bloki (od ostatniego do pierwszego)

        for (int j = biezacy->ileZajetych - 1; j >= 0; j--) { //iteracja przez tablice w bloku (sekcje)

            if (biezacy->tablicaSekcji[j].sekcjaGlobalna == false) {
                for (int g = 0; g < biezacy->tablicaSekcji[j].selektory->liczbaSelektorow(); g++) {

                    if (biezacy->tablicaSekcji[j].selektory->getSelektorString(g) == nazwaSelektora) {
                        NodeAtrybutu* aktualny = biezacy->tablicaSekcji[j].atrybuty->getPoczatek();
                        while (aktualny != NULL) {
                            if (aktualny->stringKlucz == nazwaAtrybutu) {
                                 return aktualny->stringWartosc; //znaleziono atrybut o podanej nazwie dla danego selektora
                            }
                            if (aktualny == biezacy->tablicaSekcji[j].atrybuty->getKoniec()) { //nie znaleziono atrybutu
                            return nieZnalezionoString;
                            }
                            aktualny = aktualny->nastepny;
                        }
                    }
                }
            }
        }
        biezacy = biezacy->poprzedni;
    }

    return nieZnalezionoString;
}

myString Sekcje::getNazwaAtrybutu(int numerSekcji, int indeksAtrybutu) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return NULL; //sekcja o takim indeksie nie istnieje
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);

    return sekcja->atrybuty->getKluczString(indeksAtrybutu);
}

int Sekcje::ileSekcji() const {

    return liczbaSekcji;

}

int Sekcje::znajdzAtrybutNazwa(int numerSekcji, myString nazwa) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return -1; //sekcja o takim indeksie nie istnieje
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);
    for (int i = 0; i < sekcja->atrybuty->liczbaAtrybutow(); i++) {
        if (getNazwaAtrybutu(numerSekcji, i) == nazwa) {
            return i;
        }
    }
    
    sekcja = idzDoSekcji(numerSekcji+1);
    return -1;
}

bool Sekcje::usunAtrybutSekcji(int numerSekcji, int indeksAtrybutu) {

    if (numerSekcji < 1 || numerSekcji > liczbaSekcji) {
        return false; //sekcja o takim indeksie nie istnieje
    }

    NodeSekcji* sekcja = idzDoSekcji(numerSekcji);

    NodeAtrybutu* aktualny = sekcja->atrybuty->getPoczatek();

    for (int i = 0; i < indeksAtrybutu; i++) { //idziemy do odpowiedniego atrybutu
        aktualny = aktualny->nastepny;
    }

    if(sekcja->atrybuty->liczbaAtrybutow() == 1){ //jedyny atrybut (jest poczatkiem i koncem)
        delete aktualny;
        aktualny = NULL;
        usunSekcje(numerSekcji);
        return true;
    }
    else if (sekcja->atrybuty->liczbaAtrybutow() > 1 && aktualny == sekcja->atrybuty->getPoczatek()) { //pierwszy atrybut
        sekcja->atrybuty->setPoczatek(aktualny->nastepny);
        aktualny->nastepny->poprzedni = NULL;
        delete aktualny;
        return true;
    }
    else if (sekcja->atrybuty->liczbaAtrybutow() > 1 && aktualny == sekcja->atrybuty->getKoniec()) { //ostatni atrybut
        sekcja->atrybuty->setKoniec(aktualny->poprzedni);
        aktualny->poprzedni->nastepny = NULL;
        delete aktualny;
        return true;
    }
    else if (sekcja->atrybuty->liczbaAtrybutow() > 1 && aktualny != sekcja->atrybuty->getKoniec() && aktualny != sekcja->atrybuty->getPoczatek()) { //atrybut gdzies w srodku
        aktualny->poprzedni->nastepny = aktualny->nastepny;
        aktualny->nastepny->poprzedni = aktualny->poprzedni;
        delete aktualny;
        return true;
    }

return false;
}
