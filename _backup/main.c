//3. Seètení (respektive vynásobení) èísel
//Na vstupu je posloupnost èísel oddìlených mezerami. Pomocí dlouhé aritmetiky naprogramujte:
//a) souèet celých èísel
//b) souèin celých èísel
//c) souèet reálných èísel 
//d) souèin reálných èísel

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
