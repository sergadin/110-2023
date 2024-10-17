#include "geom_obj.h"

Point& Point::operator=(const Point &p){
      if(this != &p){
        x_ = p.x_;
        y_ = p.y_;
      }
      return *this;
    }
 
 Point& Point::operator=(Point&& p) noexcept{
      if(this != &p){
        x_ = p.x_;
        y_ = p.y_;
        p.x_ = 0;
        p.y_ = 0;
      }
      return *this;
    }
    
bool Point::operator<(const Point& other) const{
    double x1 = x_, x2 = other.x_, y1 = y_, y2 =other.y_;
      if((x1 < x2) || ((fabs(x1 - x2) < eps) && (y1 < y2))){
        return true;
      }else{
        return false;
      }
    }
bool findEl(const std::vector<Point> &p, Point el){
  return (std::find(p.begin(), p.end(), el) != p.end());
}

ConComp::ConComp(const std::vector<Point> &p){
    for (const auto&i : p){
      parent_.emplace(i, i);
    }
  }

Point ConComp::Find(Point x){
if(!parent_.count(x)){
  throw MstError(-2, std::string("Wrong index\n"));
}
     if (parent_[x] != x){
        parent_[x] = Find(parent_[x]);
      }
      return parent_[x];
    }
    
    
void ConComp::Union(Point x, Point y){
      Point rootX = Find(x);
      Point rootY = Find(y);
      parent_[rootY] = rootX;
    }



