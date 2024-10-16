#include "strings.h"

void solution(FILE *input, FILE *output)
{
    fseek(input, 0, SEEK_END);
    long fileSize = ftell(input);
    fseek(input, 0, SEEK_SET);
    error_code = OK;

    if (fileSize == 0) {
        printf( "file is empty");
        error_code = ERR;
    }

    char *file = (char *)malloc(fileSize + 1);
    if (file == NULL) {
        printf("Failed to allocate memory");
        error_code = ERR;
    }


    while(fgets(file, fileSize + 1, input)){
        int i = 0;
        while (file[i] != '\0') {
            if (file[i]==file[i+1])
		    {
			    for (int j=i+1; j<fileSize ;j++)
			    {
			    file[j]=file[j+1];
			    }
			    i = i - 1;
		    }
		i++;
        }
    }

    fputs(file, output);

    free(file);
}
