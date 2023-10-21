#include <stdio.h>


int min_distance_between_local_mins(const char* name);


int main(int argc char** argv)
{
if (argc != 2){
 printf("need only one argument - input filename\n");
 return -1;
}
char* name;
int result = 0;
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
printf("Minimum distance between two local minimums is %d", result);
return 0;
}


int min_distance_between_local_mins(char* name)
{
FILE* fp;
fp = fopen(name, "r");
if (!fp){
 return -1;
}
int min_distance = 99999999;
int previous;
int present = 0;
int current_distance = 1;
int flag = 0;
previous = fscanf(fp, "%d", &previous);
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
fclosef(fp);
return min_distance;
}
