#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE (sizeof(unsigned int)*8)


unsigned int perestavit_v_obr_poradke(unsigned int num);

// переставляет байты целого числа в обратном порядке
unsigned int perestavit_v_obr_poradke(unsigned int num)
{
unsigned int result = 0;
int i;
for (i = 0; i < SIZE; i += 8)
{
    result = result << 8; // сдвигаем результат на 8 бит
    result |= (num >> i) & 0xFF; // добавляем очередные 8 бит из исходного числа
}

return result;
}

int main(void)
{
unsigned int num;
unsigned int answ;
printf("Введите целое число:");
scanf("%u", &num);

answ = perestavit_v_obr_poradke(num);
printf("Число %u после перестановки байт в обратном порядке: %u\n", num, answ);

return 0;
}