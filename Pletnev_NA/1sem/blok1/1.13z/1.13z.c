#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer 222

int LastMinimum(FILE* inp_f);

//������� ���� ����� ���������� ����������� �������� ���� ����� ������������������
int LastMinimum(FILE* inp_f) {

	int x;            // -������� ������������������
	int i;            // -��������������� �������� ��� ��������� ��������� � ������������������
	int minx;         // -���������� ����� � ������������������
	int mini;         // -��������� ������� - ����� ���������� ����������� �������� ������������������  


	if (fscanf(inp_f, "%d", &x) != 1) {
		return Error_Invalid_Data;
	}

	minx = x;
	mini = 0;
	i = 1;

	//���� �� ����� ���� �� ����� ��������� ����
	while (fscanf(inp_f, "%d", &x) == 1) {

		//���� ��������� ���������� ������� � �����
		if (x <= minx) {
			minx = x;
			mini = i;
		}

		++i;
	}

	//���������, ��� � ���� ���������� (��� ������ ������� ���������)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//��������� ����� �� ������ (����� ���������� ����������� �������� ������������������)
	return mini;

}

int main(void) {

	FILE* inp_f; // -���� ����� �������� ��� ���������
	FILE* out_f; // -���� ��� ������ ������
	int result;  // -��������������� ��������� ��� �������� ���������� ����� �������
	char fi[30]; // -��������������� ��������� ��� ����� ����� ����� ����� ��������
	char fo[30]; // -��������������� ��������� ��� ��� ����� ����� ����� ������

	printf("Enter the name of the input file:\n");
	scanf("%s", fi);

	//������� ���� ��� ������
	inp_f = fopen(fi, "r");

	//��������� ������������� �����. ���� ��� ���, ������� ������
	if (inp_f == NULL) {
		printf("Error: The file '%s' does not exist\n", fi);
		return Error_File_NOT_Exist;
	}

	//��������� ������ ������� � ��������� ��������� � ��������������� ���������
	result = LastMinimum(inp_f);

	//������� ���� ��� ������
	fclose(inp_f);

	if (result == Error_Invalid_Data) {
		printf("Error: Invalid data entry. Check the file '%s'\n", fi);
		return Error_Invalid_Data;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	//������� ���� ��� ������
	out_f = fopen(fo, "w");

	printf("The result is uploaded to the file '%s'\n", fo);
	fprintf(out_f, "Result: The number of the last smallest element in the sequence = %d", result);

	//������� ���� ��� ������
	fclose(out_f);

	return Result_Answer;
}
