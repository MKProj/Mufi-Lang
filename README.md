<img src="logo.png" width="200px" height="200px">

# Mufi Lang 

> Note: This project is currently being developed and is changing quite often, it is not recommended 
> to be installed until it reaches a stable state which is approximately coming in 1-2 months. 


## To build 
Have `clang` installed, currently this guide will only be for linux systems. 
```shell
$ sudo apt install clang # to install clang 
# clone the repo 
$ git clone https://github.com/MKProj/Mufi-Lang
$ cd Mufi-Lang
$ make build 
$ make install_linux # Not recommended to install yet 
```

## Sample Code 
```
class IP{
    init(address, port){
        self.address = address;
        self.port = port;
    }
    connect(){
        let message = "Connecting to " + this.address + "at port " + this.port;
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
