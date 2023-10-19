#include <stdio.h>

int main(void){

	int prev, cur, next, count = 0;
	double sum = 0;
	FILE*f = fopen("input.txt","r");

	if(f == NULL){
		printf("Empty file\n");
		return -1;
	}

	fscanf(f, "%d", &prev);
	fscanf(f, "%d", &cur);

	while(fscanf(f, "%d", &next)!=EOF){

		if(cur > prev && cur > next){
			sum = sum + cur;
			count ++;
		}

		if(cur < prev && cur < next){
                        sum = sum + cur;
                        count ++;
                }

		prev = cur;
		cur = next;
	}

	if(count == 0){
		printf("No extremums\n");
		return 0;
	}else{
		sum = sum/count;
		printf("%lf\n", sum);
		return 0;
	}
}
