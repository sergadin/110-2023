#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#define LEN 4098
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Error_Large_Values -222
#define Error_File_Empty -111
#define Result_Answer_N0 111
#define Result_Answer_YES 222

int LastMinimum(FILE* inp_f, int mxlen);

//������� ���� ����� ���������� ����������� �������� ���� ����� ������������������
int LastMinimum(FILE* inp_f, int mxlen) {

	int x;                                 // -������� ������������������
	int i;                                 // -��������������� �������� ��� ��������� ��������� � ������������������
	double minx;                           // -���������� ����� � ������������������
	double checklen = 1 * pow(10, mxlen);  // -��������� ��� �������� �������� ��������
	int mini;                              // -��������� ������� - ����� ���������� ����������� �������� ������������������  
	char buf[LEN];                         // -��������������� ���� ������ ��� ���������� ������ �� �����


	//������ ����������� ������� ��������, ����� �������� � ��� ��������
	minx = 1 * pow(10, 2 * mxlen + 1);
	mini = 0;
	i = 1;
    
    //���� �� ����� ���� �� ����� ��������� ����
	while (fgets(buf, LEN, inp_f)) {

		//���������, ��� �� ����� ������� �������
		if (sscanf(buf, "%d", &x) != 1) {
			return Error_Invalid_Data;
		}

		//���������, ��� ���� �������� �� ������� ������
		if (abs(x) > checklen) {
			return Error_Large_Values;
		}
        
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

	//���������, ��� � ���� �� ����
	if (minx > 1 * pow(10, 2 * mxlen)) {
		return Error_File_Empty;
	}
    
    //��������� ����� �� ������ (����� ���������� ����������� �������� ������������������)
	return mini;

}

int main(void){
    
	FILE* inp_f; // -���� ����� �������� ��� ���������
	FILE* out_f; // -���� ��� ������ ������
	int mxlen;   // -������������ ������ ��������
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

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);
    
    //������� ���� ��� ������
	out_f = fopen(fo, "w"); 

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //��������� ������ ������� � ��������� ��������� � ��������������� ���������
	result = LastMinimum(inp_f, mxlen); 
    
	if (result == Error_Invalid_Data) {
		printf("Error: Invalid data entry. Check the file '%s'\n", fi);
		return Error_Invalid_Data;
	}

	if (result == Error_Large_Values) {
		printf("Error: The file file '%s' contains too large values\n", fi);
		return Error_Large_Values;
	}

	if (result == Error_File_Empty) {
		printf("The file '%s' is empty\n", fi);
		return Error_File_Empty;
	}

	printf("The result is uploaded to the file '%s'\n", fo);

	fprintf(out_f, "Result: The number of the last smallest element in the sequence = %d", result);
    
    //������� ���� ��� ������
	fclose(inp_f);
    //������� ���� ��� ������
	fclose(out_f); 

	return Result_Answer_YES;
}
