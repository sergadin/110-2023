#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_diff.h"

typedef struct {
	const char* file_A;
	const char* file_B;
	const char* file_out;
} test_case;


int main(void) {
	int n_tests;
	test_case tests[] = {
		{"A1.txt", "B1.txt", "out1.txt"},
		{"A2.txt", "B2.txt", "out2.txt"},
		{"A3.txt", "B3.txt", "out3.txt"}
	};
	n_tests = sizeof(tests) / sizeof(tests[0]);
	error err;
	for (int i = 0; i < n_tests; i ++) {
		find_diff(tests[i].file_A, tests[i].file_B, tests[i].file_out, &err);
		if (err == FILE_ERR) {
			printf("file err \n");
			return -1;
		} 
	}
	return 0;
}