#include <stdio.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
double compute_max_dev (FILE *input, ERR *error);      //вычисляет максимальное отклонение от среднего арифметического последовательности
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

double compute_max_dev (FILE *input, ERR *error)
{
        int quan = 1;
        double curr = 0, max, min, summ, aver;
        test_file_input_double(input, & curr, error);
	max = curr;
	min = curr;
	summ = curr;
        while ((test_file_input_double(input, & curr, error) == 0))
        {
                summ += curr;
		if (curr > max) {max = curr;}
		if (curr < min) {min = curr;}
		quan ++;
        }
        aver = summ / quan;
	if (max - aver < aver - min) {return aver - min;}
	else {return max - aver;}
}


int main (void)
{
        double max_dev;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
        max_dev = compute_max_dev(input, &error);
        fprintf (output, "answ = %f \n", max_dev);
        fclose (input);
        fclose (output);
        if (error == E_DATA)
        {
                printf ( "ошибка при открытии файла \n" );
                        return -1;
        }
        if (error == E_IO)
        {
                printf ( "ошибка при чтении файла \n" );
                return -1;
        }
        return 0;
}
