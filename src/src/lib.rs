mod bindings;
use std::ffi::CString;
use bindings::{runFile, initVM, freeVM};


pub fn compile(path: &str){
    unsafe {
        initVM();
        let cstr = CString::new(path).unwrap();
        let raw = cstr.into_raw();
        runFile(raw);
        freeVM();
    }
}
