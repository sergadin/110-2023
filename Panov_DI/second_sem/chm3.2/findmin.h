#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {           // Коды ошибок:
	OK,                     //  Все хорошо
	I_LIMIT,                //  Превышен лимит итераций
	INVALID_INTERVAL,       //  Неправильно задан интервал
} error;

double findmin(RRFun f, double a, double b, double eps, error* err);

/* Функция для нахождения минимума функции с использованием метода золотого сечения
**
** Функция принимает указатель на функцию, границы интервала, в котором необходимо
** найти минимальное значение, допустимую погрешность и указатель на переменную
** для кода ошибки.
** Алгоритм работает следующим образом: на каждой итерации вычисляются значения
** функции в двух точках, определённых по принципу золотого сечения. После этого
** выбирается подотрезок, на котором функция принимает меньшее значение, а другая
** часть интервала отбрасывается. Длина нового интервала всегда составляет 0.618
** от длины предыдущего, что соответствует золотому сечению.
** Этот процесс продолжается до тех пор, пока разница значений функции в двух точках
** не станет меньше допустимой погрешности.
**
** При успешном выполнении функция возвращает значение функции в точке минимума,
** соответствующее заданной погрешности.
*/