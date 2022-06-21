use std::ffi::{CString, CStr};
use std::os::raw::{c_char, c_double, c_int};
use std::fs::{File, read_to_string};
use std::io::Write;

// OS Functions

/// Used for Mufi's `cmd(command)`
#[no_mangle]
pub unsafe extern "C" fn cmd_(command: *mut c_char){
    let str = CStr::from_ptr(command).to_str().unwrap();
    let mut s = std::process::Command::new(str);
    let _ = s.spawn().unwrap();
}

/// Used for Mufi's `sys_exit(code)`
#[no_mangle]
pub unsafe extern "C" fn sys_exit(code: c_int){
    std::process::exit(code as i32);
}

// File functions
/// Used for Mufi's `file_write(path, data)`
#[no_mangle]
pub unsafe extern "C" fn file_write(path: *mut c_char, data: *mut c_char){
    let path = CStr::from_ptr(path).to_str().unwrap();
    let data = CStr::from_ptr(data).to_bytes();
    let mut file = File::open(path).unwrap();
    file.write_all(data).unwrap();
}

/// Used for Mufi's `file_append(path, data)`
#[no_mangle]
pub unsafe extern "C" fn file_append(path: *mut c_char, data: *mut c_char){
    let path = CStr::from_ptr(path).to_str().unwrap();
    let data = CStr::from_ptr(data).to_bytes();
    let mut file = File::options().append(true).open(path).unwrap();
    file.write_all(data).unwrap();
}

#[no_mangle]
pub unsafe extern "C" fn new_dir(path: *mut c_char){
    let path = CStr::from_ptr(path).to_str().unwrap();
    std::fs::create_dir(path).unwrap()
}


/// Used for Mufi's `file_read(path)`
#[no_mangle]
pub unsafe extern "C"  fn read_file(path: *const c_char) -> *mut c_char{
    let cstr = CStr::from_ptr(path).to_str().unwrap();
    let file_str = read_to_string(cstr).unwrap();
    let c = CString::new(file_str).unwrap();
    return c.into_raw()
}

// String functions
/// Used for Mufi's `char_at(string, index)`
#[no_mangle]
pub unsafe extern "C" fn char_at(str: *mut c_char, index: c_int) -> *mut c_char{
    let str = CStr::from_ptr(str).to_str().unwrap();
    let c = str.chars().nth(index as usize).unwrap();
    let cstr = CString::new(c.to_string()).unwrap();
    return cstr.into_raw()
}

/// Used for Mufi's `len(Value)`
#[no_mangle]
pub unsafe extern "C" fn len_str(str: *mut c_char) -> c_int{
    let str = CString::from_raw(str);
    let str = str.to_str().unwrap();
    let len = str.len();
    return len as c_int
}

/// Used for Mufi's `sub_str(string, start, end)`
#[no_mangle]
pub unsafe extern "C" fn substr(str: *mut c_char, start: c_int, end: c_int) -> *mut c_char{
    let str = CStr::from_ptr(str).to_str().unwrap();
    let string = str.to_string();
    let mut vec: Vec<char> = Vec::new();
    for i in start as usize .. (end + 1) as usize{
        vec.push(string.chars().nth(i).unwrap())
    }
    let mut string = String::new();
    for i in vec{
        string.push(i);
    }
    let cstr = CString::new(string).unwrap();
    return cstr.into_raw()
}

/// Used for Mufi's `trim(string)`
#[no_mangle]
pub unsafe extern "C" fn trim(str: *mut c_char) -> *mut c_char{
    let str = CStr::from_ptr(str).to_str().unwrap();
    let str = str.trim();
    let cstr = CString::new(str.to_string()).unwrap();
    return cstr.into_raw()
}

// Math functions
#[no_mangle]
pub unsafe extern "C" fn powd(a: c_double, b: c_double) -> c_double{
    return a.powi(b as i32)
}

#[no_mangle]
pub unsafe extern "C" fn powi(a: c_int, b: c_int) -> c_int{
    let result = a ^ b;
    return result
}

#[no_mangle]
pub unsafe extern "C" fn modulo(a: c_int, b: c_int) -> c_int{
    return a % b
}

#[no_mangle]
pub unsafe extern "C" fn log_(base: c_double, value: c_double)->c_double{
    return value.log(base)
}
