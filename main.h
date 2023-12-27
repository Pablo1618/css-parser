#pragma once
#include "Sekcje.h"


int tablicaCharNaInt(char* napis);

bool sprawdzCzyCyfra(char* napis);

bool czyRozpoczetoSekcjeKomend(char znak, int* licznikZnakow);

void wykonajKomende(myString komendaStr, Sekcje* sekcje);

void obslugaKomend(Sekcje* sekcje);

void wczytujAtrybuty(Sekcje* sekcje, bool czyGlobalne);

void wczytujSelektory(Sekcje* sekcje);