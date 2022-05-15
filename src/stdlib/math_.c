#include <math.h>
#include "math_.h"

double powd(double a, double b){
    return pow(a, b);
}

int powi(int a, int b){
    return (int) pow((double)a, (double)b);
}

int modulo(int a, int b){
    return a % b;
}

double sum(double* values){
    double sum = 0;
    for(int i=0; i < sizeof(values); i++){
        sum += values[i];
    }
    return sum;
}

double product(double* values){
    double product = 1;
    for(int i=0; i < sizeof(values); i++){
        product *= values[i];
    }
    return product;
}


double log_(double base, double value){
    // to get value log_base value
    // we can use the rule (ln base / ln value) = log_base value
    return log(base) / log(value);
}