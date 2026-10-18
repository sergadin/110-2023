#include <algorithm>
#include "point.h"
#include "triangle.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <set>
#include <limits>

int main() {
	// Задаем координаты вершин треугольников. 

	//Point a1(0, 0), b1(1, 0), c1(0, 1);
	// Point a2(0.5, 0.5), b2(1.5, 0.5), c2(2, 1.5);

	//Point a1(0, 0), b1(3, 0), c1(1.5, 2);
	//Point a2(0, 0), b2(2, 0), c2(1, 1.5);

	Point a1(0, 0), b1(1, 0), c1(0, 1);
	Point a2(0.5, 0.5), b2(1.5, 3), c2(2, 1.5);

	//Point a1(0, 0), b1(1, 0), c1(0, 1);
	//Point a2(1, 1), b2(2, 1), c2(1, 2);

	//Point a1(0, 0), b1(1, 0), c1(0, 1);
	//Point a2(0, 0), b2(4, 0), c2(0, 4);

	//Point a1(2, 3), b1(1, 2), c1(4, 1);
	//Point a2(2, 1), b2(5, 0), c2(3, 4);

	Triangle triangle1(a1, b1, c1);
	Triangle triangle2(a2, b2, c2);

	// Хотим найти наилучшее смещение
	double bestArea = 0;
	Triangle bestTriangle1 = triangle1;
	Triangle bestTriangle2 = triangle2;

	double bestDx = 0;
	double bestDy = 0;
	double bestAngle = 0;

	const double moveStep = 0.1;
	const double rotateStep = 0.1;
	const double moveRange = 2.0;
	const double rotateRange = 2 * M_PI;
	Triangle tempTriangle1;
	for (double dx = -moveRange; dx <= moveRange; dx += moveStep) {
		for (double dy = -moveRange; dy <= moveRange; dy += moveStep) {
			for (double angle = 0; angle <= rotateRange; angle += rotateStep) {
				tempTriangle1 = triangle1;
				tempTriangle1.move(dx, dy);

				Point center(
						(triangle1.getA().getX() + triangle1.getB().getX() + triangle1.getC().getX()) / 3.0,
						(triangle1.getA().getY() + triangle1.getB().getY() + triangle1.getC().getY()) / 3.0
					    );
				tempTriangle1.rotate(angle, center);

				double area = tempTriangle1.getIntersectionArea(triangle2);

				if (area > bestArea) {
					bestArea = area;
					bestTriangle1 = tempTriangle1;
					bestTriangle2 = triangle2;
					bestDx = dx;
					bestDy = dy;
					bestAngle = angle;
				}
			}
		}
	}

	// Вывод результата
	std::cout << "Наилучшее совмещение:" << std::endl;
	std::cout << "Треугольник 1:" << std::endl;
	std::cout << "A: (" << bestTriangle1.getA().getX() << ", " << bestTriangle1.getA().getY() << ")" << std::endl;
	std::cout << "B: (" << bestTriangle1.getB().getX() << ", " << bestTriangle1.getB().getY() << ")" << std::endl;
	std::cout << "C: (" << bestTriangle1.getC().getX() << ", " << bestTriangle1.getC().getY() << ")" << std::endl;
	std::cout << "Треугольник 2:" << std::endl;
	std::cout << "A: (" << bestTriangle2.getA().getX() << ", " << bestTriangle2.getA().getY() << ")" << std::endl;
	std::cout << "B: (" << bestTriangle2.getB().getX() << ", " << bestTriangle2.getB().getY() << ")" << std::endl;
	std::cout << "C: (" << bestTriangle2.getC().getX() << ", " << bestTriangle2.getC().getY() << ")" << std::endl;
	std::cout << "Площадь пересечения: " << bestArea << std::endl;
	std::cout << "Сдвиг: (" << bestDx << ", " << bestDy << ")" << std::endl;
	std::cout << "Угол поворота: " << bestAngle << std::endl;


	// Находим точки пересечения
	std::vector<Point> intersectionPoints = bestTriangle1.getIntersectionPoints(bestTriangle2);

	// Определяем xrange и yrange
	double minX = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::lowest();
	double minY = std::numeric_limits<double>::max();
	double maxY = std::numeric_limits<double>::lowest();

	auto updateMinMax = [&](const Point& p) {
		minX = std::min(minX, p.getX());
		maxX = std::max(maxX, p.getX());
		minY = std::min(minY, p.getY());
		maxY = std::max(maxY, p.getY());
	};

	updateMinMax(a1);
	updateMinMax(b1);
	updateMinMax(c1);
	updateMinMax(a2);
	updateMinMax(b2);
	updateMinMax(c2);
	updateMinMax(bestTriangle1.getA());
	updateMinMax(bestTriangle1.getB());
	updateMinMax(bestTriangle1.getC());

	// Рисуем все в одном файле
	std::ofstream intersectionFile("intersection.plt");
	intersectionFile << "set terminal png" << std::endl;
	intersectionFile << "set output 'intersection.png'" << std::endl;
	intersectionFile << "set title 'Initial and Transformed Triangles with Intersection'" << std::endl;
	intersectionFile << "set xrange [" << minX - 0.2 << ":" << maxX + 0.2 << "]" << std::endl;
	intersectionFile << "set yrange [" << minY - 0.2 << ":" << maxY + 0.2 << "]" << std::endl;
	intersectionFile << "plot '-' with lines lw 2 lc rgb 'blue' title 'Triangle 1 (Initial)', '-' with lines lw 2 lc rgb 'green' title 'Triangle 2', '-' with lines lw 2 lc rgb 'red' title 'Intersection', '-' with lines lw 2 lc rgb 'cyan' title 'Triangle 1 (Transformed)'" << std::endl;


	// Данные для треугольника 1
	intersectionFile << triangle1.getA().getX() << " " << triangle1.getA().getY() << std::endl;
	intersectionFile << triangle1.getB().getX() << " " << triangle1.getB().getY() << std::endl;
	intersectionFile << triangle1.getC().getX() << " " << triangle1.getC().getY() << std::endl;
	intersectionFile << triangle1.getA().getX() << " " << triangle1.getA().getY() << std::endl;
	intersectionFile << "e" << std::endl;

	// Данные для треугольника 2
	intersectionFile << triangle2.getA().getX() << " " << triangle2.getA().getY() << std::endl;
	intersectionFile << triangle2.getB().getX() << " " << triangle2.getB().getY() << std::endl;
	intersectionFile << triangle2.getC().getX() << " " << triangle2.getC().getY() << std::endl;
	intersectionFile << triangle2.getA().getX() << " " << triangle2.getA().getY() << std::endl;
	intersectionFile << "e" << std::endl;

	// Данные для пересечения
	for (const auto& p : intersectionPoints) {
		intersectionFile << p.getX() << " " << p.getY() << std::endl;
	}
	if (!intersectionPoints.empty()) {
		intersectionFile << intersectionPoints[0].getX() << " " << intersectionPoints[0].getY() << std::endl;
	}
	intersectionFile << "e" << std::endl;

	// Данные для преобразованного треугольника 1
	intersectionFile << bestTriangle1.getA().getX() << " " << bestTriangle1.getA().getY() << std::endl;
	intersectionFile << bestTriangle1.getB().getX() << " " << bestTriangle1.getB().getY() << std::endl;
	intersectionFile << bestTriangle1.getC().getX() << " " << bestTriangle1.getC().getY() << std::endl;
	intersectionFile << bestTriangle1.getA().getX() << " " << bestTriangle1.getA().getY() << std::endl;
	intersectionFile << "e" << std::endl;

	intersectionFile.close();
	system("gnuplot intersection.plt");

	return 0;
}
