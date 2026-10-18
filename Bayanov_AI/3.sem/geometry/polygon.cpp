#include "./utils/utils.h"

int Point::EqualsPoint(const Point& A){
    if(A.x == x && A.y == y)
        return 1;
    return 0;
}

Segment::Segment(){}
Segment::Segment(const Point &pv, const Point &qv): p(pv), q(qv) {}
Point Segment::P(){
    return p;
}
Point Segment::Q(){
    return q;
}
Segment::~Segment(){}

Straight::Straight(){}
Straight::Straight(double a, double b, double c): a(a), b(b), c(c) {}
Straight::Straight(const Point &P, const Point &Q): a(Q.y-P.y), b(P.x-Q.x), c(Q.x*P.y-Q.y*P.x) {}
double Straight::A(){
    return a;
}
double Straight::B(){
    return b;
}
double Straight::C(){
    return c;
}
int Straight::Sign(const Point& P){
    double L = a*P.x + b*P.y + c;
    if(L > 0){
        return 1;
    }
    if(L < 0){
        return -1;
    }
    return 0;
    }
Straight::~Straight(){}


void draw(int N, std::vector<Segment> Segments, int color){
    FILE *input = NULL;
    FILE *gp = NULL;
    Point P{0, 0};
    Point Q{0, 0};

    input = fopen("Test.txt", "w");
    for(int i = 0; i < N; i++){
        P = Segments[i].P();
        fprintf(input, "%lf ", P.x);
        fprintf(input, "%lf ", P.y);
    }
    fprintf(input, "\n");
    for(int i = 0; i < N; i++){
        Q = Segments[i].Q();
        fprintf(input, "%lf ", Q.x);
        fprintf(input, "%lf ", Q.y);
    }
    fclose(input);


    gp = popen("gnuplot -persist","w");
    fprintf(gp, "set yrange [-5:5]\n");
    fprintf(gp, "set xrange[-5:5]\n");
    fprintf(gp, "set grid\n");
    if(color == 1)
        fprintf(gp, "plot 'Test.txt' u 1:2 w l lc rgb 'green'");
            else
        fprintf(gp, "plot 'Test.txt' u 1:2 w l lc rgb 'red'");
    for(int i = 3; i < 2*N+1; i+=2){
    if(color == 1)
        fprintf(gp, ", 'Test.txt' u %d:%d w l lc rgb 'green'", i, i+1);
            else
        fprintf(gp, ", 'Test.txt' u %d:%d w l lc rgb 'red'", i, i+1);
    }
    fprintf(gp, "\n");
    
    pclose(gp);
}
//Функция, которая рисует множество отрезков. Если они образуют многоугольник, то они рисуются зеленым цветом, иначе - красным.

int InsectSegments(Segment I1, Segment I2){
    Straight L1(I1.P(), I1.Q());
    Straight L2(I2.P(), I2.Q());
    if((L1.Sign(I2.P())*L1.Sign(I2.Q()) < 0) && (L2.Sign(I1.P())*L2.Sign(I1.Q()) < 0)){
        return 1;
    }
    if((I1.P()).EqualsPoint(I2.P()) + (I1.P()).EqualsPoint(I2.Q()) +(I1.Q()).EqualsPoint(I2.P()) + (I1.Q()).EqualsPoint(I2.Q()) > 0){
        return 1;
    }
    if((L1.Sign(I2.P())*L1.Sign(I2.Q()) < 0) && (L2.Sign(I1.P())*L2.Sign(I1.Q()) == 0)){
        return 1;
    }
    if((L1.Sign(I2.P())*L1.Sign(I2.Q()) == 0) && (L2.Sign(I1.P())*L2.Sign(I1.Q()) < 0)){
        return 1;
    }

    return 0;
}
//Функция, которая проверяет пересечение двух отрезков


int ExactlyPolygon(const std::vector<Segment> &Segments, int n){
    Segment I = Segments[0];
    Segment J = Segments[0];
    double x = (I.Q()).x;
    double y = (I.Q()).y;
    int flag = 1;
    std::vector<Segment> polygon(Segments);

    for(int m = 0; m < n - 1; m++){
        for(int k = m + 1; k < n; k++){
		J = polygon[k];
            if(x == (J.P()).x && y == (J.P()).y){
                x = (J.Q()).x;
                y = (J.Q()).y;
		polygon[k] = polygon[m+1];
		polygon[m+1] = J;
                break;
            }
            if(x == (J.Q()).x && y == (J.Q()).y){
                x = (J.P()).x;
                y = (J.P()).y;
		polygon[k] = polygon[m+1];
		polygon[m+1] = J;
                break;
            }
	    if(k == n - 1){
		flag = 0;
	    }
	}
        }
    if((polygon[0].P()).x != x || (polygon[0].P()).y != y){
	    flag = 0;
    }

    for(int m = 1; m < n-1; m++){
        for(int k = 0; k < n; k++){
            if(k != m-1 && k != m+1 && k != m){
                if(InsectSegments(polygon[k], polygon[m]) == 1){
                    flag = 0;
                }
            }
        }
    }
 for(int k = 2; k < n-1; k++){
                if(InsectSegments(polygon[0], polygon[k]) == 1){
                    flag = 0;
                }
            }

 for(int k = 1; k < n-2; k++){
                if(InsectSegments(polygon[n-1], polygon[k]) == 1){
                    flag = 0;
                }
            }

    return flag;
}

//Главная функция, которая проверяет, образует ли данное множество отрезков многоугольник.