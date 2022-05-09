<img src="logo.png" width="200px" height="200px">

# Mufi Lang 

[Mufi Roadmap Plan](https://www.notion.so/mkproj/a0ce104710f546d5aea1b0ec70995b73?v=ef7b2a18763b4e228c9f389f765965b1)

> Note: This project is currently being developed and is changing quite often, it is not recommended 
> to be installed until it reaches a stable state which is approximately coming in 1-2 months. 

## Installation Requirements 

- clang 
- make
- wget 
- Python3
- unzip

> Note: Currently the `setup.py` script will only support Unix systems in super user mode. I do plan 
> on releasing a stable on `winget` when ready.

## Doc Requirements 

- Rust (Uses MDBook)
- pdflatex 

## Making Debug and Release Mode 

For development purposes, keeping debug macros are useful to see 
the op codes being emitted. As such, either you make the mufi binary in debug or 
release mode using `make debug` or `make release`. These run a python script 
that changes `src/common.h` to not `undef` (Debug) or does `undef` (Release) the `#define DEBUG_*` macros. 


```shell
# Debug mode 
$ make debug 
$ ./mufi 
Version 0.1.0 (Baloo Release)
(mufi) >> 2 + 2
== code ==
0000    1 OP_CONSTANT         0 '2'
0002    | OP_CONSTANT         1 '2'
0004    | OP_ADD
0005    2 OP_RETURN

0000    1 OP_CONSTANT         0 '2'
4
# Release mode 
$ make release 
$ ./mufi 
Version 0.1.0 (Baloo Release)
(mufi) >> 2 + 2
4
```
## Sample Code 
```
class IP{
    init(address, port){
        self.address = address;
        self.port = port;
    }
    connect(){
        let message = "Connecting to " + self.address + "at port " + self.port;
        print message;
    }
}

let ip = IP("127.0.0.1", "45675");
ip.connect();
```

## Plans after First Release 
- Project Manager 
- Documentation books 
- Standard Library (built in)
- Figure out how to do imports 
- Some type of continuous integration 
- Support to Mac and Windows in guide 
