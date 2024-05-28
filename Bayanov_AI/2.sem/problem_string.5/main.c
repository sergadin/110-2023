
#include "./utils/utils.h"

struct testing
{
  const char *input_name;
  const char *output_name;
};

int main (void)
{
  FILE *input = NULL;
  FILE *output = NULL;

  struct testing test_number[4] = {
	{"Test1_input.txt", "Test1_output.txt"},
	{"Test2_input.txt", "Test2_output.txt"},
	{"Test3_input.txt", "Test3_output.txt"},
	{"Test4_input.txt", "Test4_output.txt"}
  };

  for (int i = 0; i < 4; i++)
	{
		input = fopen (test_number[i].input_name, "r");
		if (input == NULL)
		{
			continue;
		}

		output = fopen(test_number[i].output_name, "w");
		if (output == NULL )
		{
        	fclose(input);
			continue;
		}  
	
	function_string5 (output, input);
	
    fclose(input);
    fclose(output);
    
	}

  return 0;
}