#include "ConvexHull.h"
#include <algorithm>

ConvexHull::ConvexHull() {}

void ConvexHull::addPoint(const Point& point) {
    points.push_back(point);
}

std::vector<Point> ConvexHull::buildHull() {
    removeDuplicates(points);

    std::sort(points.begin(), points.end());

    std::vector<Point> lowerHull = findLowerHull(points);

    std::vector<Point> upperHull = findUpperHull(points);

    lowerHull.insert(lowerHull.end(), upperHull.begin() + 1, upperHull.end());

    return lowerHull;
}

std::vector<Point> ConvexHull::findLowerHull(const std::vector<Point>& points) {
    std::vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() >= 2 &&
               Point::orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
            hull.pop_back();
        }

        if(hull.back() != points[i]){
            hull.push_back(points[i]);
        }

    }

    return hull;
}

std::vector<Point> ConvexHull::findUpperHull(const std::vector<Point>& points) {
    std::vector<Point> hull;
    hull.push_back(points[points.size() - 1]);
    hull.push_back(points[points.size() - 2]);

    for (int i = points.size() - 3; i >= 0; --i) {
        while (hull.size() >= 2 && Point::orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
            hull.pop_back();
        }
	if(hull.back() != points[i]){
            hull.push_back(points[i]);
	}
    }

    return hull;
}

void ConvexHull::removeDuplicates(std::vector<Point>& points) {
    std::sort(points.begin() , points.end() );
    auto last = std:: unique(points.begin(), points.end());
    points.erase(last, points.end());
}
