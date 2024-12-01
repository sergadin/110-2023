#ifndef POINT_H
#define POINT_H

#include <ostream>

class Point {
	public:
		Point();
		Point(double x, double y);

		double getX() const;
		double getY() const;

		void move(double dx, double dy);
		void rotate(double angle, const Point& center);

		bool isDef() const;

	private:
		double x_;
		double y_;
		bool isDef_;
};

std::ostream &operator<<(std::ostream &os, Point &p);

#endif

