use std::path::PathBuf;

fn main(){
    //println!("cargo:rustc-rerun-if-changed=.");
   // println!("cargo:rustc-link-search=.");

    cc::Build::new()
        .include(".")
        .file("chunk.c")
        .file("compiler.c")
        .file("debug.c")
        .file("memory.c")
        .file("pre.c")
        .file("object.c")
        .file("scanner.c")
        .file("table.c")
        .file("value.c")
        .file("vm_bench.c")
        .out_dir(".")
        .compile("mufi.so");

    let bindings = bindgen::Builder::default()
        .header("vm.h")
        .header("value.h")
        .header("table.h")
        .header("scanner.h")
        .header("object.h")
        .header("memory.h")
        .header("debug.h")
        .header("pre.h")
        .header("compiler.h")
        .header("common.h")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from("./src/");
    bindings.write_to_file(out_path.join("bindings.rs")).unwrap();
}