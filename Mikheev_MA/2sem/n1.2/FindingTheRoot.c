#include "FindingTheRoot.h"

double FindingTheRoot(RFun f, RFun g, double a, double b, double EPS, int *count, Er *error){
    double root;
    double x = a, y = b; // точки из метода Ньютона 
    int max_count = 10000; // максимальное количесвто итераций
    int i = 0; // счетчик
    
    
    for(i = 0; i < max_count && fabs(x - y) > EPS; i++){
        x = y;
        y = x - f(x)/g(x);
    }
    
    root = y;
    *error = OK;
    *count = i;
    
    if(root > b || root < a){
        *error = HAVE_NO_ROOT;
    }
    
    if(isnan(root) || isinf(root)){
        *error = NOT_CORRECT;
    }
    
    if(i == max_count - 1){
        *error = LIMIT;
    }
    
    return root;
}
