#include "TaylorOfcos.h"



double TaylorOfcos(double x, Er *error, double EPS){
    double cosx = 1;
    int max_count = 10000;
    double res = 1;
    int i;
    
    for(i = 1; i < max_count && fabs(res) > EPS; i++){
        
        res = res * (-1) * x*x / (2*i) / (2*i - 1);  // Каждое слагаемое отличается от предыдушего на
                                                     // (-1)X^2/2i/(2i-1)   
        cosx = cosx + res;
    }
    
    *error = OK;
    
    if(i == max_count - 1){
        *error == LIMIT;
    }
    
    if(isnan(cosx) || isinf(cosx)){
        *error = NOT_CORRECT;
    }
    
    return cosx;
}
