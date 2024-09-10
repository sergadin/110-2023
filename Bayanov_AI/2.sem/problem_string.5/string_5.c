#include "./utils/utils.h"


void function_string5 (FILE *output, FILE *input)
{
	int symbols_size = 256;
   	int *symbol_frequency = NULL;
   	int	current_length = 0;
   	int	counter_sym = 0;
   	int word_count = 0;
	char symbol;
	int mid = 0;
	int max = 0;
	int min = 0;
	int check_gap = 2;
	symbol_frequency = (int*) malloc ((symbols_size) * sizeof(int));
	for(int i = 0; i < symbols_size; i++)
		symbol_frequency[i] = 0;

	while(!feof(input)) 
	{
		current_length = 0;
		check_gap = 2;

		while(fscanf(input, "%c", &symbol) == 1 && symbol != '\n') 
		{ 
			symbol_frequency[(int)symbol]++;
			if((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) 
			{
				    current_length++;
				    check_gap = 0;
			}
			else 
			{
				check_gap++;
				if(check_gap == 1) 
				{ 
					if(word_count == 0) 
					{
						min = current_length;
						max = current_length;
						mid = current_length;
						word_count++;
						current_length = 0;
						continue;
					}
				    word_count++;
					if(max < current_length) 
						max = current_length;
					if(min > current_length)
						min = current_length;
					mid += current_length;
				}
				current_length = 0; 
			}
		}
			check_gap++;	
			if(check_gap == 1) 
			{
				if(word_count == 0) 
				{
					min = current_length;
					max = current_length;
					mid = current_length;
					word_count++;
					current_length = 0;
					continue;
				}
				word_count++;
				if(max < current_length)
					max = current_length;
				if(min > current_length)
					min = current_length;
				mid += current_length;
			}
	}
	fprintf(output, "Maximum word length: %d\n", max);
	fprintf(output, "Minimum word length: %d\n", min);
	if(word_count != 0)
	fprintf(output, "Average word length: %d\n", mid / word_count);
	
	for(int i = 0; i < symbols_size; i++)
		counter_sym += symbol_frequency[i];
	
	for(int i = 0; i < symbols_size; i++)
	{
		if( (char)i != '\0' && (char)i != '\n' && symbol_frequency[i] != 0)
			fprintf(output, "Frequency of symbol '%c': %lf percent \n", i, (double)symbol_frequency[i]*100/counter_sym);
	}
	free(symbol_frequency);
}
