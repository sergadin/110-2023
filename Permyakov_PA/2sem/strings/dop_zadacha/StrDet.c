#include "StrDet.h"
#include <string.h>

static int fact(int n)
{
	if (n == 1){
		return 1; 
	}
	else{
		return n * fact(n - 1);
	}
}

static void swap(char**** mat, int n, int i, int j)
{
        double elem;
        for (int k = 0; k < n; k++){
                elem = (*mat)[i][k];
                (*mat)[i][k] = (*mat)[j][k];
                (*mat)[j][k] = elem;
        }
}

char* calculate(double*** mat, int n, int p, int iter_c, size_t max_len)
{
	int factn;
        char* res = NULL;
	char* expand = NULL;
	char* elem = NULL;
	int m = 0;
        int c = 1;
	int flag = 0;
        if (n == 2) {
                return ((*mat)[0][0] * (*mat)[1][1]) - ((*mat)[0][1] * ((*mat)[1][0]);
        }
        for (int i = 0; i < n; i++){
		int k = 0;
                c *= -1;
                for (int j = i; j < (n - 1); j++){
                        swap(mat, n + iter_c, j, j + 1);
                }
		elem = (*mat)[i][n - 1];
                res = calculate(mat, n - 1, p * (-1), iter_c + 1);
		expand = (char*)malloc((strlen(elem) * fact(n - 1) + strlen(res)) * sizeof(char));
		for (int k = 0; k < strlen(res); k++){
			if (c * p == -1){
				if (res[k] == "+"){
					expand[m] = "-";
					m++;
					continue;
				}
				else if (res[k] == "-"){
					expand[m] = "+";
					m++;
					continue;
				}
			}
			if (res[k] != " " && res[k] != "+" && res[k] != "-"){
				if (flag){
					for (int q = 0; q < strlen(elem); q++){
						expand[m] = elem[q];
				 		m++;
					}
				}
				expand[m] = res[k];
			}
			if (res == "+" || res == "-"){
				flag = fabs(1 - flag);
				expand[m] = res[k];
				m++;
			}
			if (res == " "){
				expand[m] = " ";
				m++;
			}
		}
                for (int j = n - 1; j > i; j--){
                        swap(mat, n + iter_c, j, j - 1);
                }
        }
        return expand;
}

