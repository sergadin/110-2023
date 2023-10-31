#include <stdio.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int compute_define (FILE *input, FILE *output, ERR *error);	 //определяет является ли последовательность убыващей или ворастащей
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int compute_define (FILE *input, FILE *output, ERR *error)
{
        int answ;
        double curr = 0, prev = 0;
        test_file_input_double ( input, & curr, error );
        prev = curr;
	test_file_input_double ( input, & curr, error );
	if ( prev < curr ) { answ = 1; }
	else { answ = -1; }	
        while ((test_file_input_double ( input, & curr, error ) == 0) && (int) curr != 0)
	{
		if ( ( prev > curr ) && answ == 1 ) { 
			fprintf ( output , " последовательность ни возрастащая, ни убыващая " );
			return 1;
		}
		else { if ( ( prev < curr ) && answ == -1 ) { 
			fprintf ( output , " последовательность ни возрастащая, ни убыващая " );
			return 1;
		}
		}
		prev = curr;
	}
	if ( answ == 1 ) { fprintf ( output , " последовательность является возрастащей " ) ; }
	else { fprintf ( output , " последовательность является убыващей " ) ; }
	return 0;
}


int main (void)
{
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file ( input, & error );
        test_file ( output, & error );
        compute_define (input, output, & error);
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

