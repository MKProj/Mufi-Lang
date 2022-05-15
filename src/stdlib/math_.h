#ifndef mufi_stdlib_math_h
#define mufi_stdlib_math_h



//> Returns power of value: a^b (double)
double powd(double a, double b);
//> Returns power of value: a^b (int)
int powi(int a, int b);

//> Returns modulo of a to b: a % b
int modulo(int a, int b);

//> Returns sum of array of values (double)
double sum(double* values);

//> Returns product of array of values (double)
double product(double* values);

//> Returns log of value with a specified base: log_b a
double log_(double base, double value);




#endif