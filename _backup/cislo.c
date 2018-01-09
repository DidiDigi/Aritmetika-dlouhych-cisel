#include "cislo.h"

Cislo* VytvorCislo(void)
	{
		Cislo* pCislo = NULL; 
		
		pCislo = (Cislo*) malloc(sizeof(Cislo));
		(*pCislo).mantisa = VytvorGumu(10);
		VlozDoGumy((&(*pCislo).mantisa), 0, '0');
		(*pCislo).exponent = VytvorGumu(10);
		VlozDoGumy(&((*pCislo).exponent), 0, '0');
		(*pCislo).znamenkoMan = '+';
		(*pCislo).znamenkoExp = '+';
		return pCislo;	
	};

Cislo* VratCislo(FILE* soubor)
	{
		Cislo* pCislo = VytvorCislo();
		Cislo** ppCislo = &pCislo;
		int stav = 0;
		int index = 0;
		char znak = '0';
		char kam = '0';
			
		if (soubor == NULL) //kontrola, ze soubor neni null
		 	{
				return NULL;
			};	
		//printf("\%s", whiteSpace);
		znak = fgetc(soubor);
			
		while ((stav != 66)	|| (stav != 99)) // kontrola radneho konce cisla nebo chyby v nacteni cisla
			{
				if ((znak == '\n') || (feof(soubor) == 16))
					{
						switch (stav)
							{
								case 0: SmazCislo(ppCislo); return NULL;
								case 1:	SmazCislo(ppCislo); return NULL;
								case 2: return pCislo;
								case 3: SmazCislo(ppCislo); return NULL;
								case 4: return pCislo;
								case 5: SmazCislo(ppCislo); return NULL;
								default: return NULL; 							
							};
					};
				
				stav = Automat(stav,index,znak);
				
				if ((stav == 1) && (strchr("+-",znak)))
				// znamenko zapisuju jen, kdyz prijde + nebo -, stav 1 se muze vratit, i kdyz nacitam za znamenkem same nuly
					{
						kam = 'M';
						ZapisZnamenko(ppCislo,kam,znak);
					};
				
				if ((stav == 2) || (stav == 5))
				// vratila se cislice, kterou chci zapsat do mantisy
					{
						VlozDoGumy(&((*pCislo).mantisa),index,znak);
						index = index + 1;		
					};
				if (stav == 5)
				// vratila se cislice v desetinne casti, tak musim zvysit zaporny exponent vysledneho cisla
					{
						Inkrement(&((*pCislo).exponent));
					};
				if (stav == 99) //CHYBA
					{
						SmazCislo(ppCislo);
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

void SmazCislo(Cislo** ppCislo)
	{
		if (ppCislo == NULL)
			{
				return;
			};
		SmazGumu(&((**ppCislo).mantisa));
		SmazGumu(&((**ppCislo).exponent));
		free(*ppCislo);
		return;	
	};

void ZapisZnamenko(Cislo** ppCislo, char kam, char znak)
	{
		if (ppCislo == NULL)
			{
				*ppCislo = VytvorCislo();
			};
		if (kam == 'M')
			{
				(**ppCislo).znamenkoMan = znak;	
			};
		if (kam == 'E')
			{
				(**ppCislo).znamenkoExp = znak;	
			};	
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
	
Cislo* OptimalizujCislo(Cislo** ppCislo)
	{
		// odstrani koncove nuly, pokud mantisa nekonci cislici 1-9
		// pri odstranovani nepotrebnych nul upravuje exponent cisla
		return *ppCislo;
	};

void VypisCislo(Cislo** ppVysledek)
	{
		printf("%c", (**ppVysledek).znamenkoMan);
		//podle exponentu celou cast cisla
		//desetinna carka
		//desetinna cast cisla
		VypisGumu((**ppVysledek).mantisa);
		return;
	};

