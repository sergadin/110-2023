#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#include <stdlib.h> 
#define Error_File_NOT_Exist -444
#define Error_Invalid_Data -333
#define Result_Answer 222


int Counter(FILE* inp_f);

//������� ���� ���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������
int Counter(FILE* inp_f) {

	int x;                                 // -������� ������� ������������������ 
	int px;                                // -���������� ������� ������������������
	int gl_k;                              // -���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������
	int lc_k;                              // -������� ���������� ��������� � ���������� ������� ����� ������������������
	int gl_sm;                             // -���������� ����� ��������� � ���������� ������� ����� ������������������
	int lc_sm;                             // -������� ����� ��������� � ���������� ������� ����� ������������������
	int lc_xch;
    int gl_xch;
	
	if (fscanf(inp_f, "%d", &x) != 1) {
		return Error_Invalid_Data;
	}
    
    px = x;
    
	lc_k = 1;
	lc_sm = px;
    if (px == 0){
        lc_xch = 0;
    }
    else {
        lc_xch = abs(px)/px
    }
    
    gl_k = lc_k;
	gl_sm = lc_sm;
    gl_xch = lc_xch;
    
    //���� �� ����� ���� �� ����� ��������� ����
	while (fscanf(inp_f, "%d", &x) == 1) {

		//���������, ��� ���������� ������� ����� ���������
		if (x == px) {
			lc_k += 1;
			lc_sm += x;
            
            if ((lc_xch == gl_xch) && (gl_xch == -1)) {
                //���������, ��� ��������� ����� ������ ���������� �� ������, ���� ����� �������������
                if (lc_sm < gl_sm) {
                    gl_k = lc_k;
                    gl_sm = lc_sm;
                    gl_xch = lc_xch;
                }
            }
            
            //���������, ��� ��������� ����� ������ ����������
            if (lc_sm > gl_sm) {
                    gl_k = lc_k;
                    gl_sm = lc_sm;
                    gl_xch = lc_xch;
                }
            
			//���������, ��� ��� ������ ����� ��������� ������� ������ ����������
			if ((lc_sm == gl_sm) && (lc_k > gl_k)) {
				gl_k = lc_k;
			}
		}

		else {

			lc_k = 1;
			lc_sm = x;
            if (x == 0){
                lc_xch = 0;
            }
            else {
                lc_xch = abs(x)/x;
            }
    
		}

		px = x;
	}

	//���������, ��� � ���� ���������� (��� ������ ������� ���������)
	if (!feof(inp_f)) {
		return Error_Invalid_Data;
	}

	//��������� ��������� ������� (���������� ���������� ��������� � ���������� ������� ����� ������������������ � ���������� ������ ��������� ����� �������)
	return gl_k;
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
	result = Counter(inp_f);

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
	fprintf(out_f, "Result: The largest number of elements in a constant section of the whole sequence with the largest sum of elements of this section = %d", result);

	//������� ���� ��� ������
	fclose(out_f);

	return Result_Answer;
}
