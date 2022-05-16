# **MATH**

## List of Functions
- [pow](#pow)
- [modulo](#modulo)
- [sum](#sum)
- [product](#product)
---
## <a id="pow">*pow*</a>
> ```pow(int/double a, int/double b) => int/double```
<br>
pow() returns \\( a^b \\). To use this function properly, make
sure to either have both values integers or double.


### Example:
```
var four = pow(2,2);
print four; // 4
var sixty_four = pow(8,2);
print sixty_four; // 64

```


---
## <a id="modulo">*modulo*</a>
> ```modulo(int a, int b) => int```
<br>
Modulo returns the remainder of `a % b`. To use this function properly
make sure both values are integers.


### Example:
```
var rem = modulo(567, 89);
print rem; // 33

```


---
## <a id="sum">*sum*</a>
> ```sum(int/double ...) => int/double```
<br>
This functions returns the sum of all values in the function.
All values in this function should be all integers or all double.


### Example:
```
var s = sum(3.2,8.6,9.6668, 5.21454);
print s; // 26.6813

```


---
## <a id="product">*product*</a>
> ```product(int/double ...) => int/double```
<br>
This function returns the product of all values in the function.
All values in this function should all be integers or all double.


### Example:
```
var p = product(8,7,9,3,4);
print p; //

```
