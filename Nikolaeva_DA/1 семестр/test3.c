#include <stdio.h>

double sol(const char* name);

double sol(const char* name){
	int current;
	int prev;
	int next;
	double sum = 0 ;
	int count = 0;
	 
	FILE* data;
          data=fopen(name, "r");
	  if(!data) return -1;
    fscanf(data,"%d%d", &prev, &current);
    while(fscanf(data,"%d", &next) == 1){
	    if (current>prev && current>next)
	    {
		    sum=sum+current;
		    count++;
	    }
	    if (current<prev && current<next)
	    {
		    sum=sum+current;
		    count++;
	    }
	    prev=current;
	    current=next;
    }   
    if (!feof(data)) {
    	fclose(data);
    	return -2;
    }
            if(count==0){
		    printf("No extremums");
	    }
             else{
		     sum=sum/count;
		     printf("%lf", sum);
	     }
         fclose(data);
	 return sum;
 }
int main(void) {
  FILE *answer = fopen("output.txt", "w");
  if (!answer) {
      printf("What?");
      return -1;
  }
  if (fprintf(answer, "%lf", sol("input1.txt")) == 0) {
      printf("NO SUCCESS!!");
      return -2;
  }
}

