#ifndef OBJ
#define OBJ

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>

/*
 * Класс ошибок.
 * Переменные: code_ - код ошибки, reason_ - причина ошибки;
 */
class MstError{ 
  private:
    int code_;
    std::string reason_;
  public:
    MstError(int code, std::string reason){ //Конструктор
      code_ = code;
      reason_ = reason;
    }
    std::string getReason(){ //Функция, выдающая причину ошибки
      return reason_;
    }
    int getCode(){ //Функция, выдающая код ошибки
      return code_;
    }
};

/*
 * Класс точек.
 * Переменные: x_ - первая координата, y_ - вторая координата, num_ - статическая переменная-счетчик точек, id_ - порядковый номер точки;
 */
class Point{
  private:
    double x_,y_;
    static int num_;
    int id_;
  public:
    Point(double x, double y):x_(x), y_(y){ //Конструктор
      x_ = x;
      y_ = y;
      id_ = num_++;
    }
    ~Point() { //Деструктор
      id_= 0;
      num_--;
      x_ = 0;
      y_ = 0;
    }
    double getX() const{ //Функция, возвращающая первую координату
      return x_;
    }
    double getY() const{ //Функция, возвращающая вторую координату
      return y_;
    }
    
    int getId() const{ //Функция, возвращающая номер точки
      return id_;
    }
    double distance(const Point &p) const{ //Расстояние между точками
      return sqrt((x_-p.x_)*(x_-p.x_) + (y_-p.y_)*(y_-p.y_));
    }
    Point &operator=(const Point &p);
};

/*
 * Класс ребер.
 * Переменные: p1_ - первый конец, p2_ - второй конец, weight_ - длина ребра(ее вес);
 */
class Edge { 
  private:
    Point p1_, p2_;
    double weight_;
  public:
    Edge(const Point& p1, const Point& p2); //Конструктор
    Point get_St() const{ //Функция, возвращающая первый конец
      return p1_;
    }
    Point get_End() const{ //Функция, возвращающая второй конец
      return p2_;
    }
    double get_Weight() const{ //Функция, возвращающая вес ребра
      return weight_;
    }
    bool operator<(const Edge& e) const{
      return (weight_ < e.weight_);
    }
};

/*
 * Класс компонент связности.
 * Переменные: parent_ - корневой элемент, rank_ - ранк(вес) элемента;
 */
class DifSets{
  private:
    std::vector<int> parent_;
    std::vector<int> rank_;
  public:
    DifSets(const std::vector <Point> &p); //Конструктор
    
    int Find(int x); //Функция, ищущая корневой элемент
    
    void Union(int x, int y); //Функция, объединяющая две компоненты связности
};

#endif
