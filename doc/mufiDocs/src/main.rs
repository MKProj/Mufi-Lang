use std::fs::File;
use std::io::Write;
use std::path::PathBuf;
use toml::{from_str, to_string_pretty};
use serde_derive::{Serialize, Deserialize};
const VERSION: &str = "0.1.0";
const RELEASE: &str = "Baloo";
fn TOML_PATH()-> PathBuf {PathBuf::from("../toml/")}
fn OUT_PATH()-> PathBuf { PathBuf::from("../std/src")}
const ROOT: &str = r#"# Mufi Lang v{version} [{release} Release]

## List of Modules
"#;

const MOD_TEMPLATE: &str = r#"# **{module}**

## List of Functions
"#;

const TEMPLATE: &str = r#"
---
## <a id="{function}">*{function}*</a>
> {description}

### Example:
```
{example}
```
"#;


#[derive(Deserialize, Serialize, Clone)]
struct Function{
    name: String,
    description: String,
    example: String,
}

#[derive(Deserialize, Serialize, Clone)]
struct Module{
    name: String,
    Function: Vec<Function>,
}

#[derive(Deserialize, Serialize, Clone)]
struct RootModule{
    version: String,
    release_name: String,
    modules: Vec<Module>
}



impl RootModule{
    fn new(modules: Vec<Module>) -> Self{
        Self{
            version: VERSION.to_owned(),
            release_name: RELEASE.to_owned(),
            modules
        }
    }
    fn combine(&self) -> String{
        let mut r = ROOT.to_owned();
        r = r.replace("{version}", &self.version);
        r = r.replace("{release}", &self.release_name);

        let mut list = Vec::new();

        for i in &self.modules{
            list.push(format!("- ### [{}](./{}.md)", &i.name.to_uppercase(), &i.name))
        }

        r.push_str(&list.join("\n"));

        r
    }
}


impl Module{
    fn get(path: PathBuf) -> Self{
        from_str(&std::fs::read_to_string(path).unwrap()).unwrap()
    }
    fn combine(&self) -> String{
        let mut s = MOD_TEMPLATE.to_owned();
        s = s.replace("{module}", &self.name.to_uppercase());
        let mut list = Vec::new();
        for i in &self.Function{
            list.push(format!("- [{}](#{})", i.name, i.name));
        }
        let list_str = list.join("\n");
        s.push_str(&list_str);
        let mut func_temps = Vec::new();
        for i in &self.Function{
            func_temps.push(i.change_params());
        }
        let func_str = func_temps.join("\n");
        s.push_str(&func_str);
        s
    }
}

impl Function{
    fn change_params(&self)->String{
        let mut s = TEMPLATE.to_owned();
        s = s.replace("{function}", &self.name);
        s = s.replace("{description}", &self.description);
        s = s.replace("{example}", &self.example);
        s
    }
}



fn main() {
    //let string_path = TOML_PATH.join("string.toml");
    let os_path = TOML_PATH().join("os.toml");
    let conv_path = TOML_PATH().join("conv.toml");
    let files_path = TOML_PATH().join("files.toml");
    let math_path = TOML_PATH().join("math.toml");

    let os_mod = Module::get(os_path);
    let conv_mod = Module::get(conv_path);
    let files_mod = Module::get(files_path);
    let math_mod = Module::get(math_path);

    let mut index = File::create(OUT_PATH().join("index.md")).unwrap();
    let mut os_file = File::create(OUT_PATH().join("os.md")).unwrap();
    let mut conv_file = File::create(OUT_PATH().join("conv.md")).unwrap();
    let mut files_file = File::create(OUT_PATH().join("files.md")).unwrap();
    let mut math_file = File::create(OUT_PATH().join("math.md")).unwrap();

    let root_mod = RootModule::new(vec![os_mod.clone(), conv_mod.clone(), files_mod.clone(), math_mod.clone()]);

    index.write_all(root_mod.combine().as_bytes()).unwrap();
    os_file.write_all(os_mod.combine().as_bytes()).unwrap();
    conv_file.write_all(conv_mod.combine().as_bytes()).unwrap();
    files_file.write_all(files_mod.combine().as_bytes()).unwrap();
    math_file.write_all(math_mod.combine().as_bytes()).unwrap();

}