#ifndef GUMA_H
#define GUMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Guma
	{
		char* znaky;
		unsigned int delka;
		unsigned int ukazovatko;
		struct Guma* dalsi; 
	} Guma;

Guma* VytvorGumu (int delka);
void SmazGumu (Guma* pGuma);
void VlozDoGumy (Guma* pGuma, int index, char znak);
void VlozDoGumyZleva (Guma* pGuma, int index, char znak);
void VypisGumu (Guma* pGuma);
void Vrat (Guma* pGuma, int index, char* znak);
int DelkaGumy (Guma* pGuma);
char* GumaNaRetezec (Guma* pGuma);
Guma* GumaPridejZleva (Guma* pGuma);
Guma* GumaOdeberZleva (Guma* pGuma);
Guma* GumaPridejZprava (Guma* pGuma);

#endif
