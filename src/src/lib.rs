mod bindings;
use std::ffi::CString;
use bindings::{runFile, initVM, freeVM, MINOR, PATCH, MAJOR};


pub fn compile(path: &str){
    unsafe {
        initVM();
        let cstr = CString::new(path).unwrap();
        let raw = cstr.into_raw();
        runFile(raw);
        freeVM();
    }
}


pub fn version() -> String{
    format!("Mufi Version {}.{}.{}", MAJOR, MINOR, PATCH)
}
