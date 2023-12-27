#pragma once
#include <iostream>
#include "myString.h"

using namespace std;

	myString::myString() {
		znaki = new char[1];
		znaki[0] = '\0';
	}

	myString::myString(char* tablicaCharow) {
		znaki = new char[sizeof(tablicaCharow) / sizeof(char)];
		for (int i = 0; i < sizeof(tablicaCharow) / sizeof(char); i++) {
			znaki[i] = tablicaCharow[i];
		}
	}

	void myString::usunString() {
		delete[] znaki;
	}

	void myString::wyczyscString() {
		delete[] znaki;
		znaki = new char[1];
		znaki[0] = '\0';
	}

	void myString::nowyString() {
		myString nowyString;
		znaki = nowyString.znaki;
	}

	char* myString::getString() {

		return znaki;
	}

	int myString::jakaDlugosc() const {
		int len = 0;
		while (znaki[len] != '\0')
			len++;
		return len;
	}

	void myString::dodajZnak(char znak) {
		int wielkoscStarejTablicy = jakaDlugosc() + 1; // +1 bo jeszcze znak \0 na koncu
		char* noweZnaki = new char[wielkoscStarejTablicy + 1];
		for (int i = 0; i < wielkoscStarejTablicy - 1; i++) {
			noweZnaki[i] = znaki[i];
		}
		noweZnaki[wielkoscStarejTablicy - 1] = znak;
		noweZnaki[wielkoscStarejTablicy] = '\0';
		delete[] znaki;
		znaki = noweZnaki;
	}

	char myString::jakaLitera(int i) const {
		return this->znaki[i];
	}

	void myString::usunSpacjeNaKoncu() {
		int wielkoscStarejTablicy = jakaDlugosc() + 1; // +1 bo jeszcze znak \0 na koncu
		if (znaki[wielkoscStarejTablicy - 2] == ' ') {
			char* noweZnaki = new char[wielkoscStarejTablicy - 1];
			for (int i = 0; i < wielkoscStarejTablicy - 2; i++) {
				noweZnaki[i] = znaki[i];
			}
			noweZnaki[wielkoscStarejTablicy - 2] = '\0';
			delete[] znaki;
			znaki = noweZnaki;
		}
	}

	bool myString::operator==(myString& other) {
		int dlugosc = this->jakaDlugosc();
		if (other.jakaDlugosc() == dlugosc) {
			for (int i = 0; i < dlugosc; i++) {
				if (this->znaki[i] != other.jakaLitera(i)) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}


