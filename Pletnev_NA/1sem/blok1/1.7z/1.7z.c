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

int EqualityCheck(const FILE* inp_f, const double eps, const int mxlen);


//������� ���������, ��� ��� �������� � ����� ����� � ����� � ������ �����������
int EqualityCheck(const FILE* inp_f, const double eps, const int mxlen) {
    
	double x;                              // -������� ������������������
    double maxx;                           // -���������� ����� � ������������������
    double minx;                           // -���������� ����� � ������������������
    double checklen = 1 * pow(10, mxlen);  // -��������� ��� �������� �������� ��������
	char buf[LEN];                         // -��������������� ���� ������ ��� ���������� ������ �� �����
    
    //������ ����������� ����� ��������, ����� �������� � ���
	maxx = -1 * pow(10, 2 * mxlen + 1);
    
    //������ ����������� ������� ��������, ����� �������� � ���
	minx = 1 * pow(10, 2 * mxlen + 1);  
    
    //���� �� ����� ���� �� ����� ��������� ����
	while (fgets(buf, LEN, inp_f)) { 
        
        //���������, ��� �� ����� ������� �������
		if (sscanf(buf, "%lf", &x) != 1) { 
			return Error_Invalid_Data;
		}
		
        //���������, ��� ���� �������� �� ������� ������
		if (fabs(x) > checklen)) { 
			return Error_Large_Values;
		}
        
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
	
    //���������, ��� � ���� �� ����
	if ((maxx < -1 * pow(10, 2 * mxlen)) || (minx > 1 * pow(10, 2 * mxlen))) {  
		return Error_File_Empty;
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
	int mxlen;   // -������������ ������ �����
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

	printf("Enter the error value:\n");
	scanf("%lf", &eps);

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //��������� ������ ������� � ��������� ��������� � ��������������� ���������
	result = EqualityCheck(inp_f, eps, mxlen); 
    
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

	if (result == Result_Answer_N0) {
		fprintf(out_f, "Result: No, not all numbers are equal");
		return Result_Answer_N0;
	}

	fprintf(out_f, "Result: Yes, all numbers are equal\n");
    
    //������� ���� ��� ������
	fclose(inp_f);
    //������� ���� ��� ������
	fclose(out_f); 

	return Result_Answer_YES;
}



