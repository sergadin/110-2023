#include <stdio.h>

typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int compute_max_len (FILE *input, ERR *error);      //вычисляет кол-во элементов самой длинной подпоследовательности
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int compute_max_len (FILE *input, ERR *error)
{
        int len = 1, quan = 1;
        double curr = 0, prev = 0;
        test_file_input_double ( input, & curr, error );
        prev = curr;
        while ((test_file_input_double ( input, & curr, error ) == 0) && (int) curr != 0)
	{
		if ( prev <= curr ) { quan++; }
		else { if ( len < quan ) { len = quan;}
		quan = 1;}
		prev = curr;
	}
	return len;
}


int main (void)
{
	int answ;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file ( input, & error );
        test_file ( output, & error );
        answ = compute_max_len (input, & error);
	fprintf ( output, "answ = %d \n", answ);
        fclose (input);
        fclose (output);
        if ( error == E_DATA)
        {
                printf ( "ошибка при открытии файла" );
                        return -1;
        }
        if ( error == E_IO)
        {
                printf ( "ошибка при чтении файла" );
                return -1;
        }
        return 0;
}

