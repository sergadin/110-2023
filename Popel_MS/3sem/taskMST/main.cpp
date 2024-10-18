#include "mst.h"
#include "geom_obj.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace shortNames;
int main(void){
try{
    Points points = {{3, 2},{2, 6},{9, 1}, {14, 6}, {8, 4}, {6, 6}, {3, 2}, {11, 8}, {7, 9}, {4, 11},{12, 3}};
    Point pnt(2, 2);
    Point dpnt(6, 6);
    
    printf("first - simple\n");
    MST_builder mst1(points);
    vector<Edge> res = mst1.MST_build();
    plotMst(res);
    
    mst1.add_point(pnt);
    printf("second - add point\n");
    vector<Edge> res2 = mst1.MST_build();
    plotMst(res2);
    
    mst1.del_point(dpnt);
    printf("third - delete point\n");
    vector<Edge> res3 = mst1.MST_build();
    plotMst(res3);
    return 0;
  }catch(MstError &err){
    cout << "EXCEPTION: " << err.getReason() << endl;
  }catch(...){
    cout << "Something wrong" << endl;
  }
  return 0;
}
