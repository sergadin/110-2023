#include <values_at_point.c>


int main(int argc, char** argv)
{
	double x;
	int length = 1000;
	if (argc != 1){
		printf("need only 1 argument - real number\n");
		return -1;
	}
	if (!scanf('%lf', argv[0], &x)){
		printf("need only 1 argument - real number\n");
		return -2;
	};
	function* functions;
	functions = (function)malloc(length * sizeof(function));
	if (functions == NULL){
		return -3;
	}
	for (int i = 0; i < length; i++){
		function f[
	}
}
