#include "aritmetika.h"

void Scitani(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek)
	{
		// vytvoreni struktury pro Vysledek
		if (pVysledek == NULL)
			{
				pVysledek = (Cislo*) malloc(sizeof(Cislo));
				pVysledek = VytvorCislo();
			};
		
		(*pVysledek).exponent = SrovnejExponenty(pCisloA, pCisloB);
					
		if (((*pCisloA).znamenko) == ((*pCisloB).znamenko))
			{
				((*pVysledek).znamenko) = ((*pCisloA).znamenko);
				(*pVysledek).mantisa = SectiCisla((*pCisloA).mantisa, (*pCisloB).mantisa);
			}
			else
				{
					(*pVysledek).znamenko = UrciZnamenkoVysledku(pCisloA, pCisloB);
					if ((DelkaGumy((*pCisloA).mantisa)) >= ((DelkaGumy((*pCisloB).mantisa))))
						{
							(*pVysledek).mantisa = OdectiCisla((*pCisloA).mantisa, (*pCisloB).mantisa);
							OptimalizujMantisu((*pVysledek).mantisa);
						}
						else
							{
								(*pVysledek).mantisa = OdectiCisla((*pCisloB).mantisa, (*pCisloA).mantisa);
								OptimalizujMantisu((*pVysledek).mantisa);
							};
				};
		
		return;				
	};
	
Guma* SectiCisla(Guma* pMantisaA, Guma* pMantisaB)
	{
		Guma* pivot = NULL;
		Guma* pVetsi = pMantisaA;
		Guma* pMensi = pMantisaB;
		
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
				pVetsi = pMantisaB;
				indexV = delkaB;
				pMensi = pMantisaA;
				indexM = delkaA;
			};
				
		//nacitam pred vstupem do cyklu, abych mohla dalsi cisla nacist na konci cyklu, hodi se mi to pro nulove indexy
		
		if (pivot == NULL)
			{
				pivot = VytvorGumu((DelkaGumy(pVetsi))); // vytváøím Gumu velikosti vetsi mantisy
			};
		
		while (indexM > 0)
			{
				indexV = indexV - 1;
				indexM = indexM - 1;
				Vrat(pVetsi, indexV, pCisliceV);
				Vrat(pMensi, indexM, pCisliceM);
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
				VlozDoGumyZleva(pivot,indexV,(*pCislice));
			};
			
		while (indexV > 0)
			{
				indexV = indexV - 1;
				Vrat(pVetsi, indexV, pCisliceV);
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
				VlozDoGumyZleva(pivot,indexV,(*pCislice));
			};
		if ((indexV == 0) && (preteceni == 1))
			{
				pivot = GumaPridejZleva(pivot);
				VlozDoGumyZleva(pivot,0,'1');
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
				VlozDoGumyZleva(pivot,indexV,(*pCislice));
				indexM = indexM - 1;
				indexV = indexV - 1;
			};
			
		while (indexV >= 0)
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
				VlozDoGumyZleva(pivot,indexV,(*pCislice));
				indexV = indexV - 1;
			};
		
		
		//pivot = OptimalizujMantisu(pivot);			
		return pivot;	
	};

void Nasobeni(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek)
	{
		Guma* pivot = (*pVysledek).mantisa;
		Guma* pMantisaA = (*pCisloA).mantisa;
		Guma* pMantisaB = (*pCisloB).mantisa;
		int exponentA = (*pCisloA).exponent;
		int exponentB = (*pCisloB).exponent;
		int delkaA = DelkaGumy(pMantisaA);
		int delkaB = DelkaGumy(pMantisaB);
		Guma* pTemp1 = VytvorGumu(delkaA);
		Guma* pTemp2 = VytvorGumu(delkaA);
		Guma* pTemp3 = VytvorGumu(delkaA);
		int indexA = delkaA - 1;
		int indexB = delkaB - 1;
		int i = 0;
		int j = 0;
		int k = 0;
		int preteceni = 0;
		int hodnota = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
		char* pCisliceA = (char*) malloc(sizeof(char));
		*pCisliceA = '0';
		char* pCisliceB = (char*) malloc(sizeof(char));
		*pCisliceB = '0';
		
		// vytvoreni struktury pro Vysledek
		if (pVysledek == NULL)
			{
				pVysledek = (Cislo*) malloc(sizeof(Cislo));
				pVysledek = VytvorCislo();
			};
		
		// znamenko Vysledku
		if (((*pCisloA).znamenko) == ((*pCisloB).znamenko))
			{
				(*pVysledek).znamenko = '+';
			}
			else
				{
					(*pVysledek).znamenko = '-';
				};
		//exponent vysledku 
		(*pVysledek).exponent = exponentA + exponentB;
		
		for (j = indexB; j >= 0; j--)
			{
				Vrat(pMantisaB,j,pCisliceB);
				indexA = delkaA - 1;
				pTemp2 = VytvorGumu(delkaA);
				for (i = indexA; i >= 0; i--)
					{
						Vrat(pMantisaA,i,pCisliceA);
						hodnota = ((atoi(pCisliceA)) * (atoi(pCisliceB)) + preteceni);
						preteceni = 0;
						if  (hodnota > 9)
							{
								while (hodnota > 9)
									{
										hodnota = hodnota - 10;
										preteceni = preteceni + 1; 
									};
							}
							else
								{
									preteceni = 0;
								};
						sprintf(pCislice, "%i", hodnota);
						VlozDoGumyZleva(pTemp2,indexA,(*pCislice));
						indexA = indexA - 1;
					};
					if (preteceni > 0)
						{
							pTemp2 = GumaPridejZleva(pTemp2);
							sprintf(pCislice, "%i", preteceni);
							VlozDoGumy(pTemp2,0,(*pCislice));
							preteceni = 0;
						};	
				for (k = 0; k < (delkaB - j - 1); k++)
					{
						int index = DelkaGumy(pTemp2);
						VlozDoGumy(pTemp2,index,'0');
					};
				pTemp3 = SectiCisla(pTemp1,pTemp2);
				pTemp1 = pTemp3;
				//SmazGumu(pTemp2);
				//SmazGumu(pTemp3);
			};
		
		(*pVysledek).mantisa = pTemp1;
		return;
	};

void Deleni(Cislo* pCisloA, Cislo* pCisloB, Cislo* pVysledek, int pocet_mist)
	{
		Guma* pivot = (*pVysledek).mantisa;
		Guma* pMantisaA = (*pCisloA).mantisa;
		Guma* pMantisaB = (*pCisloB).mantisa;
		Guma* pTemp = VytvorGumu(1);
		char* pCisliceA = (char*) malloc(sizeof(char));
		(*pCisliceA) = '0';
		char* pCislice = (char*) malloc(sizeof(char));
		(*pCislice) = '0';
		int exponentA = (*pCisloA).exponent;
		int exponentB = (*pCisloB).exponent;
		int exponentV = 0;
		int indexA = DelkaGumy(pMantisaA) - 1;
		int a = 0;
		int indexT = 0;
		int indexV = 0;
		int hodnota = 0;
				// vytvoreni struktury pro Vysledek
		if (pVysledek == NULL)
			{
				pVysledek = (Cislo*) malloc(sizeof(Cislo));
				pVysledek = VytvorCislo();
				pivot = (*pVysledek).mantisa;
			};
		
		Vrat(pMantisaA,a,pCisliceA);
		a = a + 1;
		VlozDoGumy(pTemp,indexT,(*pCisliceA));
		
		//urceni vysledku
		exponentV = ((exponentA - exponentB));
	
		while ((a <= indexA) && (!(AVetsiB(pTemp,pMantisaB))))
			{
				Vrat(pMantisaA,a,pCisliceA);
				indexT = DelkaGumy(pTemp);
				VlozDoGumy(pTemp,indexT,(*pCisliceA));
				a = a + 1;
			
				while (AVetsiB(pTemp,pMantisaB))
					{
						pTemp = OdectiCisla(pTemp, pMantisaB);
						pTemp = OptimalizujMantisu(pTemp);
						hodnota = hodnota + 1;
					};
				sprintf(pCislice, "%i", hodnota);
				//indexV = (DelkaGumy(pivot));
				VlozDoGumy(pivot,indexV,(*pCislice));
				//pivot = OptimalizujMantisu(pivot);
				indexV = indexV + 1;
				hodnota = 0;
			};
		
		while ((NeniNula(pTemp)) && (exponentV >= (-pocet_mist)) && (!(AVetsiB(pTemp,pMantisaB))))
			{
				indexT = DelkaGumy(pTemp);
				VlozDoGumy(pTemp,indexT,'0');	
				exponentV = exponentV - 1;
						
				while (AVetsiB(pTemp,pMantisaB))
					{
						pTemp = OdectiCisla(pTemp, pMantisaB);
						pTemp = OptimalizujMantisu(pTemp);
						hodnota = hodnota + 1;
					};
				sprintf(pCislice, "%i", hodnota);
				//indexV = (DelkaGumy(pivot));
				VlozDoGumy(pivot,indexV,(*pCislice));
				//pivot = OptimalizujMantisu(pivot);
				indexV = indexV + 1;
				hodnota = 0;
			};
					
		// znamenko Vysledku
		if (((*pCisloA).znamenko) == ((*pCisloB).znamenko))
			{
				(*pVysledek).znamenko = '+';
			}
			else
				{
					(*pVysledek).znamenko = '-';
				};
				
		//exponent vysledku 
		(*pVysledek).exponent = exponentV;
		(*pVysledek).mantisa = pivot;
		return;
	};
	
void Faktorial(Cislo* pCislo, Cislo* pVysledek)
	{
		Cislo* pivot = pVysledek;
		Cislo* pCisloA = VytvorCislo();
		Cislo* pCisloB = VytvorCislo();
		Cislo* pMinusJednicka = VytvorCislo();
		
		VlozDoGumy((*pMinusJednicka).mantisa,0,'1');
		
		(*pMinusJednicka).znamenko = '-';
		
		pCisloA = pCislo;
		Scitani(pCisloA,pMinusJednicka,pCisloB);
		(*pCisloB).mantisa = OptimalizujMantisu((*pCisloB).mantisa);
		
		while (NeniNula((*pCisloB).mantisa))
			{
				Nasobeni(pCisloA,pCisloB,pivot);
				(*pivot).mantisa = OptimalizujMantisu((*pivot).mantisa);
				pCisloA = pivot;
				Scitani(pCisloB,pMinusJednicka,pCisloB);
				(*pCisloB).mantisa = OptimalizujMantisu((*pCisloB).mantisa);
			};
		pVysledek = pivot;
		return;
	};
	
	
char UrciZnamenkoVysledku(Cislo* pCisloA, Cislo* pCisloB)
	{
		char znamenko = ' ';
		Guma* pMantisaA = (*pCisloA).mantisa;
		Guma* pMantisaB = (*pCisloB).mantisa;
		
		char* pCisliceV = (char*) malloc(sizeof(char));
		char* pCisliceM = (char*) malloc(sizeof(char));
		int indexV = 0; // index vetsiho cisla a soucasne i vysledku
		int indexM = 0;
					
		int delkaA = DelkaGumy(pMantisaA);
		int delkaB = DelkaGumy(pMantisaB);
		
		Vrat(pMantisaA, indexV, pCisliceV);		
		Vrat(pMantisaB, indexM, pCisliceM);
		
		if (delkaA < delkaB)
			{
				znamenko = (*pCisloB).znamenko;				
			};
				
		if ((delkaA == delkaB) && ((atoi(pCisliceV)) < (atoi(pCisliceM))))
			{
				free(pCisliceV);
				free(pCisliceM);
				return znamenko = (*pCisloB).znamenko;
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
						free(pCisliceV);
						free(pCisliceM);
						return znamenko = (*pCisloB).znamenko;
					};
					
			};
		free(pCisliceV);
		free(pCisliceM);
		return znamenko = (*pCisloA).znamenko;
	};
	
int SrovnejExponenty(Cislo* pCisloA, Cislo* pCisloB)
	{
		int exponentA = (*pCisloA).exponent;
		int exponentB = (*pCisloB).exponent;
		int indexA = DelkaGumy((*pCisloA).mantisa) - 1; //pozice posledniho znaku mantisy
		int indexB = DelkaGumy((*pCisloB).mantisa) - 1;
		int rozdil = 0;
		
		if (exponentA == exponentB)
			{
				return exponentA;
			};
				
		if ((exponentA >= 0) && (exponentB < 0)) 
			{
				(*pCisloA).exponent = exponentB;
				rozdil = exponentA - exponentB;
				while (rozdil != 0)
					{
						indexA = indexA + 1;
						VlozDoGumy((*pCisloA).mantisa,indexA,'0');
						rozdil = rozdil - 1;
					};
				return exponentB;
			};
		
		if ((exponentA < 0) && (exponentB >= 0)) 
			{
				(*pCisloB).exponent = exponentA;
				rozdil = exponentB - exponentA;
				while (rozdil != 0)
					{
						indexB = indexB + 1;
						VlozDoGumy((*pCisloB).mantisa,indexB,'0');
						rozdil = rozdil - 1;
					};
				return exponentA;
			};
				
		if ((exponentA >= 0) && (exponentB >= 0))
			{
				if (exponentA < exponentB)
					{
						(*pCisloB).exponent = exponentA;
						rozdil = exponentB - exponentA;
						while (rozdil != 0)
							{
								indexB = indexB + 1;
								VlozDoGumy((*pCisloB).mantisa,indexB,'0');
								rozdil = rozdil - 1;
							};				
						return exponentA;	
					};
				
				if (exponentA > exponentB)
					{
						(*pCisloA).exponent = exponentB;
						rozdil = exponentA - exponentB;
						while (rozdil != 0)
							{
								indexA = indexA + 1;
								VlozDoGumy((*pCisloA).mantisa,indexA,'0');
								rozdil = rozdil - 1;
							};				
						return exponentB;	
					};
			};
			
		if ((exponentA < 0) && (exponentB < 0))
			{
				if (exponentA < exponentB)
					{
						(*pCisloB).exponent = exponentA;
						rozdil = (-1*(exponentB - exponentA));
						while (rozdil != 0)
							{
								indexB = indexB + 1;
								VlozDoGumy((*pCisloB).mantisa,indexB,'0');
								rozdil = rozdil - 1;
							};				
						return exponentA;	
					};
				
				if (exponentA > exponentB)
					{
						(*pCisloA).exponent = exponentB;
						rozdil = (exponentA - exponentB);
						while (rozdil != 0)
							{
								indexA = indexA + 1;
								VlozDoGumy((*pCisloA).mantisa,indexA,'0');
								rozdil = rozdil - 1;
							};				
						return exponentB;
					};
			};
	};
	
Guma* Inkrement(Guma* pGuma)
	{
		Guma* pivot = pGuma;
				
		char* pCisliceP = (char*) malloc(sizeof(char));
				
		int preteceni = 1;
		int index = DelkaGumy(pivot);
		int hodnota = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
		

		while (index > 0)
			{
				index = index - 1;
				Vrat(pivot, index, pCisliceP);
				hodnota = atoi(pCisliceP) + preteceni;
				if (hodnota >= 10)
					{
						hodnota = hodnota - 10;
						preteceni = 1;
					}
					else 
						{
							preteceni = 0;
						};
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumyZleva(pivot,index,(*pCislice));
			};
			
		if ((index == 0) && (preteceni == 1))
			{
				pivot = GumaPridejZleva(pivot);
				VlozDoGumyZleva(pivot,0,'1');
			};
		//free(pCisliceP);
		//free(pCislice);
		return pivot;
	};
	
void Dekrement(Guma* pGuma)
	{
		Guma* pivot = pGuma;
		int podteceni = 1;
		int index = 0;
		int hodnota = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
			
		if (pivot == NULL) //pokud jeste nemam exponent
			{
				pivot = VytvorGumu((10)); // vytváøím Gumu a vracím ukazatel na Gumu, vìtší velikost než na jaké místo zapisuju
				VlozDoGumy(pivot, 0, '1');
				free(pCislice);
				return;	
			};
	
		// najdi misto posledni cislice v gume
		index = DelkaGumy(pivot) - 1;
		
		//hlida preteceni gumy zleva
		while (index > 0)
			{
				while (podteceni != 0)
					{
						Vrat(pGuma, index, pCislice);
						hodnota = atoi(pCislice) - podteceni;
						if (hodnota < 0)
							{
								hodnota = hodnota - 10;
								podteceni = 1;
								index = index - 1;
							}
							else
								{	
									podteceni = 0;
								};
					};
				sprintf(pCislice, "%i", hodnota);
				VlozDoGumy(pivot, index, (*pCislice));
			};
		
			
		if ((index == 0) && (podteceni == 1))
			{
				
				GumaOdeberZleva(pivot);
			};
		free(pCislice);
		return;	
	};

int AVetsiB(Guma* pMantisaA, Guma* pMantisaB)
	{
		char* pCisliceV = (char*) malloc(sizeof(char));
		char* pCisliceM = (char*) malloc(sizeof(char));
		int indexV = 0; // index vetsiho cisla a soucasne i vysledku
		int indexM = 0;
					
		int delkaA = DelkaGumy(pMantisaA);
		int delkaB = DelkaGumy(pMantisaB);
		
		Vrat(pMantisaA, indexV, pCisliceV);		
		Vrat(pMantisaB, indexM, pCisliceM);
		
		if (delkaA < delkaB)
			{
				return 0;				
			};
		
		if ((delkaA == delkaB) && ((atoi(pCisliceV)) == (atoi(pCisliceM))))
			{							
				indexV = indexV + 1;
				indexM = indexM + 1;
				Vrat(pMantisaA, indexV, pCisliceV);		
				Vrat(pMantisaB, indexM, pCisliceM);
				while ((atoi(pCisliceV) == (atoi(pCisliceM))) && (indexV < delkaA))
					{
						indexV = indexV + 1;
						indexM = indexM + 1;
						Vrat(pMantisaA, indexV, pCisliceV);		
						Vrat(pMantisaB, indexM, pCisliceM);
					};
				if (indexV == delkaA)
					{
						free(pCisliceV);
						free(pCisliceM);
						return 1;
					};
					
			};
				
		if ((delkaA == delkaB) && ((atoi(pCisliceV)) < (atoi(pCisliceM))))
			{
				free(pCisliceV);
				free(pCisliceM);
				return 0;
			};
		free(pCisliceV);
		free(pCisliceM);
		return 1;	
	};
	
	Guma* OptimalizujMantisu(Guma* pMantisa)
		{
			char* pCislice = (char*) malloc(sizeof(char));
			char* pPovoleno = "123456789";
			
			int index = 0;
						
			int delka = DelkaGumy(pMantisa);
			
			Vrat(pMantisa, index, pCislice);
	
			while (index < (delka-1) && (strchr(pPovoleno,(*pCislice)) == NULL))
				{
					pMantisa = GumaOdeberZleva(pMantisa);
					Vrat(pMantisa, index, pCislice);
					delka = DelkaGumy(pMantisa);
				};
			free(pCislice);
			return pMantisa;	
		};
		
	int NeniNula(Guma* pGuma)
		{
			char* pCislice = (char*) malloc(sizeof(char));
			int index = ((DelkaGumy(pGuma)) - 1);
			
			Vrat(pGuma,index,pCislice);	
			
			if ( (index == 0) && (atoi(pCislice) == 0))
				{
					return 0;
				};
			free(pCislice);	
			return 1;	
		};
	
	
	void EulerovoCislo(Cislo* pCislo,Cislo* pVysledek,int pocet_mist)
		{
			VlozDoGumy((*pVysledek).mantisa,0,'2');
			Cislo* pJmenovatel = VytvorCislo();
			VlozDoGumy((*pJmenovatel).mantisa,0,'1');
			Cislo* pTempVysledek = VytvorCislo();
			VlozDoGumy((*pTempVysledek).mantisa,0,'0');
			Cislo* pTemp = VytvorCislo();
			VlozDoGumy((*pTemp).mantisa,0,'2');
			Cislo* pCitatel = VytvorCislo();
			VlozDoGumy((*pCitatel).mantisa,0,'1');
			int i = 0;
			
			while (!AVetsiB((*pTemp).mantisa,(*pCislo).mantisa))
				{
					Faktorial(pTemp,pJmenovatel);
					Deleni(pCitatel,pJmenovatel,pTempVysledek,pocet_mist);
					//VypisCislo(pTempVysledek);
					//printf("\n");
					(*pVysledek).mantisa = OptimalizujMantisu((*pVysledek).mantisa);
					Scitani(pVysledek, pTempVysledek, pVysledek);	
					(*pTemp).mantisa = Inkrement((*pTemp).mantisa);
					//VypisCislo(pVysledek);
					//printf("\n");
				};
		SmazCislo(pJmenovatel);
		SmazCislo(pCitatel);
		SmazCislo(pTempVysledek);
		SmazCislo(pTemp);	
		return;		
		};
	
