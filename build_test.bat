@echo off

set FLAGS=-DVT_TEST_MODE=1

rem If no parameter...
if [%1] == [] (
    echo Please type an available test name or '?' to get help.
    goto available_tests
)

rem If being told to clean the compiled tests
if "%1" == "clean" (
    del /Q src\test\*.exe src\test\*.o
    echo All .exe and .o files have been deleted.
    goto END
)

rem Help message
if "%1" == "?" (
    echo - Type "clean" as first parameter to delete all .exe and .o files
    echo - Type the name of the file with the test to compile it,
    echo        the executable will be in the same directory and will
    echo        be executed right after the compilation
    echo - Type "full" to compile and run each test, one by one
    echo        a full report file with name %FULL_REPORT_FILE% will
    echo        be created
    echo - All other parameters after the first are ignored
    goto END
)

rem Full test
if "%1" == "full" (
    echo Full test started at %date% %time%
    
    rem https://stackoverflow.com/questions/23228983/batch-file-list-files-in-directory-only-filenames/23229008
    for /f tokens^=* %%A in ('where "src\test:*.c"') do (
        echo[
        if exist src\test\%%~nA.exe (
            del /Q src\test\%%~nA.exe
        )
        gcc %FLAGS% %%A src\*.c src\command_set\*c -o src\test\%%~nA.exe
        if exist src\test\%%~nA.exe (
            echo ======   %%~nA   ======
            echo Test started at %date% %time%
            src\test\%%~nA.exe
            echo Test ended at %date% %time%
            echo ====== END %%~nA ======
        )
    )
    goto END
)

if not exist src\test\%1.c (
    echo Test named "%1" does not exist.
    goto available_tests
)

if exist src\test\%1.exe (
    del /Q src\test\%1.exe
)

gcc %FLAGS% src\test\%1.c src\*.c src\command_set\*c -o src\test\%1.exe
if exist src\test\%1.exe src\test\%1.exe
goto END


:available_tests
echo Available tests to build are:
set mypath=src\test
rem https://stackoverflow.com/questions/23228983/batch-file-list-files-in-directory-only-filenames/23229008
for /f tokens^=* %%A in ('where "$mypath:*.c"') do echo %%~nA
set "mypath="

:END
set "FLAGS="
exit /b 1