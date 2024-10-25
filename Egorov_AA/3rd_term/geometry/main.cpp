

int main() {
    Polygon polygon;

    // Добавляем вершины многоугольника
    polygon.addVertex(Point(0, 0));
    polygon.addVertex(Point(4, 0));
    polygon.addVertex(Point(4, 3));
    polygon.addVertex(Point(0, 3));

    // Выводим вершины
    polygon.print();

    // Вычисляем периметр и площадь
    cout << "Perimeter: " << polygon.getPerimeter() << endl;
    cout << "Area: " << polygon.getArea() << endl;

    return 0;
}
