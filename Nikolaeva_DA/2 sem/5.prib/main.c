/*#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prib.h"

// Функция для вычисления максимального значения
double max(double x, double y, double eps) {
    double max_ch = x;
    if (y > max_ch) {
        max_ch = y;
    }
    if (eps > max_ch) {
        max_ch = eps;
    }
    return max_ch;
}

// Функция для создания графика
void make_picture(FILE* out1, FILE* out2, point* xy_points, int qvp, point* i_points, int qv_ip, double* res) {
    for (int i = 0; i < qvp; i++) {
        fprintf(out1, "%lf %lf\n", xy_points[i].x, xy_points[i].y);
    }
    for (int k = 0; k < qv_ip; k++) {
        fprintf(out2, "%lf %lf\n", i_points[k].x, res[k]);
    }
}

double f1(double x) {
    return x * x - x - 6;
}

double f2(double x) {
    return pow(x, 3) - 2 * x - 6;
}

double f3(double x) {
    return cos(x);
}

int main() {
  const double eps = 0.1;
  int test_num;
  int func_num;
  func_num = 5;
  double* res;
  error err;
  FILE* out1;
  FILE* out2;

  typedef struct {   
    point* xy_points;      // массив определенных точек
    int qvp;         // кол-во этих точек
    point* i_points;       // точные точки функции(x используется для поиска прибл. значения, y для проверки в тесте)
    int qv_ip;       // кол-во этих точек
    error err;             // код ошибки
  } test_case;

  // Массив тестовых данных
  test_case tests[] = {
    { 
      (point[]) { {1, f1(1)}, {2, f1(2)}, {3, f1(3)}, {4, f1(4)}, {5, f1(5)} },
      5,
      (point[]) { {1.1, f1(1.1)}, {1.5, f1(1.5)}, {2.8, f1(2.8)}, {3.62, f1(3.62)} },
      4,
      OK 
    },
    {
      (point[]) {{-3.5, f2(-3.5)}, {-2.5, f2(-2.5)}, {-1.5, f2(-1.5)}, {-0.5, f2(-0.5)}, {0.5, f2(0.5)}, {1.5, f2(1.5)}, {2.5, f2(2.5)}, {3.5, f2(3.5)}, {4.5, f2(4.5)}, {5.5, f2(5.5)}},
      10,
      (point[]) {{-3.1, f2(-3.1)}, {-0.01, f2(-0.01)}, {0.9, f2(0.9)} } ,
      3,
      OK 
    },
    {	
      (point[]) {{0, f3(0)}, {0.5, f3(0.5)}, {1.0, f3(1.0)}, {2.0, f3(2.0)}, {2.5, f3(2.5)}, {3.0, f3(3.0)}, {3.5, f3(3.5)}, {4.0, f3(4.0)}, {4.5, f3(4.5)}, {5.0, f3(5.0)}},
      10,
      (point[]) {{0.25, f3(0.25)}, {1.75, f3(1.75)}, {2.2, f3(2.2)}},
      3,
      OK 
    },
    {	
      (point[]) {{0, f3(0)}, {1, f3(1)}, {2, f3(2)}, {4, f3(4)}, {3, f3(3)}, {9, f3(9)}, {7, f3(7)}, {5, f3(5)}},
      8,
      (point[]) {{0.5, f3(0.5)}, {2.5, f3(2.5)}, {4.5, f3(4.5)}},
      3,
      OK  // x y не по порядку в изнач точках
    },
    {
      (point[]) {{0, f3(0)}, {1, f3(1)}, {2, f3(2)}, {4, f3(4)}},
      4,
      (point[]) {{-9, f3(-9)}, {-9, f3(-9)}, {-9, f3(-9)}},
      3,
      ERR_INTER_POINTS // точки интерполяции совпали
    }
  };

  // Количество тестовых данных
  test_num = sizeof(tests) / sizeof(tests[0]);

  // Цикл по тестовым данным
  for (int i = 0; i < test_num; i++) {
    char file1[32], file2[32];
    sprintf(file1, "out%d.txt", 2 * (i + 1) - 1);
    sprintf(file2, "out%d.txt", 2 * (i + 1));
    out1 = fopen(file1, "w");
    if (out1 == NULL) {
      printf("test %d - file1 err\n", i + 1);
      continue;
    }
    out2 = fopen(file2, "w");
    if (out2 == NULL) {
      fclose(out1);
      printf("test %d - file2 err\n", i + 1);
      continue;
    }
    res = (double*)malloc(sizeof(double) * tests[i].qv_ip);
    if (res == NULL) {
      printf("test %d - memory err\n", i + 1);
      fclose(out1);
      fclose(out2);
      continue;
    }
    
    // Вызов функции interpolate
    interpolate(tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res, &err);
    
    // Проверка результата
    if (err != tests[i].err) {
      printf("тест %d потерпел крах\n", i + 1);
      free(res);
      fclose(out1);
      fclose(out2);
      continue;
    } else if (err == ERR_INTER_POINTS) {
      printf("тест %d пройден, но точки интерполяции совпали\n", i + 1);
      make_picture(out1, out2, tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res);
      free(res);
      fclose(out1);
      fclose(out2);
      continue;
    } else if (err == OK) {
      for (int j = 0; j < tests[i].qv_ip; j++) {
        if (fabs(res[j] - tests[i].i_points[j].y) > (max(fabs(res[j]), fabs(tests[i].i_points[j].y), 1.0) * eps)) {
          printf("тест %d не пройден \n", i + 1);
          free(res);
          fclose(out1);
          fclose(out2);
          continue;
        }
      }
      printf("тест %d пройден.\n", i + 1);
      make_picture(out1, out2, tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res);
      free(res);
      fclose(out1);
      fclose(out2);
    }
  }

  return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prib.h"

// Функция для вычисления максимального значения
double max(double x, double y, double eps) {
    double max_ch = x;
    if (y > max_ch) {
        max_ch = y;
    }
    if (eps > max_ch) {
        max_ch = eps;
    }
    return max_ch;
}

// Функция для создания графика
void make_picture(FILE* out1, FILE* out2, point* xy_points, int qvp, point* i_points, int qv_ip, double* res) {
    for (int i = 0; i < qvp; i++) {
        fprintf(out1, "%lf %lf\n", xy_points[i].x, xy_points[i].y);
    }
    for (int k = 0; k < qv_ip; k++) {
        fprintf(out2, "%lf %lf\n", i_points[k].x, res[k]);
    }
}

double f1(double x) {
    return x * x - x - 6;
}

double f2(double x) {
    return pow(x, 3) - 2 * x - 6;
}

double f3(double x) {
    return cos(x);
}

int main() {
  const double eps = 0.1;
  // int func_num; // Удаляем эту строку
  double* res;
  error err;
  FILE* out1;
  FILE* out2;

  typedef struct {   
    point* xy_points;      // массив определенных точек
    int qvp;         // кол-во этих точек
    point* i_points;       // точные точки функции(x используется для поиска прибл. значения, y для проверки в тесте)
    int qv_ip;       // кол-во этих точек
    error err;             // код ошибки
  } test_case;

  // Массив тестовых данных
  test_case tests[] = {
    { 
      (point[]) { {1, f1(1)}, {2, f1(2)}, {3, f1(3)}, {4, f1(4)}, {5, f1(5)} },
      5,
      (point[]) { {1.1, f1(1.1)}, {1.5, f1(1.5)}, {2.8, f1(2.8)}, {3.62, f1(3.62)} },
      4,
      OK 
    },
    {
      (point[]) {{-3.5, f2(-3.5)}, {-2.5, f2(-2.5)}, {-1.5, f2(-1.5)}, {-0.5, f2(-0.5)}, {0.5, f2(0.5)}, {1.5, f2(1.5)}, {2.5, f2(2.5)}, {3.5, f2(3.5)}, {4.5, f2(4.5)}, {5.5, f2(5.5)}},
      10,
      (point[]) {{-3.1, f2(-3.1)}, {-0.01, f2(-0.01)}, {0.9, f2(0.9)} } ,
      3,
      OK 
    },
    {	
      (point[]) {{0, f3(0)}, {0.5, f3(0.5)}, {1.0, f3(1.0)}, {2.0, f3(2.0)}, {2.5, f3(2.5)}, {3.0, f3(3.0)}, {3.5, f3(3.5)}, {4.0, f3(4.0)}, {4.5, f3(4.5)}, {5.0, f3(5.0)}},
      10,
      (point[]) {{0.25, f3(0.25)}, {1.75, f3(1.75)}, {2.2, f3(2.2)}},
      3,
      OK 
    },
    {	
      (point[]) {{0, f3(0)}, {1, f3(1)}, {2, f3(2)}, {4, f3(4)}, {3, f3(3)}, {9, f3(9)}, {7, f3(7)}, {5, f3(5)}},
      8,
      (point[]) {{0.5, f3(0.5)}, {2.5, f3(2.5)}, {4.5, f3(4.5)}},
      3,
      OK  // x y не по порядку в изнач точках
    },
    {
      (point[]) {{0, f3(0)}, {1, f3(1)}, {2, f3(2)}, {4, f3(4)}},
      4,
      (point[]) {{-9, f3(-9)}, {-9, f3(-9)}, {-9, f3(-9)}},
      3,
      ERR_INTER_POINTS // точки интерполяции совпали
    }
  };

  // Количество тестовых данных
  int test_num = sizeof(tests) / sizeof(tests[0]);

  // Цикл по тестовым данным
  for (int i = 0; i < test_num; i++) {
    char file1[32], file2[32];
    sprintf(file1, "out%d.txt", 2 * (i + 1) - 1);
    sprintf(file2, "out%d.txt", 2 * (i + 1));
    out1 = fopen(file1, "w");
    if (out1 == NULL) {
      printf("test %d - file1 err\n", i + 1);
      continue;
    }
    out2 = fopen(file2, "w");
    if (out2 == NULL) {
      fclose(out1);
      printf("test %d - file2 err\n", i + 1);
      continue;
    }
    res = (double*)malloc(sizeof(double) * tests[i].qv_ip);
    if (res == NULL) {
      printf("test %d - memory err\n", i + 1);
      fclose(out1);
      fclose(out2);
      continue;
    }
    
    // Вызов функции interpolate
    interpolate(tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res, &err);
    
    // Проверка результата
    if (err != tests[i].err) {
      printf("тест %d потерпел крах\n", i + 1);
      free(res);
      fclose(out1);
      fclose(out2);
      continue;
    } else if (err == ERR_INTER_POINTS) {
      printf("тест %d пройден, но точки интерполяции совпали\n", i + 1);
      make_picture(out1, out2, tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res);
      free(res);
      fclose(out1);
      fclose(out2);
      continue;
    } else if (err == OK) {
      for (int j = 0; j < tests[i].qv_ip; j++) {
        if (fabs(res[j] - tests[i].i_points[j].y) > (max(fabs(res[j]), fabs(tests[i].i_points[j].y), 1.0) * eps)) {
          printf("тест %d не пройден \n", i + 1);
          free(res);
          fclose(out1);
          fclose(out2);
          continue;
        }
      }
      printf("тест %d пройден.\n", i + 1);
      make_picture(out1, out2, tests[i].xy_points, tests[i].qvp, tests[i].i_points, tests[i].qv_ip, res);
      free(res);
      fclose(out1);
      fclose(out2);
    }
  }

  return 0;
  }
