#include <math.h>

/* Множество функций из R в R*/
typedef double (*RRFun)(double);

/* Основные ошибки*/
typedef enum {
	OK,
	NO_ITER,
	NO_FUNC,
	LIMIT_NO,
	NA_NO_ROOT
} Error;


/**
 * Функция реализует метод хорд для поиска корней функции.
 * Не берем функции с несколькими корнями.
 * На вход подаются параметры:
 *              f - функция
 *              а - вещественное число, левая граница отрезка. Должна быть меньше правой.
 *              b - вещественное число, правая граница отрезка. Должна быть больше левой.
 *              eps - погрешность
 *              *err - указатель на код ошибки
 *		*max_iter - указатель на количество итераций
 * Вычисляются значения на границах отрезка. Если границы отрезка написаны не в правильном порядке, выдается ошибка NO_ITER
 * Если значения в этих точках одного знака выдается ошибка NO_FUNC.   
 * Если значения разных знаков, значения в этих точках соединяются хордой и вычисляется точка, в которой она пересекает ось Х.
 * Подсчитывается значение в найденной точке, в нее сдвигается конец хорды того же знака. Пока концы хорды остаются разных знаков 
 * или не совпадают, эти операции продолжают выполняться. Когда модуль разности текущего корня и предыдущего корня становится меньше погрешности,
 * функция завершает работу, передает код ошибки OK и точку, в которой значение близко к нулю. Если возвращаются остальные типы ошибок, 
 * функция возвращает значение -1.
 * Вывод:Если код выполнен без ошибок и не преодлел лимит количества итераций, возвращается код ошибки OK и точку со значением 0
 *                               (с учетом погрешности). Также выводится количество итераций (в остальных случаях оно не выводится).
 * Если левый конец отрезка больше правого, возвращается код ошибки NO_ITER и значение -1.
 * Если превышен лимит количества итераций (iter) или значения функции одного знака, возвращается код ошибки NA_NO_ROOT и значение -1.
 */

double chord_metod(RRFun f, double a, double b, double eps, int *max_iter, Error *err);
