//3. Se�ten� (respektive vyn�soben�) ��sel
//Na vstupu je posloupnost ��sel odd�len�ch mezerami. Pomoc� dlouh� aritmetiky naprogramujte:
//a) sou�et cel�ch ��sel
//b) sou�in cel�ch ��sel
//c) sou�et re�ln�ch ��sel 
//d) sou�in re�ln�ch ��sel

#include <stdio.h>

#include <string.h>
#include "aritmetika.h"

void main(int argc, char** argv)
	{
		Cislo* pCisloA = NULL;
		Cislo* pCisloB = NULL;
		Cislo* pVysledek = VytvorCislo();
		FILE* soubor;
		char* nazevSouboru;
				
		nazevSouboru = argv[1];
		soubor = fopen(nazevSouboru,"r");
		
	    pCisloA = VratCislo(soubor);
	    pCisloB = VratCislo(soubor);
	    //ypisGumu((*pCisloA).mantisa);
	    //printf("\n");
	    //pCisloB = VratCislo(soubor);
	    //VypisGumu((*pCisloB).mantisa);
	    //printf("\n");
		while (pCisloB != NULL)
	    	{
				if (pCisloA == NULL)
					{
						pVysledek = pCisloB; 
					};
				if (pCisloB == NULL)
					{
						pVysledek = pCisloA;
					};
				if ((pCisloA != NULL) && (pCisloB != NULL))
					{
						Scitani(&pCisloA,&pCisloB,&pVysledek);
					};
				//VypisGumu((*pVysledek).mantisa);
				//printf("\n");
				pCisloA = pVysledek;
				//VypisGumu((*pCisloA).mantisa);
	    		//printf("\n");
				pCisloB = VratCislo(soubor);
				//VypisGumu((*pCisloB).mantisa);
	    		//printf("\n");
			};
		VypisGumu((*pVysledek).mantisa);
	    fclose(soubor);	
	    getchar();
		return;	
	};
