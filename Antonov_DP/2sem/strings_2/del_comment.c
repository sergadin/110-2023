#include "del_comment.h"



static int str2_in_str1(char *str1, int n, char *str2);

static int str2_in_str1(char *str1, int n, char *str2)
{
	int i = 0;
	while ((str1[n + i] != 0) && (str2[i] != 0))
	{
		if(str1[n + i] != str2[i])	
		{
			return -1;
		}
		i++;
	}
	if ((str1[n + i] == 0) && (str2[i] != 0))
	{
		return -1;
	}
	return 0;
}

static int del_com(char *str, int start, int end);

static int del_com(char *str, int start, int end)
{
	int i = 1;
	while (str[end + i] != 0)
	{
		str[start + i - 1] = str[end + i];
		i++;
	}
	str[start + i - 1] = str[end + i];
	return 0;
}


int del_comment (char *str, char *start, char *end, FILE *output, ERR *err)
{
	if ((str == NULL) || (str[0] == 0))
	{
		*err = ER_NL;
		printf("строка - пуста, ошибка \n");
		return -1;
	}
	int i = 0, count = 0, start_i, end_i, len1 = strlen(start), len2 = strlen(end);
	while (str[i] != 0)
	{
		if (str2_in_str1(str, i, start) == 0)
		{
			count++;
			if(count == 1)
			{
				start_i = i;
			}
			i += (len1 - 1);
		}
		else if ((str2_in_str1(str, i, end) == 0) && (count == 1))
		{
			end_i = i + len2 - 1;
			del_com(str, start_i, end_i);
			i = start_i - 1;
			count --;
		}
		else if (str2_in_str1(str, i, end) == 0)
		{
			i += (len2 - 1);
			count --;
		}
		i++;
	}
	fprintf(output, "%s", str);
	return 0;
}
