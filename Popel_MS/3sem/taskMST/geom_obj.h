#ifndef OBJ
#define OBJ
#define eps 1e-6 

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>


/*
 * Класс ошибок.
 * Переменные: code_ - код ошибки, reason_ - причина ошибки;
 */
class MstError{ 
  private:
    int code_ = 0;
    std::string reason_ = "";
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
 * Переменные: x_ - первая координата, y_ - вторая координата;
 */
class Point{
  private:
    double x_ = 0, y_ = 0;
  public:
    Point() : x_(0), y_(0){}//конструктор без входных данных
    Point(double x, double y): x_(x), y_(y){}//конструктор
    Point(const Point& p){ //конструктор копирования
        x_=p.x_;
        y_=p.y_;
    }
    Point(Point&& p) noexcept : x_(p.x_), y_(p.y_){ //конструктор перемещения
      p.x_ = 0;
      p.y_ = 0;
    }
    Point& operator=(Point&& p) noexcept; //оператор перемещения
    ~Point() { //Деструктор
      x_ = 0;
      y_ = 0;
    }
    double getX() const{ //Функция, возвращающая первую координату
      return x_;
    }
    double getY() const{ //Функция, возвращающая вторую координату
      return y_;
    }
    double distance(const Point &p) const{ //Расстояние между точками
      return sqrt((x_ - p.x_)*(x_ - p.x_) + (y_ - p.y_)*(y_ - p.y_));
    }
    
    bool operator==(const Point& other) const { //оператор сравнения - равенство
      return (fabs(x_ - other.x_) < eps) && (fabs(y_ - other.y_) < eps);
    }
    
    bool operator!=(const Point& other) const{ //оператор сравнения - не равен
      return !(*this == other);
    } 
    bool operator<(const Point& other) const; //оператор сравнения - меньше: сперва сравнение по х, иначе по у
    Point &operator=(const Point &p); //оператор присваивания
};

/*
 * Параметры:
 *  р - вектор точек - вершин графа, el - искомый элемент
 * Функция ищет переданный элемент в полученном векторе
 * Функция возвращает true, если элемент найден, иначе - false.
 */
bool findEl(const std::vector<Point> &p, Point el);


/*
 * Класс ребер.
 * Переменные: p1_ - первый конец, p2_ - второй конец, weight_ - длина ребра(ее вес);
 */
class Edge{ 
  private:
    Point p1_, p2_;
    double weight_;
  public:
    Edge() = default;//конструктор по умолчанию
    Edge(const Point& p1, const Point& p2): p1_(p1), p2_(p2), weight_(p1.Point::distance(p2)){} //Конструктор
    Point get_St() const{ //Функция, возвращающая первый конец
      return p1_;
    }
    Point get_End() const{ //Функция, возвращающая второй конец
      return p2_;
    }
    double get_Weight() const{ //Функция, возвращающая вес ребра
      return weight_;
    }
    bool operator<(const Edge& e) const{ //оператор сравнения - сравнивает по весу ребер
      return (weight_ < e.weight_);
    }
};

/*
 * Параметры:
 *  р - вектор точек - вершин графа
 * Функция по множеству точек собирает вектор из всевозможных ребер с концами в переданных вершинах.
 * Функция возвращает вектор ребер.
 */
std::vector<Edge> makeEdges(const std::vector<Point> &p);

/*
 * Класс компонент связности.
 * Переменные: parent_ - корневой элемент
 */
class ConComp{
  private:
    std::map<Point, Point> parent_{};
  public:
    ConComp(const std::vector <Point> &p); //Конструктор
    Point Find(Point x); //Функция, ищущая корневой элемент
    void Union(Point x, Point y); //Функция, объединяющая две компоненты связности
};
#endif
