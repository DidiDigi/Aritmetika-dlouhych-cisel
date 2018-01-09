#ifndef ARITMETIKA_H
#define ARITMETIKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cislo.h"
#include "guma.h"

void Scitani(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek);
Guma* SectiCisla(Guma* pMantisaA, Guma* pMantisaB);
Guma* OdectiCisla(Guma* pMantisaA, Guma* pMantisaB);
void Nasobeni(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek);
void Deleni(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek, int pocet_mist);
void Faktorial(Cislo* pCislo,Cislo* pVysledek);
char UrciZnamenkoVysledku(Cislo* pCisloA, Cislo* pCisloB);
int SrovnejExponenty(Cislo* pCisloA, Cislo* pCisloB);
Guma* Inkrement(Guma* pGuma);
void Dekrement(Guma* pGuma);
int AVetsiB(Guma* pMantisaA, Guma* pMantisaB);
Guma* OptimalizujMantisu(Guma* pGuma);
int NeniNula(Guma* pGuma);
void EulerovoCislo2(Cislo* pCislo,Cislo* pVysledek,int pocet_mist);

#endif
