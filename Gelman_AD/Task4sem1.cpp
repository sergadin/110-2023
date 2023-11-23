#include<stdio.h>
#include<<stdlib.h>>

//(��������� ����� �������, �������� ������ ������� � �����)

void shiftrightk(double* mas, int len);
//�������� �� ���� ������ (mas) � ��� ����� (lngh)
//������� ���������� �������� ���������� �� ���� ������ mas, ������ ������� ������� ���������� ������


void shiftrightk(double* mas, int lngh)
{
	double posled_el;

	if (lngh == 0)
	{
		printf("No array, lngh = 0\n");
		return;
	}

	if (lngh == 1)
	{     //������ ��������, � � ������ ���� �������
		return;
	}

	posled_el = mas[lngh - 1];    //��������� ��������� ������� �������

	for (int i = lngh - 1; i > 0; i--)
	{		//�������� �������� ������� ������
		mas[i] = mas[i - 1];
	}

	mas[0] = posled_el;
}


int main(void) 
{
	int lngh; //����� �������
	int K; //����� �������� ������ �� � ������� ������
	FILE* file_in = fopen("input.txt", "r");
	FILE* file_out = fopen("output.txt", "w");
	double* mas = NULL;

	if (file_in == NULL) 
	{
		printf("Unable to open the file input.txt\n");
		return -1;
	}

	if (file_out == NULL) 
	{
		printf("Unable to open the file output.txt\n");
		fclose(file_in);
		return -1;
	}

	if (fscanf(file_in, "%d", &lngh) != 1)
	{
		printf("Unable to read the file\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	mas = (double*)malloc((lngh) * sizeof(double));

	if (mas == NULL) 
	{
		printf("Memory error\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	for (int i = 0; i < lngh; i++)
	{
		if (fscanf(file_in, "%lf", &mas[i]) != 1) 
		{
			printf("Problems with array\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}

	//��������� ����� �, ��������� � ����������

	printf("Enter the value of shifting the array\n");
	fscanf(&K);

	//�������� ������ �� � ������� ������

	for (int K = 0; K)
	{
		shiftrightk(mas, lngh);
	}

	for (int i = 0; i < lngh; i++)
	{
		fprintf(file_out, "%lf ", mas[i]);
	}

	if (lngh != 0)
	{
		printf("The result is printed\n");
	}

	free(mas);
	fclose(file_in);
	fclose(file_out);

	return 0;
}