# Vector Terminal
This program is a simple terminal written in C. All its operations are designed to work around vectors of integers.

## Why?
I wanted to deeply understand how a terminal worked, so I decided to build one entirely from scratch.

## Why vectors?
I needed some "objects" to make my terminal work with, like the real OS terminals that work with strings and files.

## Why C?
I love it.

## My System Specs
Last update: 26/05/2021

Windows: `Microsoft Windows [Versione 10.0.19042.985]`

Output of `gcc --version`:
`gcc (MinGW.org GCC-6.3.0-1) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.`

## Compile and Run
In the main folder of the project there are three `.bat` scripts to build and run the project.
For now, there's no Linux-compatible script so I report down here the commands used in the scripts.
- `build.bat` builds the project and puts the executable in the `bin` folder.
Runs the command `gcc src/*.c src/command_set/*.c src/main/*.c -o bin/vector.exe`
- `execute.bat` runs the executable `bin/vector.exe` (I am a bit lazy)
- `build_test.bat` builds either one single test file, by typing the name of the file without extension, or each test file (all test files are `src/test/*.c`), by typing `full`. When executing a full test, each test file is compiled and run separately and the result is written on `stdout`. The command run is: `gcc -DVT_TEST_MODE=1 src/test/<test_file> src\*.c src\command_set\*c -o src/test/<test_file>.exe`

## Contributions/Suggestions/Ideas
If you want to help, you can take a look at the ever-growing file `TODO.txt` where i write my ideas about future features to implement. I'm always happy to hear some suggestions, even crazy ones, so please let me know if you want to help me and maybe i'll add your name to the contributors' list.

## Bugs
This project is, obviously, full of bugs that i can't find so, if you're luckier than me, please let me know and i'll add your name in the contributors' list.

## How to contact me
My e-mail is `ledmington.dev@gmail.com`