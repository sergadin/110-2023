#include <stdio.h>


int min_distance_between_local_mins(const char* name);


int main(int argc, char** argv)
{
char* name;
int result;
if (argc != 2){
 printf("need only one argument - input filename\n");
 return -1;
}
name = argv[1];
result = min_distance_between_local_mins(name);
if (result == -1){
 printf("can't open the file\n");
 return -2;
}
if (result == -2){
 printf("incorrect input file - need only number sequence\n");
 return -3;
}
printf("Minimum distance between two local minimums is %d\n", result);
return 0;
}


int min_distance_between_local_mins(const char* name)
{
FILE* fp;
int min_distance;
int previous;
int present;
int current_distance;
int flag;
flag = 1;
fp = fopen(name, "r");
current_distance = 0;
min_distance = 9999999;
previous = fscanf(fp, "%d", &previous);
if (!fp){
 return -1;
}
while (fscanf(fp, "%d", &present) == 1){
 if (present < previous){
  current_distance++;
  flag = 1;
 }
 if ((previous > present) & (flag = 1)){
  current_distance++;
  flag = 0;
  if (current_distance < min_distance){
   min_distance = current_distance;
  }
  current_distance = 0;
 }
 previous = present;
}
if (!feof(fp)){
 return -2;
}
fclose(fp);
return min_distance;
}
