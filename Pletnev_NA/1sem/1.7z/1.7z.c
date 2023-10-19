#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#define LEN 4098

//������� ���������, ��� ��� ����� � ����� ����� � ����� � ������ �����������
int EqualityCheck(FILE* inp_f, double eps, int mxlen)
{
	double x, maxx, minx;
	char buf[LEN];

	maxx = -1 * pow(10, 2 * mxlen + 1);  //������ ����������� ����� ��������, ����� �������� � ���
	minx = 1 * pow(10, 2 * mxlen + 1);  //������ ����������� ������� ��������, ����� �������� � ���

	while (fgets(buf, LEN, inp_f)) { //���� �� ����� ���� �� ����� ��������� ����

		if (sscanf(buf, "%lf", &x) != 1) { //���������, ��� �� ����� ������� �������
			return -2;
		}

		if (fabs(x) > 1 * pow(10, mxlen)) {  //���������, ��� ���� ����� �� ������� ������
			return -1;
		}

		if (x > maxx) { //���� ���������� �������� � �����
			maxx = x;
		}

		if (x < minx) { //���� ���������� �������� � �����
			minx = x;
		}

	}

	if (!feof(inp_f)) {
		return -2;
	}

	if ((maxx < -1 * pow(10, 2 * mxlen)) || (minx > 1 * pow(10, 2 * mxlen))) {  //���������, ��� � ���� �� ����
		return 0;
	}

	if ((maxx - minx) > eps) { //���������, ��� ��� ���� ������� ����� ����� � ������� �����������
		return 1;
	}

	return 2;
}


int main(void) {

	FILE* inp_f;
	FILE* out_f;
	double eps;
	int mxlen;
	int result;
	char fi[30];
	char fo[30];

	printf("Enter the name of the input file:\n");
	scanf("%s", &fi);

	inp_f = fopen(fi, "r");  //������� ���� ��� ������

	if (inp_f == NULL) {                             //��������� ������������� �����. ���� ��� ���, ������� ������
		printf("Error: The file '%s' does not exist\n", fi);
		return -3;
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", &fo);

	out_f = fopen(fo, "w"); //������� ���� ��� ������

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	printf("Enter the maximum power of 10 to check the numbers\n");
	scanf("%d", &mxlen);


	result = EqualityCheck(inp_f, eps, mxlen); //��������� ������ �������

	if (result == -2) {
		printf("Error: Invalid data entry. Check the input file\n");
		return -2;
	}

	if (result == -1) {
		printf("Error: The file input file contains too large values\n");
		return -1;
	}

	if (result == 0) {
		printf("The input file is empty\n");
		return 0;
	}

	printf("The result is uploaded to the output file\n");

	if (result == 1) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return 1;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");

	fclose(inp_f); //������� ���� ��� ������
	fclose(out_f); //������� ���� ��� ������

	return 2;
}



