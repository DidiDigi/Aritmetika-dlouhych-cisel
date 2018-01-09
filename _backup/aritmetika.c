#include "aritmetika.h"

void Inkrement(Guma* pGuma)
	{
		Guma* pivot = pGuma;
		char* cislice = (char*) malloc(sizeof(char));
		int preteceni = 1;
		int index = 0;
			
		if (pivot == NULL) //pokud jeste nemam exponent
			{
				pivot = VytvorGumu((10)); // vytváøím Gumu a vracím ukazatel na Gumu, vìtší velikost než na jaké místo zapisuju
				VlozDoGumy(&(pivot), 0, '1');
				return;	
			};
	
		// najdi misto posledni cislice v gume
		index = DelkaGumy(pGuma);
		//hlida preteceni gumy zleva
		while (index > 0)
			{
				while (preteceni != 0)
					{
						Vrat(pGuma, index, cislice);
						if (((*cislice) + preteceni) > 9)
							{
								*cislice = 0;
								index = index - 1;
							}
							else
								{	
									*cislice = *cislice + preteceni;
									preteceni = 0;
								};
					};
			};
		if ((index = 0) && (preteceni = 1))
			{
				GumaPridejZleva(&pGuma);
				VlozDoGumy(&pGuma, 0, '1');
			};
		return;	
	};
	
void Dekrement(Guma* pGuma)
	{
		Guma* pivot = pGuma;
		char* pCislice = (char*) malloc(sizeof(char));
		int podteceni = '1';
		int index = 0;
		
		if (pivot == NULL) //pokud jeste nemam exponent
			{
				return;
			};
		// najdi misto posledni cislice v gume
		index = DelkaGumy(pivot);
		//hlida preteceni gumy zleva
		while (index > 0)
			{
				while (podteceni != 0)
					{
						Vrat(pivot, index, pCislice);
						if (((*pCislice) - podteceni) < 0)
							{
								(*pCislice) = 9;
							}
							else
								{	
									(*pCislice) = (*pCislice) - podteceni;
									podteceni = 0;
								};
							index = index - 1;
					};
			};
		if ((index = 0) && (podteceni = 1))
			{
				GumaOdeberZleva(&pivot);
			};
		return;		
	};

	
void Scitani(Cislo** ppCisloA, Cislo** ppCisloB, Cislo** ppVysledek)
	{
		// vytvoreni struktury pro Vysledek
		if (ppVysledek == NULL)
			{
				ppVysledek = (Cislo**) malloc(sizeof(Cislo));
				*ppVysledek = VytvorCislo();
			};
		
		SrovnejExponenty(ppCisloA, ppCisloB);
					
		if (((**ppCisloA).znamenkoMan) == ((**ppCisloB).znamenkoMan))
			{
				((**ppVysledek).znamenkoMan) = ((**ppCisloA).znamenkoMan);
				(**ppVysledek).mantisa = SectiCisla((**ppCisloA).mantisa, (**ppCisloB).mantisa);
			}
			else
				{
					(**ppVysledek).znamenkoMan = UrciZnamenkoVysledku(ppCisloA, ppCisloB);
					if (((**ppVysledek).znamenkoMan) == ((**ppCisloA).znamenkoMan))
						{
							(**ppVysledek).mantisa = OdectiCisla((**ppCisloA).mantisa, (**ppCisloB).mantisa);
						}
						else
							{
								(**ppVysledek).mantisa = OdectiCisla((**ppCisloB).mantisa, (**ppCisloA).mantisa);
							};
				};
		return;				
	};
	
Guma* SectiCisla(Guma* pMantisaA, Guma* pMantisaB)
	{
		Guma* pivot = NULL;
		Guma* vetsi = pMantisaA;
		Guma* mensi = pMantisaB;
		
		char* pCisliceV = (char*) malloc(sizeof(char));
		char* pCisliceM = (char*) malloc(sizeof(char));
		
		int preteceni = 0;
		int indexV = 0; // index vetsiho cisla a soucasne i vysledku
		int indexM = 0;
		int hodnota = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
		
		int delkaA = DelkaGumy(pMantisaA);
		int delkaB = DelkaGumy(pMantisaB);
		
		indexV = delkaA;
		indexM = delkaB;
		
		if (delkaA < delkaB)
			{
				vetsi = pMantisaB;
				indexV = delkaB;
				mensi = pMantisaA;
				indexM = delkaA;
			};
				
		//nacitam pred vstupem do cyklu, abych mohla dalsi cisla nacist na konci cyklu, hodi se mi to pro nulove indexy
		
		while (indexM > 0)
			{
				indexV = indexV - 1;
				indexM = indexM - 1;
				Vrat(vetsi, indexV, pCisliceV);
				Vrat(mensi, indexM, pCisliceM);
				hodnota = atoi(pCisliceV) + atoi(pCisliceM) + preteceni;
				if (hodnota >= 10)
					{
						hodnota = hodnota - 10;
						preteceni = 1;
					}
					else 
						{
							preteceni = 0;
						};					
				//printf("%d\n", hodnota);
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumyZleva(&pivot,indexV,(*pCislice));
			};
			
		while (indexV > 0)
			{
				indexV = indexV - 1;
				Vrat(vetsi, indexV, pCisliceV);
				hodnota = atoi(pCisliceV) + preteceni;
				if (hodnota >= 10)
					{
						hodnota = hodnota - 10;
						preteceni = 1;
					}
					else 
						{
							preteceni = 0;
						};
				//printf("%d\n", hodnota);
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumyZleva(&pivot,indexV,(*pCislice));
			};
		if ((indexV = 0) && (preteceni = 1))
			{
				GumaPridejZleva(&pivot);
				VlozDoGumyZleva(&pivot,0,'1');
			};
		return pivot;
	};

Guma* OdectiCisla(Guma* pVetsi, Guma* pMensi)
	{
		Guma* pivot = NULL;
			
		char* pCisliceV = (char*) malloc(sizeof(char));
		char* pCisliceM = (char*) malloc(sizeof(char));
		int podteceni = 0;
		int indexV = 0; // index vetsiho cisla a soucasne i vysledku
		int indexM = 0;
		int hodnota = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
											
		if (pivot == NULL)
			{
				pivot = VytvorGumu((DelkaGumy(pVetsi))); // vytváøím Gumu velikosti vetsi mantisy
			};
		
		indexV = DelkaGumy(pVetsi) - 1;
		indexM = DelkaGumy(pMensi) - 1;
		
		while (indexM >= 0)
			{
				Vrat(pVetsi, indexV, pCisliceV);
				Vrat(pMensi, indexM, pCisliceM);
				hodnota = atoi(pCisliceV) - atoi(pCisliceM) - podteceni;
				if (hodnota < 0)
					{
						hodnota = hodnota + 10;
						podteceni = 1;
					}
					else 
						{
							podteceni = 0;
						};					
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumyZleva(&pivot,indexV,(*pCislice));
				indexM = indexM - 1;
				indexV = indexV - 1;
			};
			
		while (indexV > 0)
			{
				//*cisliceV = 
				Vrat(pVetsi, indexV, pCisliceV);
				hodnota = atoi(pCisliceV) - podteceni;
				if (hodnota < 0)
					{
						hodnota = hodnota + 10;
						podteceni = 1;
					}
					else 
						{
							podteceni = 0;
						};
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumyZleva(&pivot,indexV,(*pCislice));
				indexV = indexV - 1;
			};
		
			if ((indexV == 0) && (podteceni == 1))
			{
				GumaOdeberZleva(&pivot);	
			};
				
		return;	
	};
	
char UrciZnamenkoVysledku(Cislo** ppCisloA, Cislo** ppCisloB)
	{
		char znamenko = ' ';
		Guma* pMantisaA = (**ppCisloA).mantisa;
		Guma* pMantisaB = (**ppCisloB).mantisa;
		
		char* pCisliceV = (char*) malloc(sizeof(char));
		char* pCisliceM = (char*) malloc(sizeof(char));
		int indexV = 0; // index vetsiho cisla a soucasne i vysledku
		int indexM = 0;
					
		int delkaA = DelkaGumy(pMantisaA);
		int delkaB = DelkaGumy(pMantisaB);
		
		//*cisliceV = 
		Vrat(pMantisaA, indexV, pCisliceV);		
		//*cisliceM = 
		Vrat(pMantisaB, indexM, pCisliceM);
		
		if (delkaA < delkaB)
			{
				znamenko = (**ppCisloB).znamenkoMan;				
			};
				
		if ((delkaA == delkaB) && ((atoi(pCisliceV)) < (atoi(pCisliceM))))
			{
				znamenko = (**ppCisloB).znamenkoMan;
			};
		
		if ((delkaA == delkaB) && ((atoi(pCisliceV)) == (atoi(pCisliceM))))
			{							
				indexV = indexV + 1;
				indexM = indexM + 1;
				Vrat(pMantisaA, indexV, pCisliceV);		
				Vrat(pMantisaB, indexM, pCisliceM);
				while ((atoi(pCisliceV) <= (atoi(pCisliceM))) && (indexV < delkaA))
					{
						indexV = indexV + 1;
						indexM = indexM + 1;
						Vrat(pMantisaA, indexV, pCisliceV);		
						Vrat(pMantisaB, indexM, pCisliceM);
					};
				if (indexV != delkaA)
					{
						znamenko = (**ppCisloB).znamenkoMan;
					};
					
			};
		return znamenko;
	};
	
void SrovnejExponenty(Cislo** ppCisloA, Cislo** ppCisloB)
	{
		Guma* pExponentA = (**ppCisloA).exponent;
		char znamenkoExpA = (**ppCisloA).znamenkoExp;
		Guma* pExponentB = (**ppCisloB).exponent;
		char znamenkoExpB = (**ppCisloB).znamenkoExp;
		int indexA = DelkaGumy((**ppCisloA).mantisa) - 1; //pozice posledniho znaku mantisy
		int indexB = DelkaGumy((**ppCisloA).mantisa) - 1;
		Guma* pRozdil = NULL;
		int delkaExpA = DelkaGumy(pExponentA) - 1;
		int delkaExpB = DelkaGumy(pExponentB) - 1;
		char* pCisliceA = (char*) malloc(sizeof(char));		
		char* pCisliceB = (char*) malloc(sizeof(char));
		int a = 0; //kde se nachazim v ExponentuA
		int b = 0; // kde se nachazim v ExponentuB
		Vrat(pExponentA, a, pCisliceA);		
		Vrat(pExponentB, b, pCisliceB);
		
		if ((znamenkoExpA == '+') && (znamenkoExpB == '-')) 
			{
				pRozdil = SectiCisla(pExponentA,pExponentB);
				while (pRozdil != NULL)
					{
						indexA = indexA + 1;
						VlozDoGumy(&(**ppCisloA).mantisa,indexA,'0');
						Dekrement(pRozdil);
					};
			};
		
		if ((znamenkoExpA == '-') && (znamenkoExpB == '+')) 
			{
				pRozdil = SectiCisla(pExponentA,pExponentB);
				while (pRozdil != NULL)
					{
						indexB = indexB + 1;
						VlozDoGumy(&(**ppCisloB).mantisa,indexB,'0');
						Dekrement(pRozdil);
					};
			};
				
		if ((znamenkoExpA == '+') && (znamenkoExpB == '+'))
			{
	
				if (delkaExpA < delkaExpB)
					{
						pRozdil = OdectiCisla(pExponentB,pExponentA);
						while (pRozdil != NULL)
							{
								indexB = indexB + 1;
								VlozDoGumy(&(**ppCisloB).mantisa,indexB,'0');
								Dekrement(pRozdil);
							};				
						return;	
					};
				
				if ((delkaExpA == delkaExpB) && ((*pCisliceA) < (*pCisliceB)))
					{
						pRozdil = OdectiCisla(pExponentB,pExponentA);
						while (pRozdil != NULL)
							{
								indexB = indexB + 1;
								VlozDoGumy(&(**ppCisloB).mantisa,indexB,'0');
								Dekrement(pRozdil);
							};
						return;
					};
				
				if ((delkaExpA == delkaExpB) && ((*pCisliceA) == (*pCisliceB)))
					{							
						a = a + 1;
						b = b + 1;
						//*cisliceA = 
						Vrat(pExponentA, a, pCisliceA);		
						//*cisliceB = 
						Vrat(pExponentB, b, pCisliceB);
						while (((*pCisliceA) <= (*pCisliceB)) && (a <= delkaExpA))
							{
								a = a + 1;
								b = b + 1;
								//*cisliceA = 
								Vrat(pExponentA, a, pCisliceA);		
								//*cisliceB = 
								Vrat(pExponentB, b, pCisliceB);
							};
						if (a <= delkaExpA)
							{
								pRozdil = OdectiCisla(pExponentB,pExponentA);
								while (pRozdil != NULL)
									{
										indexB = indexB + 1;
										VlozDoGumy(&(**ppCisloB).mantisa,indexB,'0');
										Dekrement(pRozdil);
									};
								return;
							};
					};
					
				pRozdil = OdectiCisla(pExponentA,pExponentB);
				while (pRozdil != NULL)
					{
						indexA = indexA + 1;
						VlozDoGumy(&(**ppCisloA).mantisa,indexA,'0');
						Dekrement(pRozdil);
						return;
					};
			};
			
		if ((znamenkoExpA == '-') && (znamenkoExpB == '-'))
			{
				if (delkaExpA < delkaExpB)
					{
						pRozdil = OdectiCisla(pExponentB,pExponentA);
						while (pRozdil != NULL)
							{
								indexA = indexA + 1;
								VlozDoGumy(&(**ppCisloA).mantisa,indexA,'0');
								Dekrement(pRozdil);
							};				
						return;	
					};
				
				if ((delkaExpA == delkaExpB) && ((*pCisliceA) < (*pCisliceB)))
					{
						pRozdil = OdectiCisla(pExponentB,pExponentA);
						while (pRozdil != NULL)
							{
								indexB = indexA + 1;
								VlozDoGumy(&(**ppCisloA).mantisa,indexA,'0');
								Dekrement(pRozdil);
							};
						return;
					};
				
				if ((delkaExpA == delkaExpB) && ((*pCisliceA) == (*pCisliceB)))
					{							
						a = a + 1;
						b = b + 1;
						//*cisliceA = 
						Vrat(pExponentA, a, pCisliceA);		
						//*cisliceB = 
						Vrat(pExponentB, b, pCisliceB);
						while (((*pCisliceA) >= (*pCisliceB)) && (a <= delkaExpA))
							{
								a = a + 1;
								b = b + 1;
								//*cisliceA = 
								Vrat(pExponentA, a, pCisliceA);		
								//*cisliceB = 
								Vrat(pExponentB, b, pCisliceB);
							};
						if (a <= delkaExpA)
							{
								pRozdil = OdectiCisla(pExponentB,pExponentA);
								while (pRozdil != NULL)
									{
										VlozDoGumy(&(**ppCisloA).mantisa,indexA,'0');
										indexA = indexA + 1;
										Dekrement(pRozdil);
									};
								return;
							};
					};
					
				pRozdil = OdectiCisla(pExponentB,pExponentA);
				while (pRozdil != NULL)
					{
						VlozDoGumy(&(**ppCisloB).mantisa,indexB,'0');
						indexA = indexB + 1;
						Dekrement(pRozdil);
					};
			};
		return;
	};
