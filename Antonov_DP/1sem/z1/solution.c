#include <stdio.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);	//проверяет нормально ли открылся файл
double compute_midar (FILE *input, ERR *error);	//высчитывание среднего арифметического
int test_file_input_double (FILE *input, double *num, ERR *error);	//проверяет правильность ввода из файла вещественного числа

double compute_midar (FILE *input, ERR *error)
{
	int quan = 0;
	double curr = 0, summ = 0, answ = 0;
	test_file_input_double ( input, & curr, error );
	summ = curr;
	quan = 1;
	while ((test_file_input_double ( input, & curr, error ) == 0) && (int) curr != 0)
	{
		summ += curr;
		quan += 1;
	}
	answ = summ / quan;
	return answ;
}


int main (void)
{
	double answ = 0;
	ERR error = OK;
	FILE *input, *output;
	input = fopen ("input.txt", "r");
	output = fopen ("output.txt", "w");
	test_file ( input, & error );
	test_file ( output, & error );
	answ = compute_midar (input, & error);
	fprintf (output, "answ = %lf \n", answ);
	fclose (input);
	fclose (output);
	if ( error == E_DATA)
	{
		printf ( "ошибка при открытии файла" );
			return -1;
	}
	if ( error == E_IO)
	{
		printf ( "ошибка при чтении файла");
		return -1;
	}
	return 0;
}
