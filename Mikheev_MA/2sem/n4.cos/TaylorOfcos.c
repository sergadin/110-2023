#include "TaylorOfcos.h"



double TaylorOfcos(double x, Er *error, double EPS){
    double cosx = 1;
    int max_count = 10000;
    double res = 1;
    int i;
    
    //printf("x = %lf\n", x);
    
    for(i = 1; i < max_count && fabs(res) > EPS; i++){
        
        //printf("res = %lf\n", res);
        res = res * (-1) * x*x / (2*i) / (2*i - 1);
        //printf("res = %lf\n", res);
        
        cosx = cosx + res;
    }
    
    *error = OK;
    
    if(i == max_count - 1){
        *error == LIMIT;
    }
    
    if(isnan(cosx) || isinf(cosx)){
        *error = NOT_CORRECT;
    }
    
    //printf("i = %d\n", i);
    //printf("cosx = %lf\n", cosx);
    return cosx;
}
