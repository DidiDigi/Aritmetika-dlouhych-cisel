#ifndef ARITMETIKA_H
#define ARITMETIKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cislo.h"
#include "guma.h"

void Dekrement(Guma* pGuma);
void Inkrement(Guma* pGuma);
void Scitani(Cislo** ppCisloA, Cislo** ppCisloB, Cislo** ppVysledek);
Guma* SectiCisla(Guma* pMantisaA, Guma* pMantisaB);
Guma* OdectiCisla(Guma* pMantisaA, Guma* pMantisaB);
char UrciZnamenkoVysledku(Cislo** ppCisloA, Cislo** ppCisloB);
void SrovnejExponenty(Cislo** ppCisloA, Cislo** ppCisloB);

#endif
