#include <stdio.h>
#include <string.h>
#include <math.h>
#define VOZR 1
#define YBIV -1
#define NIKAK 0

int OSHIBKA = 0;

int vozr_ili_ybiv_posl(FILE *f); 


int vozr_ili_ybiv_posl(FILE *f) 
{
	//Определить является ли последовательность возрастающей, убывающей

	int vozr = 0, ybiv = 0, schit_tek, kol_el;
	double tek, pred;

	if (fscanf(f, "%lf", &pred) != 1) 
	{
		OSHIBKA = -1;
		return -1;
	}
	
	kol_el = 1;
	
	while ((schit_tek = fscanf(f, "%lf", &tek)) != EOF) {
		if (schit_tek != 1) {
			OSHIBKA = -1;
			return -1;
		}
		kol_el++;
		if (tek > pred) {
			vozr++;
		} 
		else if (tek < pred) {
            ybiv++;
        }
		pred = tek;
	}
	
	if (kol_el == vozr - 1){
        return VOZR;
    }
    if (kol_el == ybiv - 1){
        return YBIV;
    }
    else {
        return NIKAK;
    }
}

int main(void) {
	int opred_posl;
	FILE *f = fopen("1.8.txt", "r");
	if (f == NULL) {
		printf("error opening the file\n"); 
		return -1;
	}

	opred_posl = vozr_ili_ybiv_posl(f);

	if (opred_posl == OSHIBKA) {
		printf("error\n"); 
		return -1;
	}
	
	if (opred_posl == VOZR) {
		printf("Последовательность возрастает\n");
	} 
	else if (opred_posl == YBIV) {
		printf("Последовательность убывает\n");
	}
    else if (opred_posl == NIKAK) {
		printf("Последовательность не убывает и не возрастает\n");
	}

	fclose(f); 
	return 0;
}







/*
int vozr_ili_ybiv_posl(FILE *f) 
{
	//Определить является ли последовательность возрастающей, убывающей

	int vozr = 0, ybiv = 0, schit_tek, monot = 0;
	double tek, pred;

	if (fscanf(f, "%lf", &tek) != 1) 
	{
		OSHIBKA = -1;
		return -1;
	}
	
	while ((schit_tek = fscanf(f, "%lf", &tek)) != EOF) {
		if (schit_tek != 1) {
			OSHIBKA = -1;
			return -1;
		}
		if (tek > pred) {
			vozr++;
		} 
		else if (tek < pred) {
            ybiv++;
        }
        else if (tek == pred) {
			monot++;
		} 
		pred = tek;
	}
	
	if ((vozr != 0) && (ybiv == 0)){
        return VOZR;
    }
    else if ((vozr == 0) && (ybiv != 0)){
        return VOZR;
    }
    else if ((vozr == 0) && (ybiv == 0)){
        return MONOT;
    }
    else {
        return NIKAK;
    }
}
*/