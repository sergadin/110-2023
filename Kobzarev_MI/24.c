#include <stdio.h>

int main(void){

	int prev, cur, next, count = 0;
	double sum = 0;
	FILE*f = fopen("input.txt","r");

	if (f == NULL) 
    {
        printf("Error: could not open the file.\n");
        return -1;
    }

	if (fscanf(f, "%d", &prev) != 1)
    {
        printf("Cannot read the first element\n");
        return 0;
    }

    if (fscanf(f, "%d", &cur) != 1)
    {
        printf("Cannot read the second element\n");
        return 0;
    }

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