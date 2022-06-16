% Mufi(1) mufi v0.1.0 [Baloo Release]
% Mustafif Khan
% May 2022

# Description 

This page is a one-stop shop to see all different 
modules and functions inside of Mufi's standard library.
In the future we may create different pages for the modules, 
but since our library isn't the largest, this seemed like the easiest option.

# Math Module [math]

## List of Functions
- [pow](#pow)
- [modulo](#modulo)
- [sum](#sum)
- [product](#product)

### pow(int/double a, int/double b) => int/double
pow() returns a^b. To use this function properly, make
sure to either have both values integers or double.


### Example:
```
var four = pow(2,2);
print four; // 4
var sixty_four = pow(8,2);
print sixty_four; // 64

```

### modulo(int a, int b) => int

Modulo returns the remainder of **a % b**. To use this function properly
make sure both values are integers.


### Example:
```
var rem = modulo(567, 89);
print rem; // 33

```

### sum(int/double ...) => int/double

This functions returns the sum of all values in the function.
All values in this function should be all integers or all double.


### Example:
```
var s = sum(3.2,8.6,9.6668, 5.21454);
print s; // 26.6813

```

### product(int/double ...) => int/double
This function returns the product of all values in the function.
All values in this function should all be integers or all double.


### Example:
```
var p = product(8,7,9,3,4);
print p; //

```

# Conversion Module [conv]

## List of Functions
- [as_double](#as_double)
- [as_int](#as_int)

### as_double(Value value) => double
This function takes in a value and tries to convert it to a double.
If a value is passed in that cannot be converted, the function will return -1.


### Example:
```
var i = 12; // integer
print as_double(i); // 12
var s = "23.2"; // string
print as_double(s); // 23.2

```


### as_int(Value value) => int

This function takes in a value and tries to convert it to an integer.
If a value is passed in that cannot be converted, the function will return -1;


### Example:
```
var d = 23.6; // double
print as_int(d); // 23
var s = "32"; //string
print as_int(s); // 32

```

