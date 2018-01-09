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
void SmazGumu (Guma** ppGuma);
void VlozDoGumy (Guma** ppGuma, int index, char znak);
void VlozDoGumyZleva (Guma** ppGuma, int index, char znak);
void VypisGumu (Guma* pGuma);
void Vrat (Guma* pGuma, int index, char* znak);
int DelkaGumy (Guma* pGuma);
char* GumaNaRetezec (Guma* pGuma);
int GumaPridejZleva (Guma** ppGuma);
int GumaOdeberZleva (Guma** ppGuma);
Guma* GumaPridejZprava (Guma** ppGuma);

#endif
