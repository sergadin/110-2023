#ifndef MST
#define MST

#include "geom_obj.h"

namespace shortNames{
  using Points = std::vector<Point>;
  using const_iterator = Points::const_iterator;
}
std::vector<Point> removeDuplicates(const std::vector<Point>& p);

class MST_builder{
private: 
    std::vector <Point> points_{};
    std::map<Point, Point> pnt_{};
public:
    using Points = std::vector<Point>;
    using const_iterator = Points::const_iterator;
    //using MST = std::vector<Edge>;
    MST_builder() = default; //конструктор по умолчанию
    MST_builder(const std::vector<Point> &p); //конструктор
    MST_builder(const MST_builder& p): points_(p.points_), pnt_(p.pnt_){} //конструктор копирования
    MST_builder(MST_builder&& other) noexcept : points_(std::move(other.points_)), pnt_(std::move(other.pnt_)){} //конструктор перемещения
    ~MST_builder() = default; //деструктор
    
    const_iterator cbegin() const{
        return points_.cbegin();
    }
    const_iterator cend() const{
        return points_.cend();
    }
    
    /*
     * Параметры:
     * p- новая точка, которую необходимо добавить в вектор.
     * Метод добавляет в вектор точек новую точку.
     */
  void add_point(const Point& p){
    if(!findEl(points_, p)){
        points_.push_back(p);
        pnt_.emplace(p, p);
      }
    }
  /*
   * Параметры:
   * it - итератор точки, которую надо удалить.
   * Метод удаляет из вектора точку.
   */  
  void del_point(const_iterator &it);
  
  /*
   * Метод по множеству точек строит Минимальное покрывающее дерево, используя алгоритм Краскала.
   * Метод возвращает вектор ребер, составляющих МПД.
   */
  std::vector<Edge> MST_build();
    
};

/*
 * Параметры:
 *  mst - вектор ребер МПД,
 * Функция рисует полученный граф с помощью gnuplot.
 */
void plotMst(const std::vector<Edge> &mst);

#endif 
