<img src="logo.png" width="200px" height="200px">

# Mufi Lang 

[Mufi Roadmap Plan](https://www.notion.so/mkproj/a0ce104710f546d5aea1b0ec70995b73?v=ef7b2a18763b4e228c9f389f765965b1)
> This project is under the [GPLv2 License](./LICENSE.md)
## Installation Requirements 
- clang 
- Rust

Install Steps: 
```shell
$ wget https://github.com/MKProj/Mufi-Lang/archive/refs/tags/0.1.0.zip
$ unzip 0.1.0.zip
$ cd Mufi-Lang-0.1.0
$ make install 
# Test to see if it's correct 
$ mufi version 
Version 0.1.0 (Baloo Release)
```

> Note: This language only supports Unix systems, if you're on a Windows system, use WSL. 
> Documentation will come in the near future 

## Making Debug and Release Mode 

For development purposes, keeping debug macros are useful to see 
the op codes being emitted. As such, either you make the mufi binary in debug or 
release mode using `make debug` or `make release`. These run a python script 
that changes `src/common.h` to not `undef` (Debug) or does `undef` (Release) the `#define DEBUG_*` macros. 


```shell
$ make debug
$ ./mufi
# or 
$ make release 
$ ./mufi
```

> **Note:** Debug mode does show all the logging information on the Garbage Collector (`DEBUG_LOG_GC` & `DEBUG_STRESS_GC`)

## Testing 
Test programs are placed inside in `test`, to test all these programs you can run `make test_mufi` that will 
execute the simple `utils/test.py` program.

## Doc Plans 
The project is planned to contain a documentation for the `stdlib` and 
a `guide` to the language for the users. 

The `guide` will be available as: 

- `pdf`
- `web/HTML`

The `stdlib` doc will be available as: 

- `pdf`
- `web/HTML`
- `man`

---
## Credits 
A lot of this compiler is built under the guidance of *Robert's Nystroms Crafting Interpreters*. This 
book provides great theory and application to building interpreters and bytecode compilers. I highly recommend 
this book if you're interested in language hacking, and you can check more out 
at [www.craftinginterpreters.com](http://www.craftinginterpreters.com).