#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "is_zero.h"


//Предел количества исполнений функции f
#define LIMIT 1000


int number_when_zero(Rfun f, R_Rfun g, double x, Error *error) {
	
	//переменные, указывающие на предыдущий и настоящий элемент последовательности f(f(....f(x)))
	double past_value_of_sequency = (*f)(x);
	double real_value_of_sequency = (*f)(past_value_of_sequency);
	double for_val_exchange;
	
	for (int i = 0; i < LIMIT; i ++) {
	
		if ((*g)(past_value_of_sequency, real_value_of_sequency) == 0) {
			*error = OK;
			return i + 2; //возвращаем число вызовов функции f, прибавляем 2 тк первые значения уже были вычислены вне цикла
		}
		
		for_val_exchange = real_value_of_sequency;
		past_value_of_sequency = real_value_of_sequency;
		real_value_of_sequency = (*f)(for_val_exchange);
	}
	
	*error = OP_LIMIT; //Превышен предел исполнений f
	
	return -1;	
}
	
	
		
		
		
	
	
