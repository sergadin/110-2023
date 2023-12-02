#include <stdio.h>

int sol(const char* name);



int sol(const char* name)
{
  int current = 0;
  int index = 0;
  int max_val;
  int cnt = 0;
  FILE* data;
  
  data = fopen(name, "r");
  if (!data)
    return -1;
  while (fscanf(data,"%d",&current) == 1){
       if (max_val<current)
       { max_val = current;
	       index=cnt;
       }
       cnt++;
  }
  if (!feof(data))
  {
       fclose(data);
       return -2;
  }
  fclose(data);
  return index;
}
int main(void) {
  FILE *answer = fopen("output.txt", "w");
  if (!answer) {
      printf("What?");
      return -1;
  }
  if (fprintf(answer, "%d", sol("input1.txt")) == 0) {
      printf("NO SUCCESS!!");
      return -2;
  }
  fclose(answer);
  return 0;
}

