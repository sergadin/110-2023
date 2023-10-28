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

int Counter(const FILE* inp_f, const int mxlen);

//������� ���� ���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������
int Counter(const FILE* inp_f, const int mxlen) {

	int x;                                 // -������� ������� ������������������ 
	int px;                                // -���������� ������� ������������������
	int gl_k;                              // -���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������
	int lc_k;                              // -������� ���������� ��������� � ���������� ������� ����� ������������������
	int gl_sm;                             // -���������� ����� ��������� � ���������� ������� ����� ������������������
	int lc_sm;                             // -������� ����� ��������� � ���������� ������� ����� ������������������
	double checklen = 1 * pow(10, mxlen);  // -��������� ��� �������� �������� ��������
	char buf[LEN];                         // -������������� ���� ������ ��� ���������� ������ �� �����


	//������ ����������� ��������� �������� �������� ��������
	px = -1316134912;
    gl_k = -2;
    lc_k = -1;
    lc_sm = px;
    gl_sm = 0;

    //���� �� ����� ���� �� ����� ��������� ����
	while (fgets(buf, LEN, inp_f)) {

		//���������, ��� �� ����� ������� �������
		if (sscanf(buf, "%d", &x) != 1) {
			return Error_Invalid_Data;
		}

		//���������, ��� ���� ����� �� ������� ������
		if (abs(x) > checklen) {
			return Error_Large_Values;
		}
		
		//���������, ��� ���������� ������� ����� ���������
		if (x == px){
            lc_k += 1;
            lc_sm += x;
            
            //���������, ��� ��������� ����� ������� ����������
            if (lc_sm > gl_sm) {
                gl_k = lc_k;
                gl_sm = lc_sm;
            }  
            
            //���������, ��� ��� ������ ����� ��������� ������� ������ ����������
            if ((lc_sm ==  gl_sm) && (lc_k > gl_k)) {
                gl_k = lc_k;
            } 
        }
        
        else {
            
            lc_k = 1;
            lc_sm = x;
            
        }
        
        px = x;
            
	}

	//���������, ��� � ���� ���������� (��� ������ ������� ���������)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//���������, ��� � ���� �� ����
	if (px == -1316134912) {
		return Error_File_Empty;
	}
    
    
    //��������� ��������� ������� (���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������)
    return gl_k;
}

int main(void){
    
	FILE* inp_f; // -���� ����� �������� ��� ���������
	FILE* out_f; // -���� ��� ������ ������
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

	printf("Enter the estimated maximum discharge\n");
	scanf("%d", &mxlen);

    //��������� ������ ������� � ��������� ��������� � ��������������� ���������
	result = Counter(inp_f, mxlen); 
    
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

	fprintf(out_f, "Result: The largest number of elements in a constant section of the whole sequence with the largest sum of elements of this section = %d", result);
    
    //������� ���� ��� ������
	fclose(inp_f);
    //������� ���� ��� ������
	fclose(out_f); 

	return Result_Answer_YES;
}
