#include "cislo.h"

Cislo* VytvorCislo(void)
	{
		Cislo* pCislo = NULL; 
		
		pCislo = (Cislo*) malloc(sizeof(Cislo));
		(*pCislo).mantisa = VytvorGumu(1);
		VlozDoGumy(((*pCislo).mantisa), 0, '0');
		(*pCislo).znamenko = '+';
		(*pCislo).exponent = 0;
		return pCislo;	
	};

Cislo* VratCislo(FILE* soubor)
	{
		Cislo* pCislo = VytvorCislo();
		int stav = 0;
		int index = 0;
		char znak = '0';
			
		if (soubor == NULL) //kontrola, ze soubor neni null
		 	{
				return NULL;
			};	
		//printf("\%s", whiteSpace);
		znak = fgetc(soubor);
			
		while ((stav != 66)	|| (stav != 99)) // kontrola radneho konce cisla nebo chyby v nacteni cisla
			{
				if ((znak == '\n') || (feof(soubor) == 16)) //(znak == EOF));
					{
						switch (stav)
							{
								case 0: SmazCislo(pCislo); return NULL;
								case 1:	SmazCislo(pCislo); return NULL;
								case 2: return pCislo;
								case 3: SmazCislo(pCislo); return NULL;
								
								case 4: return pCislo;
								case 5: return pCislo;
								default: return NULL; 							
							};
					};
				
				stav = Automat(stav,index,znak);
				
				if ((stav == 1) && (strchr("+-",znak)))
				// znamenko zapisuju jen, kdyz prijde + nebo -, stav 1 se muze vratit, i kdyz nacitam za znamenkem same nuly
					{
						ZapisZnamenko(pCislo,znak);
					};
				
				if ((stav == 2) || (stav == 5))
				// vratila se cislice, kterou chci zapsat do mantisy
					{
						VlozDoGumy(((*pCislo).mantisa),index,znak);
						index = index + 1;		
					};
				if (stav == 5)
				// vratila se cislice v desetinne casti, tak musim zvysit zaporny exponent vysledneho cisla
					{
						((*pCislo).exponent) = (((*pCislo).exponent) - 1);
					};
				if (stav == 99) //CHYBA
					{
						SmazCislo(pCislo);
						return NULL;
					};
				if (stav == 66) //radny konec nacteni cisla
					{
						return pCislo;
					};
				znak = fgetc(soubor);	
			};
		return pCislo;
	};

void SmazCislo(Cislo* pCislo)
	{
		if (pCislo == NULL)
			{
				return;
			};
		SmazGumu((*pCislo).mantisa);
		free(pCislo);
		return;	
	};

void ZapisZnamenko(Cislo* pCislo, char znak)
	{
		if (pCislo == NULL)
			{
				pCislo = VytvorCislo();
			};
		(*pCislo).znamenko = znak;
		return;		
	};

int Automat(int stav, int index, char znak)
	{
		switch (stav)
			{
				case 0: //Zacatek
					if ((znak >= '1') && (znak <= '9'))
						{
							stav = 2;
							return stav;	
						};
					switch (znak)
						{
							case ',':
								stav = 3;
								return stav;
							case '+':
								stav = 1;
								return stav;
							case '-':
								stav = 1;
								return stav;
							default:
								return stav;	
						};
				case 1: //Znamenko
					if ((znak >= '1') && (znak <= '9'))
						{
							stav = 2;
							return stav;	
						};
					switch (znak)
						{
							case ',':
								stav = 3;
								return stav;
							case '-':
								stav = 1;
								return stav;
							case ' ':
								stav = 66;
								//KONEC
								return stav;	
							default:
								stav = 99;
								//CHYBA
								return stav;	
						};
				case 2: //Cislice
					if ((znak >= '0') && (znak <= '9'))
						{
							stav = 2;
							return stav;	
						};
					switch (znak)
						{
							case ',':
								stav = 4;
								return stav;
							case ' ':
								stav = 66; //KONEC
								return stav;
							default:
								stav = 99; //CHYBA
								return stav;
						};
				case 3: //Oddelovac na zacatku
					if ((znak >= '1') && (znak <= '9'))
						{
							stav = 5;
							return stav;
						};
					switch (znak)
						{
							case '0':
								return stav;
							case ' ':
								stav = 66; //KONEC
								return stav;
							default:
								stav = 99; //CHYBA
								return stav;	
						};
				case 4: // Oddelovac po nenulove cele casti
					if ((znak >= '0') && (znak <= '9'))
						{
							stav = 5;
							return stav;
						};
					switch (znak)
						{
							case ' ':
								stav = 66;	//KONEC
								return stav;
							default:
								stav = 99;	//CHYBA
								return stav;	
						};
				case 5: // Desetinna cislice
					if ((znak >= '0') && (znak <= '9'))
						{
							stav = 5;
							return stav;
						};
					switch (znak)
						{
							case ' ':
								stav = 66;	//KONEC
								return stav;
							default:
								stav = 99; //CHYBA
								return stav;	
						};
				default:
					return stav; // CHYBA procesu, nebyl rozpoznan stav
			};
	};
	
Cislo* OptimalizujCislo(Cislo* pCislo)
	{
		// odstrani koncove nuly, pokud mantisa nekonci cislici 1-9
		// pri odstranovani nepotrebnych nul upravuje exponent cisla
		return pCislo;
	};

void VypisCislo(Cislo* pVysledek)
	{
		Guma* pivot = (*pVysledek).mantisa;
		int exponent = (*pVysledek).exponent;	
		int delka = DelkaGumy(pivot);
		int index = delka - 1;
		int i = 0;
		char* pCislice = (char*) malloc(sizeof(char));
		*pCislice = '0';
		int carka = 0;
		
		printf("\%c", ((*pVysledek).znamenko));
		
		if (exponent < 0)
			{
				carka = index - abs(exponent);	
				for (i = 0; i <= carka; i++)
					{
						Vrat(pivot,i,pCislice);
						printf("\%c", (*pCislice));				
					};
				printf("\%c", ',');
				for (i = (carka+1); i <= index; i++)
					{
						Vrat(pivot,i,pCislice);
						printf("\%c", (*pCislice));				
					};

			};

		if (exponent >= 0)
			{
				for (i = 0; i <= index; i++)
					{
						Vrat(pivot,i,pCislice);
						printf("\%c", (*pCislice));				
					};
			
				for (i = 0; i < exponent; i++)
					{
						printf("\%c", '0');				
					};

			};
		return;
	};

