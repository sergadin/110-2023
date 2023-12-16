#include <stdio.h>
#include <stdlib.h>

int check_mas(int* mas1, int* mas2, int lngth_1, int lngth_2);
int check_mas(int* mas1, int* mas2, int lngth_1, int lngth_2)
{
	int sum = 0;
	int count = 0;


	for (int i = 0; i < lngth_1; i++)
	{
		if (i < lngth_2)
        	{
			sum += mas2[i];
			if (mas1[i] > sum)
			{
				mas1[count] = mas1[i];
				count++;
			}
			else
			{
				mas1[i] = 0;
			}
		}
	}
	return count;
}

int main(void)
{
	FILE* inA = fopen("inA.txt", "r");
	FILE* inB = fopen("inB.txt", "r");
	FILE* output = fopen("output.txt", "w");
	int lngth_1, count;
	int lngth_2;
	int* mas1 = NULL;
	int* mas2 = NULL;

	if (inA == NULL)
	{
		printf("Unable to oen the file inA.txt\n");
		return -1;
	}

	if (inB == NULL)
	{
		printf("Unable to open the file inB.txt\n");
		return -1;
	}
	
	if (fscanf(inA, "%d", &lngth_1) != 1)
	{
		printf("Unable to read the file inA.txt\n");
		fclose(inA);
		fclose(inB);
		return -1;
	}

	 if (fscanf(inB, "%d", &lngth_2) != 1)
        {
                printf("Unable to read the file inA.txt\n");
                fclose(inA);
                fclose(inB);
                return -1;
        }
	
	mas1 = (int*)malloc((lngth_1) * sizeof(int));
	mas2 = (int*)malloc((lngth_2) * sizeof(int));

	if (mas1 == NULL)
	{
		printf("Memory error\n");
		fclose(inA);
		fclose(inB);
                return -1;
	}

	 if (mas2 == NULL)
        {
                printf("Memory error\n");
                fclose(inA);
                fclose(inB);
                return -1;
        }
	
	for (int i = 0; i < lngth_1; i++)
	{
		if (fscanf(inA, "%d", &mas1[i]) != 1)
		{
			printf("Problems with array\n");
			free(mas1);
			fclose(inA);
               		fclose(inB);
                	return -1;

		}
	}

	 for (int i = 0; i < lngth_2; i++)
        {
                if (fscanf(inB, "%d", &mas2[i]) != 1)
                {
                        printf("Problems with array\n");
                        free(mas2);
                        fclose(inA);
                        fclose(inB);
                        return -1;

                }
        }
	
	count = check_mas(mas1, mas2, lngth_1, lngth_2);
	fprintf(output, "%d", count);

	fclose(inA);
	fclose(inB);
	fclose(output);
	free(mas1);
	free(mas2);

	return 0;



	
}
