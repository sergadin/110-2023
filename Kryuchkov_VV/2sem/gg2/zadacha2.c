#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char *str;
    int len;
} StrLenPair;

int compareStrLenPairs(const void *a, const void *b) 
{
    StrLenPair *strPairA = (StrLenPair *)a;
    StrLenPair *strPairB = (StrLenPair *)b;

    if (strPairA->len != strPairB->len) 
    {
        return strPairB->len - strPairA->len;
    } 
    
    else 
    {
        return strcmp(strPairB->str, strPairA->str);
    }
}

int main() 
{
    int numStrings;

    if (scanf("%d", &numStrings) != 1 || numStrings <= 0) {
        fprintf(stderr, "Неверный ввод.\n");
        return 1;
    }

    StrLenPair *strings = (StrLenPair *)malloc(numStrings * sizeof(StrLenPair));
    if (strings == NULL) 
    {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return 1;
    }

    for (int i = 0; i < numStrings; i++) {
        char str[100000];
        if (scanf("%99s", str) != 1) 
        {
            fprintf(stderr, "Ошибка ввода.\n");
            return 1;
        }
        strings[i].str = strdup(str);
        if (strings[i].str == NULL) 
        {
            fprintf(stderr, "Ошибка выделения памяти.\n");
            return 1;
        }
        strings[i].len = strlen(str);
    }

    qsort(strings, numStrings, sizeof(StrLenPair), compareStrLenPairs);

    printf("%s", strings[0].str);

	for (int i = 1; i < numStrings; ++i)
	{
		if (strings[i].len == strings[0].len) 
        {
			printf("%s", strings[i].str);
		}
	}
    printf("\n");

    for (int i = 0; i < numStrings; i++) 
    {
        free(strings[i].str);
    }
    free(strings);

    return 0;
}