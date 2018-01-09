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
	  EulerovoCislo(pCisloA,pVysledek,100);
	//  Faktorial(pCisloA,pVysledek);
	/*
		pCisloA = VratCislo(soubor);
		pCisloB = VratCislo(soubor);
	    if (pCisloA != NULL)
	    	{
	    		VypisCislo(pCisloA);
	    		printf("\n");		
			};
		//pVysledek = pCisloA;	
		if (pCisloB != NULL)
	    	{
	    		VypisCislo(pCisloB);
	    		printf("\n");		
			};
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
						//Scitani(pCisloA,pCisloB,pVysledek);
						//Nasobeni(pCisloA,pCisloB,pVysledek);
						Deleni(pCisloA,pCisloB,pVysledek,3);
					};
				pCisloA = pVysledek;
				pCisloB = VratCislo(soubor);
				if (pCisloB != NULL)
			    	{
			    		VypisCislo(pCisloB);
			    		printf("\n");		
					};
			};
	*/	
		if (pVysledek != NULL)
			{
				//VypisGumu((*pVysledek).mantisa);
				//printf("\n");
				VypisCislo(pVysledek);		
			};
		SmazCislo(pVysledek);
	    fclose(soubor);	
	    getchar();
		return;	
	};
