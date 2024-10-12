#include "geom_obj.h"
#include "mst.h"
#include <algorithm>
#include <fstream>

std::vector<Edge> makeEdges(const std::vector<Point>& p){
  std::vector<Edge> e;
  for(int i = 0; i < p.size(); i++){
    for (int j = i+1; j < p.size(); j++){
      double dist = p[i].distance(p[j]);
      std::cout << "("<<p[i].getX() <<", " << p[i].getY() << ") - (" << p[j].getX() << ", " << p[j].getY() <<")" << p[i].getId() << " " << p[j].getId() << std::endl;
      //Edge newE(p[i], p[j]);
      e.push_back({p[i], p[j]}); 
    }
  }
  return e;
}

std::vector<Edge> Mst(const std::vector<Point>& p){
  std::vector<Edge> edges = makeEdges(p);
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
    return (e1 < e2);
  });
  for (int i = 0 ; i < edges.size(); i++){
    std::cout << "(" << edges[i].get_St().getX() << ", " << edges[i].get_St().getY() << ") "<< (edges[i].get_St()).getId()<<" (" << edges[i].get_End().getX() << ", " << edges[i].get_End().getY() << ") " <<(edges[i].get_End()).getId() << " number "<< i << std::endl;
  }
  //std::cout << p.size() << std::endl;
  DifSets set(p);
  std::vector<Edge> res;
  
  for(int i = 0; i < edges.size(); i++){
    if(set.Find((edges[i].get_St()).getId()) != set.Find((edges[i].get_End()).getId())){
    /*std::cout << "(" << edges[i].get_St().getX() << ", " << edges[i].get_St().getY() << ") "<< (edges[i].get_St()).getId()<<" (" << edges[i].get_End().getX() << ", " << edges[i].get_End().getY() << ") " <<(edges[i].get_End()).getId() << " number "<< i << std::endl;*/
      set.Union((edges[i].get_St()).getId(), (edges[i].get_End()).getId());
      res.push_back(edges[i]);
    }
  }
  return res;
}

/*void addPoint(std::vector<Point>& p, Point newPoint){
  p.push_back(newPoint);
}*/

void plotMst(const std::vector<Edge> &mst, const std::vector<Point> &p){
  std::ofstream fout;
  fout.open("output.txt");
  
  if (!fout){
    throw MstError(-1, std::string("File opening error\n"));
  }
  
  for(int j = 0; j < mst.size(); j++){
    fout << (mst[j].get_St()).getX() << " " << (mst[j].get_St()).getY() << " " << ((mst[j].get_End()).getX()- (mst[j].get_St()).getX())<< " " << ((mst[j].get_End()).getY() - (mst[j].get_St()).getY())<< std::endl;
    //std::cout << (mst[j].get_St()).getX() << " " << (mst[j].get_St()).getY() << std::endl;
    //std::cout << (mst[j].get_End()).getX() << " " << (mst[j].get_End()).getY() << std::endl;
  }
  fout.close();
  
  system("gnuplot -e \"set size ratio 1; set xrange [0:*]; set yrange [0:*]; plot 'output.txt' using 1:2:3:4 with vectors nohead\" -p");
}
//points, '' using 1:2 with lines
