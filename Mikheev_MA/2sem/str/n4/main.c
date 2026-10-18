#include "PosOfWord.h"


typedef struct{
    const char* input;  // имя входного файла
    int value;  // ожидаемое количество слов
    const char* word; // слово, которое ищем
    Er error;  // код ошибки
}Testcase;


int main(void){
    int length; // количество тестов
    Er error = OK;
    int res = 0; // результат работы функции
    
    
    Testcase test[] = {
        {"input1.txt", 8, "the", OK},
        {"input2.txt", 2, "a", OK},
        {"input2.txt", 3, "of", OK}
    };
    
    length = sizeof(test)/sizeof(test[0]);
    
    for(int i = 0; i < length; i++){
        FILE* input;
        
        
        if((input = fopen(test[i].input, "r")) == NULL){
            printf("Тест №%d не пройден", i + 1);
            return -1;
        }
        
        res = PosOfWord(input, &error, test[i].word);
        
        if(error == OK && res == test[i].value){
            printf("Тест №%d пройден успешно\n\n", i + 1);
        }
        else{
            printf("Тест №%d не пройден\n\n", i + 1);
        }
        
        fclose(input);
    }
    
    
    return 0;
}