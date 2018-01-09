#ifndef CISLO_H
#define CISLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guma.h"

typedef struct Cislo
	{
		Guma* mantisa;
		char znamenko;
		int exponent;
	} Cislo;
	
Cislo* VratCislo(FILE* soubor);
Cislo* VytvorCislo(void);
void SmazCislo(Cislo* pCislo);
void ZapisZnamenko(Cislo* pCislo, char znak);
int Automat(int stav,int index, char znak);
Cislo* OptimalizujCislo(Cislo* pCislo);
void VypisCislo(Cislo* ppVysledek);

#endif
