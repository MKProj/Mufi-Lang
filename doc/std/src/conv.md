# **CONV**

## List of Functions
- [as_double](#as_double)
- [as_int](#as_int)
---
## <a id="as_double">*as_double*</a>
> `as_double(Value value) => double` <br>
This function takes in a value and tries to convert it to a double.
If a value is passed in that cannot be converted, the function will return -1.


### Example:
```
var i = 12; // integer
print as_double(i); // 12
var s = "23.2"; // string
print as_double(s); // 23.2

```


---
## <a id="as_int">*as_int*</a>
> `as_int(Value value) => int` <br>
This function takes in a value and tries to convert it to an integer.
If a value is passed in that cannot be converted, the function will return -1;


### Example:
```
var d = 23.6; // double
print as_int(d); // 23
var s = "32"; //string
print as_int(s); // 32

```
