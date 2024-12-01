#ifndef POINT_H
#define POINT_H

class Point {
private:

    double x, y;

public:
    // конструктор
    Point();
    Point(double x, double y);

    // геттеры
    double getX() const;
    double getY() const;

    // сеттеры
    void setX(double x_value);
    void setY(double y_value);

    // керегрузка операторов
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;

    void draw() const;

};

#endif // POINT_H
