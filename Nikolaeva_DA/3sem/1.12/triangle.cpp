#include "triangle.h"
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>



Triangle::Triangle() : a_(0, 0), b_(0, 0), c_(0, 0), isDef_(true) {}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a_(a), b_(b), c_(c), isDef_(true) {}

const Point& Triangle::getA() const { return a_; }

const Point& Triangle::getB() const { return b_; }

const Point& Triangle::getC() const { return c_; }

double Triangle::getArea() const {
	double a = std::sqrt(std::pow(b_.getX() - a_.getX(), 2) + std::pow(b_.getY() - a_.getY(), 2));
	double b = std::sqrt(std::pow(c_.getX() - b_.getX(), 2) + std::pow(c_.getY() - b_.getY(), 2));
	double c = std::sqrt(std::pow(a_.getX() - c_.getX(), 2) + std::pow(a_.getY() - c_.getY(), 2));
	double s = (a + b + c) / 2;
	return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::getIntersectionArea(const Triangle& other) const {
	std::vector<Point> intersectionPoints = getIntersectionPoints(other);
	return polygonArea(intersectionPoints);
}

void Triangle::move(double dx, double dy) {
	a_.move(dx, dy);
	b_.move(dx, dy);
	c_.move(dx, dy);
}

void Triangle::rotate(double angle, const Point& center) {
	a_.rotate(angle, center);
	b_.rotate(angle, center);
	c_.rotate(angle, center);
}

bool Triangle::isDef() const { return isDef_; }

void Triangle::plot(const std::string& filename) const {
	std::ofstream file(filename + ".plt");
	file << "set xrange [-10:10]" << std::endl;
	file << "set yrange [-10:10]" << std::endl;
	file << "set terminal png" << std::endl;
	file << "set output '" << filename << ".png'" << std::endl;
	file << "plot '-' with lines" << std::endl;
	file << a_.getX() << " " << a_.getY() << std::endl;
	file << b_.getX() << " " << b_.getY() << std::endl;
	file << c_.getX() << " " << c_.getY() << std::endl;
	file << a_.getX() << " " << a_.getY() << std::endl;
	file << "e" << std::endl;
	file.close();
}

Point getLineIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	double x1 = p1.getX();
	double y1 = p1.getY();
	double x2 = p2.getX();
	double y2 = p2.getY();
	double x3 = p3.getX();
	double y3 = p3.getY();
	double x4 = p4.getX();
	double y4 = p4.getY();

	double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (std::abs(den) < 1e-6) return Point();

	double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		return Point(x1 + t * (x2 - x1), y1 + t * (y2 - y1));
	} else {
		return Point(); 
	}
}
std::vector<Point> Triangle::getIntersectionPoints(const Triangle& other) const {
	std::vector<Point> intersectionPoints;
	std::vector<Point> triangle1Points = {a_, b_, c_};
	std::vector<Point> triangle2Points = {other.a_, other.b_, other.c_};

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			Point intersection = getLineIntersection(triangle1Points[i], triangle1Points[(i + 1) % 3],
					triangle2Points[j], triangle2Points[(j + 1) % 3]);
			if (intersection.isDef()) {
				bool alreadyExists = false;
				for (const auto& p : intersectionPoints) {
					if (std::abs(p.getX() - intersection.getX()) < 1e-6 &&
							std::abs(p.getY() - intersection.getY()) < 1e-6) {
						alreadyExists = true;
						break;
					}
				}
				if (!alreadyExists) intersectionPoints.push_back(intersection);
			}
		}
	}

	for (const auto& p : triangle1Points) {
		if (other.isPointInside(p)) intersectionPoints.push_back(p);
	}
	for (const auto& p : triangle2Points) {
		if (isPointInside(p)) intersectionPoints.push_back(p);
	}

	//сортировка точек по углу относительно центра тяжести
	if (!intersectionPoints.empty()) {
		Point centroid = { (a_.getX() + b_.getX() + c_.getX()) / 3.0, (a_.getY() + b_.getY() + c_.getY()) / 3.0 };
		std::sort(intersectionPoints.begin(), intersectionPoints.end(), [&](const Point& a, const Point& b) {
				double angleA = std::atan2(a.getY() - centroid.getY(), a.getX() - centroid.getX());
				double angleB = std::atan2(b.getY() - centroid.getY(), b.getX() - centroid.getX());
				return angleA < angleB;
				});
	}

	// testing print
	//for(Point &p : intersectionPoints) {
	//    std::cout << p << std::endl;
	//}



	return intersectionPoints;
}

bool Triangle::isPointInside(const Point& p) const {
	double area = getArea();
	double area1 = Triangle(a_, b_, p).getArea();
	double area2 = Triangle(b_, c_, p).getArea();
	double area3 = Triangle(c_, a_, p).getArea();
	return std::abs(area - (area1 + area2 + area3)) < 1e-6;
}


double Triangle::polygonArea(const std::vector<Point>& points) const {
	if (points.size() < 3) return 0;
	double area = 0;
	for (size_t i = 0; i < points.size(); ++i) {
		area += (points[i].getX() * points[(i + 1) % points.size()].getY() -
				points[(i + 1) % points.size()].getX() * points[i].getY());
	}
	return std::abs(area) / 2.0;
}
