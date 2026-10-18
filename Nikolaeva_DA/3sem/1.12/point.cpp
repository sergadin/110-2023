#include "point.h"
#include <cmath>

Point::Point() : x_(0), y_(0), isDef_(false) {}

Point::Point(double x, double y) : x_(x), y_(y), isDef_(true) {}

double Point::getX() const { return x_; }

double Point::getY() const { return y_; }

void Point::move(double dx, double dy) {
	x_ += dx;
	y_ += dy;
}

void Point::rotate(double angle, const Point& center) {
	double newX = (x_ - center.getX()) * cos(angle) - (y_ - center.getY()) * sin(angle) + center.getX();
	double newY = (x_ - center.getX()) * sin(angle) + (y_ - center.getY()) * cos(angle) + center.getY();
	x_ = newX;
	y_ = newY;
}

bool Point::isDef() const { return isDef_; }

std::ostream &operator<<(std::ostream &os, Point &p) {
	os << p.isDef() << " (" << p.getX() << ", " << p.getY() << ")";
	return os;
}

