#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer_N0 111
#define Result_Answer_YES 222

int EqualityCheck(FILE* inp_f, double eps);


//������� ���������, ��� ��� �������� � ����� ����� � ����� � ������ �����������
int EqualityCheck(FILE* inp_f, double eps) {

	double x;                              // -������� ������������������
	double maxx;                           // -���������� ����� � ������������������
	double minx;                           // -���������� ����� � ������������������


	if (fscanf(inp_f, "%lf", &x) != 1) {
		return Error_Invalid_Data;
	}

	maxx = x;
	minx = x;

	//���� �� ����� ���� �� ����� ��������� ����
	while (fscanf(inp_f, "%lf", &x) == 1) {

		//���� ���������� ������� � �����
		if (x > maxx) {
			maxx = x;
		}

		//���� ���������� ������� � �����
		if (x < minx) {
			minx = x;
		}

	}

	//���������, ��� � ���� ���������� (��� ������ ������� ���������)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//���������, ��� ��� ���� ������� �������� ����� � ������� �����������
	if ((maxx - minx) > eps) {

		//��������� ������������� �����
		return Result_Answer_N0;
	}

	//��������� ������������� �����
	return Result_Answer_YES;
}


int main(void) {

	FILE* inp_f; // -���� ����� �������� ��� ���������
	FILE* out_f; // -���� ��� ������ ������
	double eps;  // -�����������, � ������� �� ��������� �������� 
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

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	//��������� ������ ������� � ��������� ��������� � ��������������� ���������
	result = EqualityCheck(inp_f, eps);

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

	if (result == Result_Answer_N0) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return Result_Answer_N0;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");

	//������� ���� ��� ������
	fclose(out_f);

	return Result_Answer_YES;
}



