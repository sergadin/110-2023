#include "FormatingPar.h"

typedef struct{
    const char* input;  // имя входного файла
    const char* output; // имя выходного дня
    int wide;  // ширина строки
    Er error;  // код ошибки
}Testcase;


int main(void){
    int length;
    Er error = OK;
    
    Testcase test[] = {
        {"input1.txt", "output1.txt", 70, OK},
        {"input1.txt", "output2.txt", 30, OK},
        {"input2.txt", "output3.txt", 70, OK}
    };
    
    length = sizeof(test)/sizeof(test[0]);
    
    
    for(int i = 0; i < length; i++){
        FILE* input;
        FILE* output;
        
        
        if((input = fopen(test[i].input, "r")) == NULL){
            printf("Тест №%d не пройден", i + 1);
            return -1;
        }
        
        if((output = fopen(test[i].output, "w")) == NULL){
            printf("Тест №%d не пройден", i + 1);
            fclose(input);
            return -1;
        }
        
        
        FormatingPar(input, output, &error, test[i].wide);
        
        if(error == OK){
            printf("Тест №%d успешно пройден", i + 1);
        }
        else{
            printf("Тест №%d не пройден", i + 1);
            fclose(input);
            fclose(output);
            return -1;
        }

        fclose(input);
        fclose(output);
    }    

    
    return 0;
}