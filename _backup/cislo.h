#ifndef CISLO_H
#define CISLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guma.h"

typedef struct Cislo
	{
		Guma* mantisa;
		Guma* exponent;
		char znamenkoMan;
		char znamenkoExp;
	} Cislo;
	
Cislo* VratCislo(FILE* soubor);
Cislo* VytvorCislo(void);
void SmazCislo(Cislo** ppCislo);
void ZapisZnamenko(Cislo** ppCislo, char kam, char znak);
int Automat(int stav,int index, char znak);
Cislo* OptimalizujCislo(Cislo** ppCislo);
void VypisCislo(Cislo** ppVysledek);

#endif
