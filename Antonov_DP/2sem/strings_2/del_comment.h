#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{ 
	OK = 0,
       	ER_NL 	// ER_NL - строка пустая;
} ERR;

// функция создаёт файл output.txt в котором выводится строка char *str без подстрок ограниченных заданным типом скобок включительно
// на вход нужны строка char * и открывающая 'скобка' char *start и закрывающая 'скобка' char *end
// на выходе даёт 0 если выполнилась успешно и -1, если неуспешно

int del_comment(char *str, char *start, char *end, ERR *err);
