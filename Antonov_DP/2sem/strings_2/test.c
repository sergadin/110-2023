#include "del_comment.h"

typedef struct testcase {
	char *input;
	char *output;
	char *start;
	char *end;
	char *answer;
	ERR error;
} testcase;

int main(void)
{
	struct testcase tests[] = {
		{"input1.txt", "output1.txt", "/*", "*/", " ", ER_NL},
		{"input2.txt", "output2.txt", "(", ")", "ac", OK},
		{"input3.txt", "output3.txt", "[", "]", "aa bb cc", OK}
	};
	ERR err = OK;
	FILE *input, *output;
	char *str;
	size_t len = 1;
	for (int i = 0; i < 3; i++)
	{
		err = OK;
		input = fopen(tests[i].input, "r");
		output = fopen(tests[i].output, "w");
		str = (char *)malloc(len * sizeof(char));
		getline(&str, &len, input);
		del_comment(str, tests[i].start, tests[i].end, output, &err);
		printf("%d \n", err);
		if ((err == tests[i].error) && (strcmp(str, tests[i].answer)))
		{
			printf("test %d correct\n", i);
		}
		else
		{
			printf("test %d not correct\n", i);
		}
		free(str);
		fclose(input);
		fclose(output);
	}
	return 0;
}
