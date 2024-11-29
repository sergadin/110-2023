#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include <vector>
#include <string>

class Triangle {
	public:
		Triangle();
		Triangle(const Point& a, const Point& b, const Point& c);

		const Point& getA() const;
		const Point& getB() const;
		const Point& getC() const;

		double getArea() const;
		double getIntersectionArea(const Triangle& other) const;

		void move(double dx, double dy);
		void rotate(double angle, const Point& center);

		bool isDef() const;

		void plot(const std::string& filename) const;
		std::vector<Point> getIntersectionPoints(const Triangle& other) const;
		bool isPointInside(const Point& p) const;


	private:
		Point a_;
		Point b_;
		Point c_;
		bool isDef_;
		double polygonArea(const std::vector<Point>& points) const;
};

#endif
