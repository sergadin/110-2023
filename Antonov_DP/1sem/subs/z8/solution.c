#include <stdio.h>
#include <math.h>
  
typedef enum { OK = 0, E_DATA, E_IO } ERR;

int test_file (FILE *input, ERR *error);        //проверяет нормально ли открылся файл
int define_subs (FILE *input, ERR *error);	 //определяет является ли последовательность убыващей или ворастащей
int test_file_input_double (FILE *input, double *num, ERR *error);      //проверяет правильность ввода из файла вещественного числа

int define_subs (FILE *input, ERR *error)
{
        int crease;
        double curr = 0, prev = 0;
        test_file_input_double(input, &curr, error);
        prev = curr;
	test_file_input_double(input, &curr, error);
	if ( prev < curr ) { crease = 1; }
	else if ( fabs(curr - prev) < 0.01 ) { return 0; }
	else { crease = -1; }
        while ((test_file_input_double (input, &curr, error) == 0))
	{
		if ( ( prev >= curr ) && crease == 1 ) { return 0; }
		else  if ( ( prev <= curr ) && crease == -1 ) { return 0; }
		prev = curr;
	}
	return crease;
}


int main (void)
{
        ERR error = OK;
	int crease;
        FILE *input, *output;
        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");
        test_file(input, &error);
        test_file(output, &error);
        crease = define_subs (input, &error);
	if ( crease == 1 ) { fprintf(output, "последовательность является возрастающей."); }
	else if ( crease == -1 ) { fprintf(output, "последовательность является убывающей."); }
	else {
		fprintf (output, "последовательность не убывающая и не возрастающая."); }
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
