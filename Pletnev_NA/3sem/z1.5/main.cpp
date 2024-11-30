#include "Polygon.h"

#define eps 1e-6 

double dot_product(const Point& a, const Point& b);
double pointToPointDist(const Point& a, const Point& b);
double cross_product(const Point& a, const Point& b, const Point& c);
double pointToSegmentDist(const Point& p, const Point& a, const Point& b);
double segmentDistance(const Point& a, const Point& b, const Point& c, const Point& d);

double minDistance(const Polygon& P1, const Polygon& P2) 
{
    int n = P1.get_n();
    int m = P2.get_n();
    double minDist = pointToPointDist(P1.getPoint_i(0), P2.getPoint_i(0));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            double currDist = segmentDistance(P1.getPoint_i(i), P1.getPoint_i((i + 1) % n), P2.getPoint_i(j), P2.getPoint_i((j + 1) % m));
            minDist = std::min(minDist, currDist);
        }
    }

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
        {"int3.txt", std::sqrt(2)}
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
            //std::cout << "n = " << n << "\n" << std::endl;

            for(int j = 0; j < n; ++j)
            {
                inputFile >> x >> y;
                //std::cout << "x = " << x << " y = " << y << "\n" << std::endl;
                Point Dot(x, y);
                vertices1.emplace_back(Dot);
            }

            inputFile >> m;
            //std::cout << "m = " << m << "\n" << std::endl;

            for(int j = 0; j < m; ++j)
            {
                inputFile >> x >> y;
                //std::cout << "x = " << x << " y = " << y << "\n" << std::endl;
                Point Dot(x, y);
                vertices2.emplace_back(Dot);
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