//указатели на функции
//4. Вычисление обобщённого скалярного произведения двух векторов целых чисел 
//   относительно произвольных функций сложения и умножения

#include <stdio.h>
#include <stdlib.h>
#include "scalar_product.h"

static int calc_summ(int a, int b); // функция для вычисление сложения
static int calc_mult(int a, int b); // функция для вычисление произведения

static int calc_summ(int a, int b) {
	return (a + b);
}

static int calc_mult(int a, int b) {
	return (a * b);
}


int main(void) {
	int result; // результат скалярного произведения векторов
	int n = 4; // размерность векторного пространства
	int vector1[4] = {4,2,4,2}; // первый вектор, его координаты
	int vector2[4] = {1,3,1,10}; // второй вектор, его координаты
	
	result = scalar_product(n, vector1, vector2, calc_summ, calc_mult); //подсчитываем скалярное произведение с помощью функции scalar_product
	printf("the result of the scalar product: %d\n", result);
	return 0;
}