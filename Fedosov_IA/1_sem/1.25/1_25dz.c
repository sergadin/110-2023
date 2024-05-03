#include <stdio.h>


int find_distance(FILE * fin);
//функция ищет максимальное расстояние между 2-мя соседними локальными минимумами


int main(){
	FILE *fin, *fout;
	int result;
	
	fin = fopen("input.txt", "r");
	if (fin == NULL) { 
		printf("Не удалось открыть файл 'input.txt'\n");
		return -1;
	}
	
	fout = fopen("output.txt", "w");
	if (fout == NULL) { 
		printf("Не удалось открыть файл 'output.txt'\n");
		return -1;
	}
	
	result = find_distance(fin);
	
	if (result != -1){
		fprintf(fout, "%d\n", result);
	}
	
	fclose(fin);
	fclose(fout);
	
	return 0;
}


int find_distance(FILE * fin){
	int distance = 0;	//искомое расстояние
	int nomer = 2;		//номер читаемого числа, начинается с 2 тк первые 2 элемента мы читаем вне цикла	
	int min1, min2;		//номер первого и второго минимума
	int amount_min = 0;	//общее кол-во минимумов
	double prev_num, r_num, next_num;
	
	if (fscanf(fin, "%lf", &prev_num) != 1) { 
        	printf("Не удалось прочитать первый элемент\n");
        	return -1;
    	}
     
    	if (fscanf(fin, "%lf", &r_num) != 1) {  
        	printf("В последовательности нет ни одного локального минимума так как она состоит из одного числа\n");
        	return -1;
   	}
   	
   	while (fscanf(fin, "%lf", &next_num) == 1) {
        	if ((r_num < prev_num) && (r_num < next_num)) {
			min1 = min2;
		    	min2 = nomer;
		    	amount_min ++;
		    	if ((min2 - min1 > distance) && (amount_min > 1)) {
			    	distance = min2 - min1 - 1;
		    		}
			}
		prev_num = r_num;
		r_num = next_num;
		nomer ++;
    		}
    	
    	if (feof (fin) == 0){
                printf("Файл не прочитался до конца\n");
                return -1;
        }
    	
	if (amount_min < 2) {   //проверка количества минимумов
		printf("В последовательности не более одного локального минимума\n");
		return -1;
	}
	
	return distance;
}
	 

