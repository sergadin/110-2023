#include <stdio.h>


int different_num_counter(const char* name);

int main(int argc, char** argv)
{
    char* name;
    int ans;
    if (argc != 2){
        printf("incorrect number of arguments. need only one - input filename\n");
	    return -1;
    }
    name = argv[1];
    ans = different_num_counter(name);
    if (ans == -2){
        printf("can't open input file\n");
        return 2;
    }
    if (ans == -1){
    	printf("incorrect input data\n");
	    return 1;
    }
    if (ans == -3){
    	printf("incorrect input data - nondigit stuff\n");
	    return 3;
    }
    printf("The answer is %d\n", ans);
    return 0;
}
int different_num_counter(const char* name)
{
    FILE* fp;
    int previous;
    int present;
    int counter = 0;
    int flag = 0;
    fp = fopen(name, "r");
    if (!fp){
        return -2;
    }
    fscanf(fp, "%d", &previous);
    while (fscanf(fp, "%d", &present) == 1){
    	if (previous > present){
	    fclose(fp);
	    return -1;
        }
        if (previous != present){
            counter++;
            flag = 1;
        }
        if ((previous == present) & (flag == 1)){
            counter++;
            flag = 0;
        }
        previous = present;
    }
    if (!feof(fp)){
        fclose(fp);
        return -3;
    }
    fclose(fp);
    return counter;
}
