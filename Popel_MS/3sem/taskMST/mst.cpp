
#include "mst.h"
#include <algorithm>
#include <fstream>

std::vector<Point> removeDuplicates(const std::vector<Point>& p){
  std::set<Point> unique(p.begin(), p.end());
  return (std::vector<Point>(unique.begin(), unique.end()));
}

std::vector<Edge> makeEdges(const std::vector<Point> &p){
  std::vector<Edge> e;
  int sz = p.size();
  for(int i = 0; i < sz; i++){
    for (int j = i + 1; j < sz; j++){
      e.push_back({p[i], p[j]}); 
    }
  }
  return e;
}
MST_builder::MST_builder(const std::vector <Point> &p){
  int sz = 0;
  points_ = removeDuplicates(p);
  sz = points_.size();
  for (int i = 0; i < sz; i++){
    pnt_.emplace(points_[i], points_[i]);
  }
}

void MST_builder::del_point(const_iterator &it){
    if((it >= points_.begin())&& (it <= points_.end())){
      points_.erase(it);
      pnt_.erase(*it);
      }
    }
std::vector<Edge> MST_builder::MST_build(){
  std::vector<Edge> edges = makeEdges(points_);
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
    return (e1 < e2);
  });
  ConComp set(points_);
  std::vector<Edge> res;
  int sz = edges.size();
  
  for(int i = 0; i < sz; i++){
    if(set.Find(edges[i].get_St()) != set.Find(edges[i].get_End())){
      set.Union(edges[i].get_St(), edges[i].get_End());
      res.push_back(edges[i]);
    }
  }
  return res;
}


void plotMst(const std::vector<Edge> &mst){
  std::ofstream fout;
  int sz = mst.size();
  fout.open("output.txt");
  
  if (!fout){
    throw MstError(-1, std::string("File opening error\n"));
  }
  
  for(int j = 0; j < sz; j++){
    fout << (mst[j].get_St()).getX() << " " << (mst[j].get_St()).getY() << " " << ((mst[j].get_End()).getX()-       (mst[j].get_St()).getX()) << " " << ((mst[j].get_End()).getY() - (mst[j].get_St()).getY()) << std::endl;
  }
  fout.close();
  
  system("gnuplot -e \"set size ratio 1; set xrange [0:*]; set yrange [0:*]; plot 'output.txt' using 1:2:3:4 with vectors nohead\" -p");
}
//points, '' using 1:2 with lines
