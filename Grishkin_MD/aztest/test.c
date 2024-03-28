#include <stdio.h>
#include <stdlib.h>

int luckyElements(int arrA[], int arrB[], int lengthA, int lengthB);

int main(void){
	FILE* inA;
        FILE inB;
	FILE* output;
	int lengthA;
	int lengthB;
	int* arrA;
	int* arrB;
        
	inA = fopen("inA.txt", "r");
        inB = fopen("inB.txt", "r");
	if((inA == NULL)|| (inB == NULL){
		return -1;
	}
	fscanf(inA, "%d", &lengthA);
        fscanf(inB, "%d", &lengthB);

	arrA = (int*)malloc(lengthA * sizeof(int));
	arrB = (int*)malloc(lengthB * sizeof(int));

	if((arrA == NULL)|| (arrB == NULL){
		fclose (inB);
		fclose (inA);
                return -1;
        }
	for(int i  = 0; i < lengthA; i++){
                if(fscanf(inA, "%d", &arrA[i]) != 1){
		       return -1;
	        }
        }
	for(int j  = 0; j < lengthA; j++){
                if(fscanf(inB, "%d", &arrB[j]) != 1){
                       return -1;
                }
        }
	fclose(arrA);
	fclose(arrB);

	luckyElements(int arrA[], int arrB[], int lengthA, int lengthB);
	output = fopen("output.txt", "w");
	if( output == NULL){
		fclose (output);
		return -1;
        }
	fprintf(output, "%d\n", count);

	for (int i = 0; i < count; i++){
		fprintf(output, "%d", arr[i];
	}
	fclose (output);
	free arrA;
	free arrB;
	
	return 0;

}

int luckyElements(int arrA[], int arrB[], int lengthA, int lengthB);
        int count = 0;
	int sumB = 0;

	for (int i = 0; i < lengthB; i++){
		sumB +=arrB[j];
	}

        for( int i = 0; i < lengthA; i++){
		for(int j = 0; j <= i; j++){
                        SumB += arrB[j];
		}
		if (arrA[i] > sumB){
		      arrA[count] = arrA[i];
		      count++;
		}
	}
        return count;
}	
		




	

	

