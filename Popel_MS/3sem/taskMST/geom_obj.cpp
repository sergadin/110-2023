#include "geom_obj.h"

static int maxElofVect(const std::vector<Point> &v){
if (v.size()<=0){
  throw MstError(-3, std::string("Wrong size\n"));
}
int maxEl = v[0].getId();
  for (int i = 0; i < v.size(); i++){
    if(maxEl<v[i].getId()){
      maxEl = v[i].getId();
    }
  }
  return maxEl;
}
static int minElofVect(const std::vector<Point> &v){
if (v.size()<=0){
  throw MstError(-3, std::string("Wrong size\n"));
}
int minEl = v[0].getId();
  for (int i = 0; i < v.size(); i++){
    if(minEl>v[i].getId()){
      minEl = v[i].getId();
    }
  }
  return minEl;
}
Point& Point::operator=(const Point &p){
      if(this == &p){
      return *this;  
      }
      x_ = p.x_;
      y_ = p.y_;
      return *this;
    }
 
Edge::Edge(const Point& p1, const Point& p2): p1_(p1), p2_(p2), weight_(p1.Point::distance(p2)){
      p1_ = p1;
      p2_ = p2;
      weight_ = (p1.Point::distance(p2));
    }
 
DifSets::DifSets(const std::vector<Point> &p){
    parent_.resize(p.size(), -1);
    rank_.resize(p.size(), 0);
    for (int i = minElofVect(p); i <= maxElofVect(p); i++){
      parent_[i] = i;
    }
  }

int DifSets::Find(int x){
/*if(x>=maxElofVect(parent_)){
  throw MstError(-2, std::string("Wrong index\n"));
}*/
     if (parent_[x] != x){
        parent_[x] = Find(parent_[x]);
      }
      return parent_[x];
    }
    
    
void DifSets::Union(int x, int y){
//parent_[x] = parent_[y];

      int rootX = Find(x);
      int rootY = Find(y);
      parent_[rootY] = rootX;
     /* if(rootX != rootY){
        if(rank_[rootX] > rank_[rootY]){
          parent_[rootY] = rootX;
        }else if( rank_[rootX] < rank_[rootY]){
          parent_[rootX] = rootY;
        }else{
          parent_[rootY] = rootX;
          rank_[rootX]++;
        }
      }*/
    }
