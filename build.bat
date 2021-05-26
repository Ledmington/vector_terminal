@echo off
REM The command above is for deactivating the output as if each command is executed alone
REM Remove that command to see what command is giving errors

if not exist bin mkdir bin
del /Q bin\*

gcc src/*.c src/command_set/*.c src/main/*.c -o bin/vector.exe