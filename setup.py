import os

version = 1
current_version = "0.1.0"
github = f"https://github.com/MKProj/Mufi-Lang/archive/refs/tags/v{current_version}.zip"


def ask_questions():
    print(f"""Welcome to Mufi Setup Script v{version}
Choose one of the following options:
    1) Install
    2) Uninstall
    3) Version""")
    return int(input("Enter option: "))


def install():
    print("Installing...")
    # gets the zip
    os.system(f"wget {github}")
    os.system(f"unzip v{current_version}.zip -d mufic")
    os.system("cd mufic && make release")
    os.system(f"mv mufic/mufi {bin_path}")
    os.removedirs("mufic")
    print("Installed!")


# first ask the questions
opt = ask_questions()
path = "/usr/local/bin/mufi"
bin_path = "/usr/local/bin/"

if opt == 1:
    if os.path.exists(path):
        os.remove(path)
        install()
    else:
        install()

if opt == 2 and os.path.exists(path):
    os.remove(path)

if opt == 3:
    print(f"Setup script v{version} | Mufi v{current_version}")
