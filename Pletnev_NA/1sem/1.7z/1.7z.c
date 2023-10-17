#include <stdio.h>
#include <math.h> 
#define LEN 100000000
int EqualityCheck(FILE *inp_f,  FILE *out_f, double eps, int mxlen);


int EqualityCheck(FILE *inp_f,  FILE *out_f, double eps, int mxlen){ //������� ���������, ��� ��� ����� � ����� ����� � ����� � ������ �����������
    
    double x, maxx, minx;
    char buf[LEN];
    
    maxx = -1*pow(10, 2*mxlen+1);  //������ ����������� ����� ��������, ����� �������� � ���
    minx = -1*pow(10, 2*mxlen+1);  //������ ����������� ������� ��������, ����� �������� � ���

    while (fgets(buf, LEN, inp_f)) { //���� �� ����� ���� �� ����� ��������� ����

        if (sscanf(buf, "%lf", &x) != 1) { //���������, ��� �� ����� ������� �������
            
            printf("Error: Invalid data entry. Check the input file\n");
            return -2;
        }
        
        if (fabs(x) > 1*pow(10, mxlen)) {  //���������, ��� ���� ����� �� ������� ������
            
            printf("Error: The file input file contains too large values\n");
            return -1;
        }
        
        if (x > maxx) { //���� ���������� �������� � �����
            maxx = x;
        }
        
        if (x < minx) { //���� ���������� �������� � �����
            minx = x;
        }

    }

    if  ( (maxx < -1*pow(10, 2*mxlen) ) || (minx > 1*pow(10, 2*mxlen) ) ) {  //���������, ��� � ���� �� ����
        
            printf("The input file is empty\n");
            return 0;
        }
    
    if ((maxx - minx) > eps) { //���������, ��� ��� ���� ������� ����� ����� � ������� �����������
        
            printf("The result is uploaded to the output file\n");
            fprintf(out_f, "Result: No, not all numbers are equal");
            return 1;
        }
        
        
    printf("The result is uploaded to the output file\n");    
    fprintf(out_f, "Result: Yes, all numbers are equal\n");
    return 2;

}


int main(void) {

    FILE *inp_f, *out_f;
    double eps;
    int mxlen;
    char fi[30], fo[30];
    
    printf("Enter the name of the input file:\n");
	scanf("%s" , fi);
    
	printf("Enter the name of the output file:\n");
	scanf("%s" , fo);
    

    inp_f = fopen(fi, "r");  //������� ���� ��� ������
    out_f = fopen(fo , "w"); //������� ���� ��� ������
    
    
    if (inp_f == NULL) {                             //��������� ������������� �����. ���� ��� ���, ������� ������
        printf("Error: The file '%s' does not exist\n", fi);
        return -3;
    }
    
    
    printf("Enter the error value:\n");
	scanf("%lf" , &eps);
    
	printf("Enter the maximum power of 10 to check the numbers\n");
	scanf("%d" , &mxlen);
  
    
    EqualityCheck(inp_f, out_f, eps, mxlen); //��������� ������ �������
    
    fclose(inp_f); //������� ���� ��� ������
	fclose(out_f); //������� ���� ��� ������
    
	return 100;
        
}



