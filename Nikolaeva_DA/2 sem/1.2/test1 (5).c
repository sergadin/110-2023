#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"test2.h"

typedef double (*Fun)(double);
double composing_function(double x, int n, Fun *Func){
    double y = x;
    for(int i = 0; i < n; i++){
        y = Func[i](y);
    }
    return y;
}
