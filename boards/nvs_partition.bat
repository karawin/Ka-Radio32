@echo off
rem SET path=%path%;..\webpage\bin
IF EXIST comment.txt (
    del comment.txt
)
grep --help> comment.txt
if %errorlevel% EQU 0  GOTO suite1
SET path=%path%;..\webpage\bin
:suite1
IF [%1] == []  goto all
call:build_binary %1
EXIT /B %ERRORLEVEL%


REM No file given, compute all *.csv
:all
for /r %%Y in (*.csv) do call:build_binary  %%Y
EXIT /B %ERRORLEVEL%




:build_binary
echo.
set filename=%1
For %%X in ("%filename%") do (
set fname=%%~nX
set ext=%%~xX
)


if "%ext%" NEQ ".csv" set ext=.csv

grep "L_COMMENT" %fname%%ext%  > comment.txt
sed -i "s/^.*,string,//; s/\s*\.\s*$//" comment.txt
del sed*
call:header %1 comment: 
type comment.txt
ECHO ================================================= 
del comment.txt


echo.input: %fname%%ext%
echo.output: ./build/%fname%.bin

Python nvs_partition_gen.py  --version v1  --output "./build/%fname%.bin"  --input "%fname%%ext%"  --size 0x3000
if %errorlevel% NEQ 0  (echo.error  %errorlevel% on the generation  for %fname%%ext%
goto :eof)
call:header %fname%.bin must be flashed at 0x3a2000
EXIT /B 0

:header
ECHO ================================================= 
ECHO %*
ECHO ================================================= 
EXIT /B 0