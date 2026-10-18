#include "Polygon.h"

#define eps 1e-6 

double pointToPointDist(const Point& a, const Point& b);
double pointToSegmentDist(const Point& p, const Point& a, const Point& b);
double segmentDistance(const Point& a, const Point& b, const Point& c, const Point& d);

double orientedAngle(const Point& a, const Point& b, const Point& c) 
{
    double dx1 = b.get_x() - a.get_x();
    double dy1 = b.get_y() - a.get_y();
    double dx2 = c.get_x() - b.get_x();
    double dy2 = c.get_y() - b.get_y();
    return std::atan2(dx1 * dy2 - dy1 * dx2, dx1 * dx2 + dy1 * dy2);
}


double minDistance(const Polygon& P1, const Polygon& P2) 
{
    int n = P1.get_n();
    int m = P2.get_n();
    double minDist = segmentDistance(P1.getPoint_i(0), P1.getPoint_i(1), P2.getPoint_i(0), P2.getPoint_i(1));

    int i = 1;
    int j = 1;
    double angle1 = 0;
    double angle2 = 0;

    Point OxOy(0.0, 0.0);
    do {
        Point A1 = P1.getPoint_i(i);
        Point A2 = P1.getPoint_i((i + 1) % n);
        Point B1 = P2.getPoint_i(j);
        Point B2 = P2.getPoint_i((j + 1) % m);
        minDist = std::min(minDist, segmentDistance(A1, A2, B1, B2));

        angle1 = orientedAngle(A1, A2, OxOy);
        angle2 = orientedAngle(B1, B2, OxOy);

        if (angle1 <= angle2) 
        {
            i = (i + 1) % n;
        } else {
            j = (j + 1) % m;
        }

    } while (i != 0 && j != 0);

    return minDist;
}

struct TestBox 
{
    std::string filename;
    double answer;
};

int main() 
{
    TestBox tests[] = {
        {"int1.txt", 2},
        {"int2.txt", 0},
        {"int3.txt", std::sqrt(2)},
        {"int4.txt", 1},
        {"int5.txt", std::sqrt(5)},
    };

    int k = std::size(tests);

    for(int i = 0; i < k; ++i)
    {
        try 
        {
            std::ifstream inputFile(tests[i].filename);

            if (!inputFile.is_open()) 
            {
                throw Error(-100,"Ошибка открытия файла: " + tests[i].filename);
            }

            int n;
            int m;
            double x;
            double y;

            std::vector<Point> vertices1;
            std::vector<Point> vertices2;

            inputFile >> n;

            for(int i = 0; i < n; ++i)
            {
                inputFile >> x >> y;
                //std::cout << "x = " << x << " y = " << y << std::endl;
                Point Dot(x, y);
                vertices1.push_back(Dot);
            }

            inputFile >> m;
            //std::cout << "m = " << m << std::endl;

            for(int j = 0; j < m; ++j)
            {
                inputFile >> x >> y;
                //std::cout << "x = " << x << " y = " << y << std::endl;
                Point Dot(x, y);
                vertices2.push_back(Dot);
            }

            Polygon P1(vertices1);
            Polygon P2(vertices2);


            double Ans = minDistance(P1, P2);

            if (std::abs(Ans - tests[i].answer) < eps) 
            {
                std::cout << "CORRECT test " << i + 1 << ": Расстояние = " << Ans << std::endl;
            } else {
                std::cerr << "NOT correct test " << i + 1
                          << ": Ожидалось " << tests[i].answer
                          << ", получено " << Ans << std::endl;
            }
        }
        catch(Error &err)
        {
            std::cout << "EXCEPTION: " << err.getReason() << "\n" << std::endl;
        }
        catch(...)
        {
            std::cout << "Something wrong\n" << std::endl;
        }
    }
    return 0;
}