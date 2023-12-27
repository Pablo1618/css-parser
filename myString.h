#pragma once
#include <iostream>

using namespace std;

class myString {

private:

	char* znaki;

public:

	myString();

	myString(char* tablicaCharow);

	bool operator==(myString& other);

	void usunWskaznik();

	void usunString();

	void wyczyscString();

	void nowyString();

	void dodajZnak(char znak);

	char* getString();

	int jakaDlugosc() const;

	void wypiszStringAtrybuty();

	char jakaLitera(int i) const;

	myString usunPierwszaSpacje(myString& napis);

	void usunSpacjeNaKoncu();

};