#include <iostream>
#include "main.h"
#include "myString.h"
#include "Sekcje.h"
#include "Selektory.h"
#include "Atrybuty.h"

using namespace std;

static bool zakonczonoProgram = false;


int tablicaCharNaInt(char* napis) {

    int wynik = 0;

    for(int i = 0; napis[i] != '\0'; ++i) {
        wynik = wynik * 10 + napis[i] - '0';
    }
    return wynik;
}

bool sprawdzCzyCyfra(char* napis) {

    if (napis[0] >= '0' && napis[0] <= '9') {
        return true;
    }
    else {
        return false;
    }
}

bool czyRozpoczetoSekcjeKomend(char znak, int* licznikZnakow) {

    char koniec[4] = { '?' , '?' , '?' , '?' };

    if (znak == koniec[*licznikZnakow]) {
        (*licznikZnakow)++;
    }
    else {
        (*licznikZnakow) = 0;
    }

    if (*licznikZnakow != 4) {
        return false;
    }
    else {
        return true;
    }
}

void rozdzielKomende(int* element, myString komendaStr, myString* pierwszyElement, myString* drugiElement, myString* trzeciElement) {

    //rozdzielenie komendy na 3 stringi
    for (int i = 0; i < komendaStr.jakaDlugosc(); i++) {
        if (komendaStr.jakaLitera(i) != ',') {
            switch (*element) {
            case 1:
                pierwszyElement->dodajZnak(komendaStr.jakaLitera(i));
                break;
            case 2:
                drugiElement->dodajZnak(komendaStr.jakaLitera(i));
                break;
            case 3:
                trzeciElement->dodajZnak(komendaStr.jakaLitera(i));
                break;
            }
        }
        else if (komendaStr.jakaLitera(i) == ',') {
            (*element)++;
        }
    }
}

void wykonajKomende(myString komendaStr, Sekcje* sekcje) {

    int element = 1;
    myString pierwszyElement;
    myString drugiElement;
    myString trzeciElement;

    //rozdzielenie komendy na 3 oddzielne stringi (pomiedzy przecinkami)
    rozdzielKomende(&element, komendaStr, &pierwszyElement, &drugiElement, &trzeciElement);

    //i,A,? - wypisz liczbê atrybutów dla sekcji nr i, jeœli nie ma takiego bloku lub sekcji pomiñ;
    if (sprawdzCzyCyfra(pierwszyElement.getString()) == true && drugiElement.jakaLitera(0) == 'A' && trzeciElement.jakaLitera(0) == '?') {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());

        int liczbaAtrybutow = sekcje->ileAtrybutow(numerSekcji);

        if (liczbaAtrybutow != -1) {
            cout << numerSekcji << ",A,? == ";
            cout << liczbaAtrybutow << endl;
        }
    }
        
    // i,S,? – wypisz liczbê selektorów dla sekcji nr i (numery zaczynaj¹ siê od 1), jeœli nie ma takiego bloku pomiñ;
    else if (sprawdzCzyCyfra(pierwszyElement.getString()) == true && drugiElement.jakaLitera(0) == 'S' && trzeciElement.jakaLitera(0) == '?') {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());
        if (sekcje->czySekcjaGlobalna(numerSekcji) == false) {

            int liczbaSelektorow = sekcje->ileSelektorow(numerSekcji);

            if (liczbaSelektorow != -1) {
                cout << numerSekcji << ",S,? == ";
                cout << liczbaSelektorow << endl;
            }
        }
        else {
            cout << numerSekcji << ",S,? == 0" << endl;
        }
    }

    // i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynaj¹ siê od 1) jeœli nie ma sekcji lub selektora pomiñ;
    else if (sprawdzCzyCyfra(pierwszyElement.getString()) && drugiElement.jakaLitera(0) == 'S' && trzeciElement.jakaLitera(0)>=0 && sprawdzCzyCyfra(trzeciElement.getString())) {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());
        int numerSelektora = tablicaCharNaInt(trzeciElement.getString());

        if (sekcje->czySekcjaGlobalna(numerSekcji) == false && numerSelektora != 0) {

            int ileSelektorow = sekcje->ileSelektorow(numerSekcji);

            if (ileSelektorow != -1 && numerSelektora <= ileSelektorow) { //czy sekcja i selektor istnieje
                cout << numerSekcji << ",S," << numerSelektora << " == ";
                cout << sekcje->getNazwaSelektora(numerSekcji, numerSelektora).getString() << endl; // robimy -1 bo nr selektorow liczymy od 1
            }
        }
        else {
            //pomijamy - bo nie ma selektora (sekcja jest globalna)
        }
    }

    // i,A,n – wypisz dla i-tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;
    else if (drugiElement.jakaLitera(0) == 'A' && trzeciElement.jakaLitera(0) != '?') {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());
        myString nazwaAtrybutu = trzeciElement;

        int indeksAtrybutu = sekcje->znajdzAtrybutNazwa(numerSekcji, nazwaAtrybutu);

        if (indeksAtrybutu != -1) { //czy sekcja istnieje
            cout << numerSekcji << ",A," << nazwaAtrybutu.getString() << " == ";
            cout << sekcje->getWartoscAtrybutu(numerSekcji, indeksAtrybutu).getString() << endl;
        }
    }

    // n,A,? – wypisz ³¹czn¹(dla wszystkich bloków) liczbê wyst¹pieñ atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostaæ usuniête na etapie wczytywania).Mo¿liwe jest 0;
    else if (sprawdzCzyCyfra(pierwszyElement.getString())==false && drugiElement.jakaLitera(0) == 'A' && trzeciElement.jakaLitera(0) == '?') {
        myString nazwaAtrybutu = pierwszyElement;
        cout << pierwszyElement.getString() << ",A,? == " << sekcje->liczAtrybutyNazwa(nazwaAtrybutu) << endl;
    }

    // i,D,* - usuñ ca³¹ sekcjê nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;
    else if (drugiElement.jakaLitera(0) == 'D' && trzeciElement.jakaLitera(0) == '*') {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());

        if (sekcje->usunSekcje(numerSekcji) == true) {
            cout << numerSekcji << ",D,*" << " == deleted" << endl;
        }
    }

    // z,S,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ selektora z. Mo¿liwe jest 0;
    else if (sprawdzCzyCyfra(pierwszyElement.getString()) == false && drugiElement.jakaLitera(0) == 'S' && trzeciElement.jakaLitera(0) == '?') {
        cout << pierwszyElement.getString() << ",S,? == " << sekcje->liczSelektoryNazwa(pierwszyElement) << endl;
    }

    //z,E,n – wypisz wartoœæ atrybutu o nazwie n dla selektora z, w przypadku wielu wyst¹pieñ selektora z bierzemy ostatnie.W przypadku braku pomiñ;
    else if (sprawdzCzyCyfra(pierwszyElement.getString()) == false && drugiElement.jakaLitera(0) == 'E' && sprawdzCzyCyfra(trzeciElement.getString()) == false) {
        myString nazwaSelektora = pierwszyElement;
        myString nazwaAtrybutu = trzeciElement; 

        myString wartoscAtrybutu = sekcje->znajdzWartoscAtrybutuSelektora(nazwaAtrybutu, nazwaSelektora);
        if (wartoscAtrybutu.jakaLitera(0) != 'X') {
            cout << nazwaSelektora.getString() << ",E," << nazwaAtrybutu.getString() << " == " << wartoscAtrybutu.getString() << endl;
        }
    }

    //i,D,n – usuñ z i-tej sekcji atrybut o nazwie n, jeœli w wyniku operacji pozostaje pusta sekcja powinna zostaæ równie¿ usuniêta(wraz z ew.selektorami), po poprawnym wykonaniu wypisz deleted.
    else if (sprawdzCzyCyfra(pierwszyElement.getString()) == true && drugiElement.jakaLitera(0) == 'D' && trzeciElement.jakaLitera(0)!='*') {
        int numerSekcji = tablicaCharNaInt(pierwszyElement.getString());
        int indeksAtrybutuDoUsuniecia = sekcje->znajdzAtrybutNazwa(tablicaCharNaInt(pierwszyElement.getString()), trzeciElement);
        if (indeksAtrybutuDoUsuniecia != -1) {
            sekcje->usunAtrybutSekcji(numerSekcji, indeksAtrybutuDoUsuniecia);
            cout << numerSekcji << ",D," << trzeciElement.getString() << " == deleted" << endl;
        }
    }

    pierwszyElement.usunString();
    drugiElement.usunString();
    trzeciElement.usunString();
}

void obslugaKomend(Sekcje* sekcje) {

    myString bufor;
    char znak = 0;

    while (znak != EOF) {
        znak = getchar();
        if (znak != '\n') {
            bufor.dodajZnak(znak);
        }
        else { // wcisnieto enter
            if (bufor.jakaLitera(0) == '*') { // komenda ****
                bufor.usunString();
                return; // czyli powrot do funkcji wczytujSelektory() (bo ona wywolala funkcje obslugaKomend)
            }
            if (bufor.jakaLitera(0) == '?') { // komenda ????
                cout << "? == ";
                cout << sekcje->ileSekcji() << endl;
            }
            else {
                wykonajKomende(bufor, sekcje);
            }
            bufor.wyczyscString(); // zaczyna sie nowa linijka (nowa komenda) wiec czyscimy bufor
        }
    }

    if (bufor.jakaLitera(0) == '?' && znak == EOF) { // jesli ostatnie polecenie to znak '?' (z dolaczonym znakiem EOF)
        cout << "? == ";
        cout << sekcje->ileSekcji() << endl;
    }

    //skonczylo sie wejscie
    zakonczonoProgram = true;
}

void wczytujAtrybuty(Sekcje* sekcje, bool czyGlobalne) {

    int indeksDuplikatu = 0;
    bool pomijajSpacje = true;
    myString buforowyString;
    myString buforKlucz;
    myString buforWartosc;
    Atrybuty* atrybuty = new Atrybuty;
    bool koniecAtrybutow = false;
    bool poDwukropku = false;
    char koniec[4] = { '?' , '?' , '?' , '?' }; //ciag znakow rozpoczynajacy sekcje komend
    char znak = 0;

    do {
        znak = getchar();

        if (znak != NULL && znak >= ' ') {
            switch (znak) {
            case '\t': //tabulator
                    //pomijamy tabulator przed nazwa klucza atrybutu
                break;
            case ' ': //spacja
                if (pomijajSpacje == true) {
                    //pomijamy spacje przed nazwa klucza atrybutu
                    break;
                }
                else {
                    buforowyString.dodajZnak(znak);
                }
                break;
            case ':':
                poDwukropku = true;
                pomijajSpacje = false;
                buforKlucz = buforowyString;
                buforowyString.nowyString();
                break;
            case ';':
                poDwukropku = false;
                pomijajSpacje = true;
                buforWartosc = buforowyString; //spacja na poczatku
                buforowyString.nowyString(); //tworzymy nowy string dla nastepnego atrybutu
                indeksDuplikatu = atrybuty->szukajDuplikatu(buforKlucz);
                if (indeksDuplikatu != -1) { //gdy nie ma duplikatu funkcja zwraca -1
                    atrybuty->zastapDuplikat(indeksDuplikatu, buforKlucz, buforWartosc);
                }
                else {
                    atrybuty->dodajKoniec(buforKlucz, buforWartosc);
                }
                break;
            case '}':
                if (pomijajSpacje == false) { //wyjatek - po ostatnim atrybucie nie ma srednika
                    buforWartosc = buforowyString;
                    indeksDuplikatu = atrybuty->szukajDuplikatu(buforKlucz);
                    if (indeksDuplikatu != -1) {
                        atrybuty->zastapDuplikat(indeksDuplikatu, buforKlucz, buforWartosc);
                    }
                    else {
                        atrybuty->dodajKoniec(buforKlucz, buforWartosc);
                    }
                }
                koniecAtrybutow = true;
                if (czyGlobalne == false) {
                    sekcje->dodajAtrybutyDoOstatniej(atrybuty);
                }
                else if (czyGlobalne == true) {
                    sekcje->dodajKoniec(atrybuty);
                }
                break;
            case '\n':
                //entery ignorujemy
                break;
            default:
                buforowyString.dodajZnak(znak);
                break;
            }
        }
    } while (koniecAtrybutow == false);

    buforowyString.usunString();
}

void wczytujSelektory(Sekcje* sekcje) {

    Selektory* selektory = new Selektory;
    myString buforowyString;

    bool koniecNazwSelektorow = false;
    int ktoraLiteraSelektora = 0;
    char poprzedniZnak = 0;
    int licznikZnakow = 0;
    char znak = 0;

    do {
        znak = getchar();
        if (znak != NULL && znak >= ' ' && znak != '\t') {
            switch (znak) {
            case ',':
                selektory->dodajKoniec(buforowyString);
                buforowyString.nowyString();
                break;
            case '{':
                if (ktoraLiteraSelektora > 1) {
                    buforowyString.usunSpacjeNaKoncu(); //jesli na koncu selektora jest spacja,a klamerka { bedzie dopiero w nastepnej linijce

                    if (buforowyString.jakaDlugosc() > 0) {
                        selektory->dodajKoniec(buforowyString);
                        sekcje->dodajKoniec(selektory);
                        koniecNazwSelektorow = true;
                        wczytujAtrybuty(sekcje, false);
                        return; //return do funkcji main
                    }
                }
                else if (ktoraLiteraSelektora == 0 || ktoraLiteraSelektora == 1) { //atrybuty globalne bez selektora { }
                    koniecNazwSelektorow = true;
                    buforowyString.nowyString();

                    delete selektory;
                    wczytujAtrybuty(sekcje, true);
                    return; //return do funkcji main
                }
                break;
            case ' ':
                if (ktoraLiteraSelektora == 0) {
                    ktoraLiteraSelektora = -1; //cofamy litere, w ten sposob pozbywamy sie spacji
                }
                else {
                    if (poprzedniZnak != ',') {
                        buforowyString.dodajZnak(' ');
                    }
                }
                break;
            case '\n':
                //pomijamy znak enter
                break;
            default:
                buforowyString.dodajZnak(znak);
                break;
            }
            ktoraLiteraSelektora++;
        }

        if (czyRozpoczetoSekcjeKomend(znak, &licznikZnakow) == true) {
            koniecNazwSelektorow = true;
            obslugaKomend(sekcje);
            buforowyString.usunString();
            return; //ta linijka wykona sie gdy powrocimy do wczytywania danych **** (wczyli wyjdziemy z obslugi komend), to powracamy do funkcji main
        }

        poprzedniZnak = znak;

    } while (koniecNazwSelektorow == false);

}

int main() {

    std::ios::sync_with_stdio(false);


    Sekcje sekcje; //lista sekcji
    sekcje.liczbaSekcji = 0;

    while (zakonczonoProgram == false) {
        wczytujSelektory(&sekcje);
    }

    return 0;
}