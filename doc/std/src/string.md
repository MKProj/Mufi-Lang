# **STRING**

## List of Functions
- [char_at()](#char_at())
- [len()](#len())
---
## <a id="char_at()">*char_at()*</a>
> *char_at(string str, int index) => string*<br>
CharAt returns the character in a string at the specified index,
if this functions reaches an error, either the program will panic or return nil.


### Example:
```
var char = char_at("hello", 3);
print char; // l

```


---
## <a id="len()">*len()*</a>
> *len(string) => int*<br>
Len returns the length of a string. If this function reaches an error it returns 0 alongside
an error message.


### Example:
```
var length = len("OOOOOOO");
print length; // 7

```
