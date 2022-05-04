<img src="logo.png" width="200px" height="200px">

# Mufi Lang 

> Note: This project is currently being developed and is changing quite often, it is not recommended 
> to be installed until it reaches a stable state which is approximately coming in 1-2 months. 

## Installation Requirements 

- clang 
- make
- wget 
- Python3
- unzip

## Doc Requirements 

- Rust (Uses MDBook)
- pdflatex 

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
