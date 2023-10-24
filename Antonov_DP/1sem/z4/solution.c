#include <stdio.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
long int compute_quan (FILE *input, ERR *error); //высчитывание кол-ва чисел больших предыдущего
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла

long int compute_quan (FILE *input, ERR *error)
{
        long int quan = 0, answ = 0;
        double curr = 0, prev = 0;
        test_file_input_double ( input, & curr, error );
        prev = curr;
        while ((test_file_input_double ( input, & curr, error ) == 0) && (int) curr != 0)
        {
                if ( prev < curr ) { quan += 1; }
	       prev = curr;	       
        }
        answ = quan;
        return answ;
}


int main (void)
{
        long int answ = 0;
        ERR error = OK;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file ( input, & error );
        test_file ( output, & error );
        answ = compute_quan (input, & error);
        fprintf (output, "answ = %ld \n", answ);
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
