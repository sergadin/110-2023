#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream> 
#include <math.h>
#include <vector>

#include "Error.h"
#include "Dot.h"
#include "Vector.h"
#include "Polygon.h"

using namespace std;

double interval(const Dot& A, const Dot& B) 
{
    return sqrt(pow(A.get_x() - B.get_x(), 2) + pow(A.get_y() - B.get_y(), 2));
}

double determinant(const Vector& v1, const Vector& v2) 
{
    return v1.get_vx() * v2.get_vy() - v1.get_vy() * v2.get_vx();
}


// Метод вращающихся калиперов для нахождения минимального расстояния
double Distance(const Polygon& P1, const Polygon& P2) 
{
    int n = P1.get_n();
    int m = P2.get_n();

    int index = 0;

    for (int i = 1; i < m; ++i) 
    {
        if (P2.get_dot(i).get_x() < P2.get_dot(index).get_x()) 
        {
            index = i;
        }
    }

    double minDist = interval(P1.get_dot(0), P2.get_dot(0));

    for (int i = 0; i < n; ++i) 
    {
        Dot I1 = P1.get_dot(i);
        Dot I2 = P1.get_dot((i + 1) % n);
        int j = index;

        for (int k = 0; k < m; ++k) {

            Dot J1 = P2.get_dot(j);
            Dot J2 = P2.get_dot((j + 1) % m);

            Vector v1(I2.get_x() - I1.get_x(), I2.get_y() - I1.get_y());
            Vector v2(J1.get_x() - I1.get_x(), J1.get_y() - I1.get_y());
            Vector v3(J2.get_x() - I1.get_x(), J2.get_y() - I1.get_y());
            

            if (determinant(v1, v2) > determinant(v1, v3)) {
                j = (j + 1) % m;
            }
            else
            {
                double dist1 = interval(I1, J1);
                double dist2 = interval(I2, J1);

                minDist = min(minDist, min(dist1, dist2));
            }


        }
    }

    return minDist;
}


int main() 
{
    int n;
    int m;
    ifstream inp_f("input.txt");

    if (!inp_f.is_open()) 
    {
        cerr << "Error opening file" << endl;
        return -2;
    }

    inp_f >> n;
    Polygon P1(n);

    for (int i = 0; i < n; ++i) 
    {
        double x, y;
        inp_f >> x >> y;
        P1.add_dot(Dot(x, y), i);
    }

    inp_f >> m;
    Polygon P2(m);

    for (int i = 0; i < m; ++i) 
    {
        double x, y;
        inp_f >> x >> y;
        P2.add_dot(Dot(x, y), i);
    }

    inp_f.close();
		
    try 
    {
        double result = Distance(P1, P2);
        cout << "Минимальное расстояние между двумя многоугольниками: " << result << endl;
    }
    catch (const exception& e) 
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}