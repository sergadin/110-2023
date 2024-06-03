#include "str_property.h"


int main(void)
{
	ERR err = OK;
	FILE *input;
	char *str;
	size_t len = 1;
	input = fopen("input.txt", "r");
	str = (char *)malloc(len * sizeof(char));
	getline(&str, &len, input);
	str_property(str, &err);
	return 0;
}
