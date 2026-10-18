
#include "./utils/utils.h"

int main(void)
{
    int N = 0;
    double X = 0;
    double Y = 0;
    Point A{0, 0};
    Segment I(A, A);
    std::cout << "Enter number of segments\n";
    std::cin >> N;
    std::vector<Point> Points;
    std::vector<Segment> Segments;
    std::cout << "Enter the ends of the segments\n";
    for(int i = 0; i < 2*N; i++){
        std::cin >> X >> Y;
        A.x = X;
        A.y = Y;
        Points.push_back(A);
        if(i % 2 == 1){
            I = Segment(Points[i-1], Points[i]);
            Segments.push_back(I);
        }
    }
    draw(N, Segments, ExactlyPolygon(Segments, N));
     //draw(N, Segments, 1);
   //std::cout<<ExactlyPolygon(Segments, N);
   return 0;
}
