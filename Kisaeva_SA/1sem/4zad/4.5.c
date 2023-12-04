// 4.5  Написать функции, позволяющие работать с целым числом (long) как с “массивом” четырех однобайтовых чисел (char).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool opred_bit(unsigned long ch, int j);
void write(unsigned long ch); 
unsigned long i_byte(unsigned long N, int i); // определяет байт под номером i
unsigned long rewrite(unsigned long N, unsigned char Q, int i);


void write(unsigned long ch) {
    int max_bit = sizeof(ch) * 8;  // 4 * 8
	
	for (int j = max_bit - 1; j >= 0; j--) {
		if ( (((j + 1) % 8) == 0) && (j != (max_bit - 1)) ) {
			printf (" ");
		}
		if (opred_bit(ch, j) == false) {
			printf("0");
        }
		else {
			printf("1");
		}
	}
	printf ("\n");
}

bool opred_bit(unsigned long ch, int j) {
	return (ch & (1 << j));
}

unsigned long i_byte(unsigned long N,  int i) {
	unsigned long answer;

	answer = N << (8 * (sizeof(N) - 1 - i)); // сдвинули нужный байт в самый левый байт(третий) (чистка левых байтов (относит. нужного байта))
	answer = answer >> 8*(sizeof(N) - 1); // сделали нужный байт самым правым(нулевым) (чистка правых байтов (относит. нужного байта))

	return answer;
}

unsigned long rewrite(unsigned long N, unsigned char Q, int i) {
	unsigned long nov_byte, star_byte, izmen_N;
	
	nov_byte = Q << (8 * i); 
	star_byte = N << (8 * (sizeof(N) - 1 - i));
	star_byte = star_byte >> 8*(sizeof(N) - 1);
	star_byte = star_byte << (8 * i);
	izmen_N = N - star_byte + nov_byte;
	
	return izmen_N;
}


int main (void) {
	unsigned long N; // считываем число с консоли
	int act; // номер команды
	int i; // индекс(номер) байта
	unsigned char Q; // число, на которое мы заменяем i-ый байт
	unsigned int answer;

	printf("vvedite chislo N \n");
	if (scanf ("%lu", &N) != 1) {
		printf ("not korr N \n");
		return -1;
	}
	
	printf("VUBERITE KOMANDU:\n");
	printf ("1 - vuzov znacheniya v i-tom byte \n");
	printf ("2 - zapis' znacheniya chisla Q v i-tom byte \n");

	
	if ((scanf ("%d", &act) != 1) || ((act != 1) && (act != 2))) {
		printf ("not korr komanda\n");
		return -1;
	}
	
	if (act == 1) {
		printf ("vvedite index byte i ( i = {0,1,2,3} )\n");
		if ((scanf ("%d", &i) != 1) || (i > 3) || (i < 0)) {
			printf("not korr index i\n");
			return -1;
		}
		
		answer = i_byte(N, i);
		
		printf ("bulo chislo N:\n");
		write(N);
		
		printf("vuzvali byte pod nomerom i = %d\n", i);
		write(answer);
	}

	if (act == 2) {
		printf ("vvedite natur chislo Q < 256\n");
        if ((scanf ("%hhu", &Q) != 1)) {
			printf ("not korr Q \n");
			return -1;
		}
		
		printf ("vvedite index byte i ( i = {0,1,2,3} )\n");
		if ((scanf ("%d", &i) != 1) || (i > 3)) {
			printf("not korr index i");
			return -1;
		}
		
		answer = rewrite(N, Q, i);
		
		printf("bulo chislo N: \n");
		write(N);
		
		printf("vstavili chislo Q: \n");
		write(Q);
		
		printf("na byte pod nomerom i = %d\n", i);
		
		printf("itog: \n");
		write(answer);
	}

	return 0;
}
