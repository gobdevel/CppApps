# CppProjectTemplate

This template can be used to create a simple C++ TDD Application project.

1. git clone this repository
2. Pull all submodule with `git submodule update --init --recursive`
3. Change Project name in root level CMakeLists.txt.
4. Create a build directory at project root level.
5. Symlink compile_commands.txt to project root - `ln -s ~/CppProjectTemplate/build/compile_commands.json ~/CppProjectTemplate/`


## To Compile
- Go to build directory and issue
    `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../`

- Compile using
   `make all`
