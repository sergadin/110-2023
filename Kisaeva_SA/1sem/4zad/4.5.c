// 4.5  Написать функции, позволяющие работать с целым числом (long) как с “массивом” четырех однобайтовых чисел (char).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool opred_bit(int ch, int j);
void write(int ch); 
unsigned int i_byte(unsigned int N, int i); // определяет байт под номером i
unsigned int rewrite(unsigned int N, unsigned int Q, int i);


void write(int ch) {
    int max_bit = sizeof(int) * 8;  // 4 * 8
	
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

bool opred_bit(int ch, int j) {
	return (ch & (1 << j));
}

unsigned int i_byte(unsigned int N,  int i) {
	unsigned int answer;

	answer = N << (8 * (3 - i)); // сдвинули нужный байт в самый левый байт(третий) (чистка левых байтов (относит. нужного байта))
	answer = answer >> 24; // сделали нужный байт самым правым(нулевым) (чистка правых байтов (относит. нужного байта))

	return answer;
}

unsigned int rewrite(unsigned int N, unsigned int Q, int i) {
	unsigned int nov_byte, star_byte, izmen_N;
	
	nov_byte = Q << (8 * i); 
	star_byte = N << (8 * (3 - i));
	star_byte = star_byte >> 24;
	star_byte = star_byte << (8 * i);
	izmen_N = N - star_byte + nov_byte;
	
	return izmen_N;
}


int main (void) {
	unsigned int N; // считываем число с консоли
	int act; // номер команды
	int i; // индекс(номер) байта
	unsigned int Q; // число, на которое мы заменяем i-ый байт  (Q =[0;255])
	unsigned int answer;

	printf("vvedite chislo N \n");
	if (scanf ("%u", &N) != 1) {
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
			printf("not korr index i");
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
        if ((scanf ("%u", &Q) != 1) || (Q >= 256) || (Q <= 0)) {
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