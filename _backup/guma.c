#include "guma.h"

Guma* VytvorGumu(int delka)
	{
		Guma* pGuma = (Guma*) malloc(sizeof(Guma));
		
		//printf("\nvytvarim blok velikosti %d\n", delka);
		(*pGuma).znaky = (char*) malloc(sizeof(char)*delka);  // podle pouziti by tu bylo dobre plnit pole nulama, abych jednou nevypisovala kraviny
		(*pGuma).delka = delka;
		(*pGuma).ukazovatko = 0;
		(*pGuma).dalsi = NULL;
		return pGuma;
	};

void SmazGumu(Guma** ppGuma)
	{
		if (*ppGuma == NULL)
			{
				return;
			};
		
		free((**ppGuma).znaky);
		SmazGumu(&((**ppGuma).dalsi));
		free(*ppGuma);
		*ppGuma = NULL;
		return;
	};
	
void VlozDoGumy(Guma** ppGuma, int index, char znak)
	{
		Guma* pivot = *ppGuma; 
		
		if (pivot == NULL) //pokud nem�m ��dnou Gumu
			{
				*ppGuma = VytvorGumu((10)); // vytv���m Gumu a vrac�m ukazatel na Gumu, v�t�� velikost ne� na jak� m�sto zapisuju
				pivot = *ppGuma;  // nasatvujeme pivot na nov� vytvo�enou Gumu	
			};
		
		while (index >= ((*pivot).delka))	//kontrola, do jak� ��sti Gumy budu vkl�dat char
			{
				index = index - (*pivot).delka;
				if ((*pivot).dalsi == NULL)
					{
						pivot = (*pivot).dalsi = VytvorGumu((*pivot).delka*2);
					}
					else
						{
							pivot = (*pivot).dalsi;	
						};
			};
		
		(*pivot).ukazovatko = index;	// pri vypisu Gumy budu potrebovat vedet, kde skoncit v posledni casti
		(*pivot).znaky[index] = znak;
		return;
	};
	
void VlozDoGumyZleva(Guma** ppGuma, int index, char znak)
	{
		Guma* pivot = *ppGuma; 
		
		if (pivot == NULL) //pokud nem�m ��dnou Gumu
			{
				*ppGuma = VytvorGumu((10)); // vytv���m Gumu a vrac�m ukazatel na Gumu, v�t�� velikost ne� na jak� m�sto zapisuju
				pivot = *ppGuma;  // nasatvujeme pivot na nov� vytvo�enou Gumu	
			};
		
		while (index >= ((*pivot).delka))	//kontrola, do jak� ��sti Gumy budu vkl�dat char
			{
				index = index - (*pivot).delka;
				if ((*pivot).dalsi == NULL)
					{
						pivot = (*pivot).dalsi = VytvorGumu((*pivot).delka*2);
					}
					else
						{
							pivot = (*pivot).dalsi;	
						};
			};
	
		(*pivot).znaky[index] = znak;
		if (index >= ((*pivot).ukazovatko))
			{
				(*pivot).ukazovatko = index;	// pri vypisu Gumy budu potrebovat vedet, kde skoncit v posledni casti
			};
		return;
	};
		
void VypisGumu(Guma* pGuma)
	{
		Guma* pivot = pGuma;
		int i = 0;
		
		if (pivot == NULL)
			{
				//printf("Nen� co vypsat.");
				return;
			};
		
		int j = 0;
		
		while (pivot != NULL)
			{
				//printf("\njsem v bloku %d\n", j++);
				for (i = 0; i <= ((*pivot).ukazovatko); i++)
					{
						printf("\%c", (*pivot).znaky[i]);
					};
				pivot = (*pivot).dalsi;
			};
		return;
	};
	
void Vrat(Guma* pGuma, int index, char* znak)
	{
		Guma* pivot = pGuma;
		
		if (znak == NULL)
			{
				return;
			}; 
		
		if (pivot == NULL) //pokud nem�m ��dnou Gumu
			{
				//printf("Nen� co vypsat.");
				return;	
			};
		
		while (index >= ((*pivot).delka))	//kontrola, do jak� ��sti Gumy budu vkl�dat char
			{
				index = index - (*pivot).delka;
				if ((*pivot).dalsi == NULL)
					{
						return;
					}
					else
						{
							pivot = (*pivot).dalsi;
						};
			};
		if ((*pivot).ukazovatko < index)
			{
				return;
			};
			
		*znak = (*pivot).znaky[index];
		return;
	};
	
int DelkaGumy(Guma* pGuma)
	{
		int delka = 0;
		Guma* pivot = pGuma;
		
		while (pivot != NULL)
		{
			delka = delka + ((*pivot).ukazovatko) + 1;
			pivot = ((*pivot).dalsi);
		};
		return delka;
	};

char* GumaNaRetezec(Guma* pGuma)
	{
		Guma* pivot = pGuma;
		int i = 0;
		int delka = DelkaGumy(pGuma);
		
		char* retezec = (char*) malloc(sizeof(char)*delka + 1);
		retezec[delka] = '\0';
		
		if (pivot == NULL)
			{
				return retezec;
			};
		
		int j = 0;
		
		while (pivot != NULL)
			{
				for (i = 0; i <= (*pivot).ukazovatko; i++)
					{
						retezec[j] = (*pivot).znaky[i];
						j++;
					};
				pivot = (*pivot).dalsi;
			};
		return retezec;
	};
	
int GumaPridejZleva(Guma** ppGuma)
	{
		Guma* pivot = *ppGuma;
		Guma* novy = VytvorGumu(1);
		
		(*novy).dalsi = pivot;
		pivot = novy;
		return 0;
	};

int GumaOdeberZleva(Guma** ppGuma)
	{
		Guma* pivot = *ppGuma;
		Guma* novy = NULL;
		unsigned int delka = (DelkaGumy(pivot) - 1);
		char* odkud = 0;
		char* kam = 0;
		
		novy = VytvorGumu(delka);
		
		(*novy).dalsi = (*pivot).dalsi;
		(*novy).ukazovatko = ((*pivot).ukazovatko - 1);
		
		odkud = (((*pivot).znaky)+1);
		kam = (((*novy).znaky));
		memcpy(kam,odkud,delka);
		*ppGuma = novy;
		SmazGumu(&pivot);
		return 0;
	};

Guma* GumaPridejZprava(Guma** ppGuma)
	{
		Guma* pivot = *ppGuma;
		
		while (((*pivot).dalsi) != NULL)
			{
				pivot = (*pivot).dalsi;	
			} 
		
		if (((*pivot).ukazovatko) == (((*pivot).delka)-1))
			{
				Guma* novy = VytvorGumu(1);
				(*pivot).dalsi = novy;
			}
		return pivot;
	};
