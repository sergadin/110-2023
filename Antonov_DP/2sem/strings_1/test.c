#include "str_property.h"


int main(void)
{
	ERR err;
	FILE *input;
	char *str;
	size_t len = 1;
	int count;
	str = (char *)malloc(len * sizeof(char));
	input = fopen("input2.txt", "r");
	getline(&str, &len, input);
	str[strlen(str) - 1] = 0;
	str_property(str, &err);
	free(str);
	fclose(input);
	return 0;
}
