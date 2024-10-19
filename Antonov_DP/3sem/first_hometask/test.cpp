#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "triangle.h"

using namespace sf;

int main()
{

    RenderWindow window(VideoMode(2440, 1440), L"Новый проект", Style::Default);

    window.setVerticalSyncEnabled(true);

    double points[] = { 1,2,5,1,3,0 };
    double points2[] = { 2,3,3,2,3,1 };
    triangle test(points);
    triangle other(points2);
    double* centre = test.get_centre();
    double* centre1 = other.get_centre();
    double x = centre[0] - centre1[0];
    double y = centre[1] - centre1[1];
    double z = 0.1;

    ConvexShape shape(3);
    ConvexShape shape1(3);
    CircleShape circle((test.S_ / test.p_) * 100);
    circle.setPosition(200 + (centre[0] * 100), 200 + (centre[1] * 100));
    circle.setOrigin(((test.S_ / test.p_) * 100), ((test.S_ / test.p_) * 100));
    circle.setFillColor(Color(255, 0, 0));

    shape.setPosition(200, 200);
    for (int i = 0; i < 3; i++) {
        shape.setPoint(i, Vector2f(test.points_[i][0] * 100, test.points_[i][1] * 100));
    }
    shape.setFillColor(Color(61, 112, 255));

    shape1.setPosition(200, 200);
    for (int i = 0; i < 3; i++) {
        shape1.setPoint(i, Vector2f(other.points_[i][0] * 100, other.points_[i][1] * 100));
    }
    shape1.setFillColor(Color(61, 112, 0));

    std::cout << centre[0] << " " <<centre[1] << "\n";

    while (window.isOpen())
    {
        if (std::abs(centre[0] - centre1[0]) > 0.0001)
        {
            other.move(x * z, y * z);
            centre1[0] += (x * z);
            centre1[1] += (y * z);
        }
        else {
            other.rotate(centre1, 0.03);
        }
        shape1.setPosition(200, 200);
        for (int i = 0; i < 3; i++) {
            shape1.setPoint(i, Vector2f(other.points_[i][0] * 100, other.points_[i][1] * 100));
        }
        shape1.setFillColor(Color(61, 112, 0));

        int len = 0;
        point* vert = new point[10];
        for (int i = 0; i < 3; i++) {
            point temp;
            temp = other[i];
            if (test.contains(other[i])) {

                vert[len] = other[i];
                len++;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (other.contains(test[i])) {
                vert[len] = test[i];
                len++;
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                point temp;
                temp = test.get_segment(i).intersection(other.get_segment(j));
                if (temp.real()) {
                    vert[len] = temp;
                    len++;
                }
            }
        }

        point center;
        for (int i = 0; i < len; i++) {
            center[0] += vert[i][0];
            center[1] += vert[i][1];
        }
        center[0] /= len;
        center[1] /= len;
        double* length = new double[len];
        for (int i = 0; i < len; i++) {
            vert[i][0] -= center[0];
            vert[i][1] -= center[1];
            length[i] = sqrt(pow(vert[i][0], 2) + pow(vert[i][1], 2));
            vert[i][0] /= length[i];
            vert[i][1] /= length[i];
        }
        double* angles = new double[len];
        for (int i = 0; i < len; i++) {
            if ((std::asin(vert[i][1]) < 0)) {
                angles[i] = (std::acos(-1) - std::acos(vert[i][0])) + std::acos(-1);
            }
            else { angles[i] = std::acos(vert[i][0]); }
        }

        double temp_angle;
        double temp_length;
        point temp_vert;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (angles[j] > angles[i]) {
                    temp_angle = angles[i];
                    angles[i] = angles[j];
                    angles[j] = temp_angle;


                    temp_length = length[i];
                    length[i] = length[j];
                    length[j] = temp_length;


                    temp_vert = vert[i];
                    vert[i] = vert[j];
                    vert[j] = temp_vert;
                }
            }
        }


        for (int i = 0; i < len; i++) {
            vert[i][0] *= length[i];
            vert[i][1] *= length[i];
            vert[i][0] += center[0];
            vert[i][1] += center[1];
        }

        delete[] length;
        delete[] angles;

        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        window.draw(shape);
        window.draw(circle);
        window.draw(shape1);
        if (len < 3) {
            delete[] vert;
            len = 0;
        }
        else {
            ConvexShape inter(len);
            inter.setPosition(200, 200);
            for (int i = 0; i < len; i++) {
                inter.setPoint(i, Vector2f(vert[i][0] * 100, vert[i][1] * 100));
            }
            inter.setFillColor(Color(200, 112, 255));
            window.draw(inter);
            delete[] vert;
            len = 0;
        }
        window.display();
        Time t = sf::seconds(0.1);
        sleep(t);
    }
    double area = test.Area_intersection(other);
    std::cout << area << " " << other.get_s() << "\n";
    return 0;
}
