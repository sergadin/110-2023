#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
	OK,               // ��� ������
	TOO_LONG_WORD,     // �������� ������� ������� �����
	MEM_ERR
}Error;


void copyWords(FILE* input, FILE* output, Error* err);


/*
** ������� ����������� ���� �� input.txt � output.txt, ������ ������ �����
** ������������ � ����� �������.
**
** �� ���� ������� �������� ��������� �� ���� � �������� ���������� � �� ����,
** ���� ������������ �����.
**
** ������� ��������� �� ���� �������� �� ����� � �������: �������� �� ��� ������
** ���������� ��� ������ ��� ������. ���� ���������� �� ���� ���������� ��� ������,
** �� ������� ���������� � ����� ������ ����� �� ����� �������, ���� ��� �� �����������
** �� �����
**
** 
**
** 
*/