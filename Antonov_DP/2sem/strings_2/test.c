#include "del_comment.h"


int main(void)
{
	ERR err = OK;
	FILE *input;
	char *str;
	char start[] = "/*";
	char end[] = "*/";
	size_t len = 1;
	input = fopen("input.txt", "r");
	str = (char *)malloc(len * sizeof(char));
	getline(&str, &len, input);
	del_comment(str, start, end, &err);
	fclose(input);
	return 0;
}
