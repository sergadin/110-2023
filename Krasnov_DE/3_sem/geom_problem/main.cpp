#include "polygon1.h"


int main()
{
    unsigned size_p;
    cout << "enter the number of vertices" << endl; 
    cin >> size_p;
    vector<Point> points (size_p);
    for(size_t i=0; i != size_p; i++){
        cout << "enter x-coordinate" << endl;
        cin >> points[i].x;
        cout << "enter y-coordinate" << endl;
        cin >> points[i].y;
    }

    vector<Point> points1 = {{0,0}, {4,0}, {4,4}, {0,4}};
    //drawPolygonWithParallelLines(points, 1, 0, 10 , 1);
  
    
    try{
        const Polygon pol(points.size(), points);
        const Polygon pol1(points1.size(), points1);
        pol.Bulge_check();
        auto max_gap = pol.Get_max_gap();
        auto min_gap = pol.Get_min_gap();
        Vector v_max(points[max_gap.vertex1].x - points[max_gap.vertex2].x, points[max_gap.vertex1].y - points[max_gap.vertex2].y);
        Vector perp_max(v_max);
        drawPolygonWithParallelLines(points, max_gap.vertex1, max_gap.vertex2, perp_max.Get_a(), perp_max.Get_b());
        Vector perp_min(min_gap.second);
        drawPolygonWithParallelLines(points, min_gap.first.vertex1, min_gap.first.vertex2, perp_min.Get_a() , perp_min.Get_b());
        cout << min_gap.second.Get_a();
        //pol1.Bulge_check();
        //pol1.Get_max_gap();
        //pol1.Get_min_gap();
        
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    

    return 0;
}
