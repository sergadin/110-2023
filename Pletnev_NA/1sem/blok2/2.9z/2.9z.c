#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Error_File_NOT_Exist -666
#define Error_Invalid_Data -555
#define Error_Unallocated_Memory -444
#define Error_Array_Empty -333
#define Result_Answer 222

int LenSet(int* arr, int len);
void ShiftTheArrayByPositionK(int* arr, int len, int k);
int Check(int* arr, int len, int i0);



//������� ���������, ���� � ������� ����� ��� ���������� �����
int Check(int* arr, int len, int i0)
{
	for (int i = i0; i < len; i++)
	{
		if (arr[i + 1] == arr[i])
		{
			return 1;
		}
	}

	return 0;
}


//������� �������� �������� ������� �� k ������� �����
void ShiftTheArrayByPositionK(int* arr, int len, int k)
{

	int i;			// ���������� ������ ��������
	int j;			// ������� ������ ��������
	int cnt = 0;	// ������� ��������
	int c;			// �������� ������� �������� � �����

	k %= len;

	if (k == 0)
	{
		return;
	}

	//����� ���������� �����
	for (int i0 = 0; cnt < len; i0++)
	{
		i = i0;
		c = arr[i];
		for (j = ((i + k) % len); j != i0; j = ((j + k) % len))
		{
			arr[i] = arr[j];
			cnt++;
			i = j;
		}
		arr[i] = c;
		cnt++;
	}

}


//������� ��������� ����� �������� ������� ��� ����������� ��������� ������ ������
int LenSet(int* arr, int len)
{

	if (arr == NULL)
	{
		printf("Error:The array is empty\n");
		return Error_Array_Empty;
	}

	int itoglen = len;
	int kpovtor;
	int check = 1;
	int i;

	for (int i0 = 0; ((Check(arr, itoglen, i0) != 0) && (i0 < itoglen - 1)); i0++)
	{

		i = i0;
		while (arr[i + 1] == arr[i])
		{
			i++;
		}

		kpovtor = i - i0;
		itoglen -= kpovtor;

		ShiftTheArrayByPositionK(arr, i0 + kpovtor + 1, i0 + 1);
		ShiftTheArrayByPositionK(arr, len, kpovtor);

	}

	return itoglen;
}


int main(void)
{

	FILE* inp_f;		// ���� ����� �������� ��� ���������
	FILE* out_f;		// ���� ��� ������ ������
	char fi[30];		// ��������������� ��������� ��� ����� ����� ����� ����� ��������
	char fo[30];		// ��������������� ��������� ��� ��� ����� ����� ����� �����
	int code;		// �������� �������
	int* arr = NULL;	// ��� ������ ��� ������
	int len;			// ����� ������ �������

	printf("Enter the name of the input file:\n");
	scanf("%s", fi);

	//������� ���� ��� ������
	inp_f = fopen(fi, "r");

	//��������� ������������� �����. ���� ��� ���, ������� ������
	if (inp_f == NULL)
	{
		printf("Error: The file '%s' does not exist\n", fi);
		return Error_File_NOT_Exist;
	}

	if (fscanf(inp_f, "%d", &len) != 1)
	{
		printf("Error: Invalid data entry. Check the file '%s'\n", fi);
		return Error_Invalid_Data;
	}

	arr = (int*)malloc((len + 1) * sizeof(int));

	if (arr == NULL)
	{
		printf("Error: RAM is not allocated\n");
		return Error_Unallocated_Memory;
	}

	for (int i = 0; i < len; i++)
	{

		if (fscanf(inp_f, "%d", &arr[i]) != 1)
		{
			printf("Error: Invalid data entry. Check the file '%s'\n", fi);
			return Error_Invalid_Data;
		}

	}

	//������� ���� ��� ������
	fclose(inp_f);

	code = LenSet(arr, len);

	if (code < 0)
	{
		return code;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	//������� ���� ��� ������
	out_f = fopen(fo, "w");

	printf("The result is uploaded to the file '%s'\n", fo);

	fprintf(out_f, "Number of elements in the array without repetitions %d\nThe array itself without repetitions: ", code);

	for (int i = 0; i < code; i++)
	{
		fprintf(out_f, "%d ", arr[i]);
	}

	//������� ���� ��� ������
	fclose(out_f);
	free(arr);

	return Result_Answer;
}

