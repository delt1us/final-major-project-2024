# @Author: Armin Raad <armin3600z@gmail.com>
# @Date: 2024-01-29 12:50:46
# @Last Modified by: Armin Raad <armin3600z@gmail.com>
# @Last Modified time: 2024-04-21 15:46:07

from os import makedirs, path
import sys
import subprocess


def my_print(output: str):
    line: str = "\n" + "-" * 50 + "\n"
    print(f"{line}{output}{line}")


def build():
    if (len(sys.argv) > 1):
        my_print("Running cmake")

        cmakeProcess = subprocess.run(
            'cmake -G "Unix Makefiles" -B ./build/ -S . "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DVCPKG_TARGET_TRIPLET:STRING=x64-mingw-dynamic')

        if cmakeProcess.returncode != 0:
            my_print("Cmake failed")
            return

    my_print("Running build")
    buildProcess = subprocess.run("cmake --build build")
    if buildProcess.returncode != 0:
        my_print("Build failed")
        return

    my_print("Running application")
    appProcess = subprocess.run("./build/client.exe")
    if appProcess.returncode != 0:
        my_print("Run failed")
        return

def make_build_dir():
    if not path.exists("./build/"):
        my_print("Making build directory")
        makedirs("./build/")
    else:
        my_print("Build directory exists, continuing")


if __name__ == "__main__":
    make_build_dir()
    build()

